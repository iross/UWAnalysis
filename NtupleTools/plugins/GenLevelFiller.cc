#include "UWAnalysis/NtupleTools/plugins/GenLevelFiller.h"

GenLevelFiller::GenLevelFiller(const edm::ParameterSet& iConfig):
    gensrc_(iConfig.getParameter<edm::InputTag>("gensrc"))
{
    edm::Service<TFileService> fs;
    tree = fs->make<TTree>( "genEventTree"  , "");

    // Initialize variables to zero
    hPt     = 0;
    hMass   = 0;
    hEta    = 0;
    hPhi    = 0;
    EVENT   = 0;
    RUN     = 0;
    LUMI    = 0;

    for (int i = 0; i < 2; ++i)
    {
        zPt[i]      = 0;
        zEta[i]     = 0;
        zPhi[i]     = 0;
        zMass[i]    = 0;
    }

    for (int i = 0; i < 4; ++i)
    {
        lPt[i]      = 0;
        lEta[i]     = 0;
        lPhi[i]     = 0;
        lPdgId[i]   = 0;
    }

    // Event numbers
    tree->Branch("EVENT",&EVENT,"EVENT/I");
    tree->Branch("RUN",&RUN,"RUN/I");
    tree->Branch("LUMI",&LUMI,"LUMI/I");

    // Fill Higgs values
    tree->Branch("hPt",&hPt,"hPt/D");
    tree->Branch("hMass",&hMass,"hMass/D");
    tree->Branch("hEta",&hEta,"hEta/D");
    tree->Branch("hPhi",&hPhi,"hPhi/D");

    // Fill Z values
    tree->Branch("z1Pt",&zPt[0],"z1Pt/D");
    tree->Branch("z2Pt",&zPt[1],"z2Pt/D");

    tree->Branch("z1Eta",&zEta[0],"z1Eta/D");
    tree->Branch("z2Eta",&zEta[1],"z2Eta/D");

    tree->Branch("z1Phi",&zPhi[0],"z1Phi/D");
    tree->Branch("z2Phi",&zPhi[1],"z2Phi/D");

    tree->Branch("z1Mass",&zMass[0],"z1Mass/D");
    tree->Branch("z2Mass",&zMass[1],"z2Mass/D");

    // Fill lepton Values
    tree->Branch("z1l1Pt",&lPt[0],"z1l1Pt/D");
    tree->Branch("z1l2Pt",&lPt[1],"z1l2Pt/D");
    tree->Branch("z2l1Pt",&lPt[2],"z2l1Pt/D");
    tree->Branch("z2l2Pt",&lPt[3],"z2l2Pt/D");

    tree->Branch("z1l1Eta",&lEta[0],"z1l1Eta/D");
    tree->Branch("z1l2Eta",&lEta[1],"z1l2Eta/D");
    tree->Branch("z2l1Eta",&lEta[2],"z2l1Eta/D");
    tree->Branch("z2l2Eta",&lEta[3],"z2l2Eta/D");

    tree->Branch("z1l1Phi",&lPhi[0],"z1l1Phi/D");
    tree->Branch("z1l2Phi",&lPhi[1],"z1l2Phi/D");
    tree->Branch("z2l1Phi",&lPhi[2],"z2l1Phi/D");
    tree->Branch("z2l2Phi",&lPhi[3],"z2l2Phi/D");

    tree->Branch("z1l1pdgId",&lPdgId[0],"z1l1pdgId/I");
    tree->Branch("z1l2pdgId",&lPdgId[1],"z1l2pdgId/I");
    tree->Branch("z2l1pdgId",&lPdgId[2],"z2l1pdgId/I");
    tree->Branch("z2l2pdgId",&lPdgId[3],"z2l2pdgId/I");
}

GenLevelFiller::~GenLevelFiller() {}

void GenLevelFiller::beginJob() {}

void GenLevelFiller::endJob() {}

void GenLevelFiller::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
    // Grab event identification
    EVENT  = iEvent.id().event();
    RUN    = iEvent.id().run();
    LUMI   = iEvent.luminosityBlock();

    // initialize variables to zero before
    // running over gen particles
    hPt     = 0;
    hMass   = 0;
    hEta    = 0;
    hPhi    = 0;

    for (int i = 0; i < 2; ++i)
    {
        zPt[i]      = 0;
        zEta[i]     = 0;
        zPhi[i]     = 0;
        zMass[i]    = 0;
    }

    for (int i = 0; i < 4; ++i)
    {
        lPt[i]      = 0;
        lEta[i]     = 0;
        lPhi[i]     = 0;
        lPdgId[i]   = 0;
    }

    // get gen particles
    edm::Handle<reco::GenParticleCollection> genCandidates;
    iEvent.getByLabel(gensrc_, genCandidates);

    int zn = 0;

    // iterate over gen particle collection
    reco::GenParticleCollection::const_iterator candIt;
    for (candIt = genCandidates->begin(); candIt != genCandidates->end(); ++candIt)
    {
        // if Higgs
        if ( candIt->pdgId() == 25 )
        {
            hPt     = candIt->pt();
            hMass   = candIt->mass();
            hEta    = candIt->eta();
            hPhi    = candIt->phi();
        }
        // if Z boson
        else if ( candIt->pdgId() == 23 && zn < 2 )
        {
            zPt[zn]     = candIt->pt();
            zMass[zn]   = candIt->mass();
            zEta[zn]    = candIt->eta();
            zPhi[zn]    = candIt->phi();

            const reco::Candidate* l1;
            const reco::Candidate* l2;

            // get Z daughters
            // set l1 to be leading pt lepton
            if (candIt->daughter(0)->pt() > candIt->daughter(1)->pt())
            {
                l1 = candIt->daughter(0);
                l2 = candIt->daughter(1);
            }
            else
            {
                l1 = candIt->daughter(1);
                l2 = candIt->daughter(0);
            }

            lPt[2*zn]    = l1->pt();
            lEta[2*zn]   = l1->eta();
            lPhi[2*zn]   = l1->phi();
            lPdgId[2*zn] = l1->pdgId();

            lPt[2*zn+1]    = l2->pt();
            lEta[2*zn+1]   = l2->eta();
            lPhi[2*zn+1]   = l2->phi();
            lPdgId[2*zn+1] = l2->pdgId();

            zn++;
        }
    }

    tree->Fill();
}

DEFINE_FWK_MODULE(GenLevelFiller);
