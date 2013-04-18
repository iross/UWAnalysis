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
    zzPt     = 0;
    zzMass   = 0;
    zzEta    = 0;
    zzPhi    = 0;
    EVENT   = 0;
    RUN     = 0;
    LUMI    = 0;

    for (int i = 0; i < 2; ++i)
    {
        zPt[i]      = 0;
        zEta[i]     = 0;
        zPhi[i]     = 0;
        zMass[i]    = 0;
        zP4[i].SetPtEtaPhiM(50,0.0,0.0,1000);
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

    // Fill "ZZ" values (Z1+Z2)
    tree->Branch("zzPt",&zzPt,"zzPt/D");
    tree->Branch("zzMass",&zzMass,"zzMass/D");
    tree->Branch("zzEta",&zzEta,"zzEta/D");
    tree->Branch("zzPhi",&zzPhi,"zzPhi/D");

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

    zzPt     = 0;
    zzMass   = 0;
    zzEta    = 0;
    zzPhi    = 0;

    for (int i = 0; i < 2; ++i)
    {
        zPt[i]      = 0;
        zEta[i]     = 0;
        zPhi[i]     = 0;
        zMass[i]    = 0;
        zP4[i].SetPtEtaPhiM(50,0.0,0.0,1000);
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
    int lepCount = 0;

    std::vector<std::vector<reco::GenParticle>::const_iterator> leptons;

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
            zP4[zn].SetPtEtaPhiM(candIt->pt(),candIt->eta(),candIt->phi(),candIt->mass());

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
        // if gg to ZZ to 4l @ 8 TeV
        // consider electrons, muons, or taus
        else if ( candIt->status() == 3 && ( abs(candIt->pdgId()) == 11 || abs(candIt->pdgId()) == 13 || abs(candIt->pdgId()) == 15 ) )
        {
            lepCount++;
            leptons.push_back(candIt);
        }
    }
    zzP4 = zP4[0]+zP4[1];
    zzMass      = zzP4.M();
    zzEta       = zzP4.Eta();
    zzPhi       = zzP4.Phi();
    zzPt        = zzP4.Pt();

    // special case for running on 8 TeV ggZZ sample
    if ( zn == 0 && lepCount >= 4 )
    {
        // leptons must be sorted before they can be permuted
        std::sort(leptons.begin(),leptons.end(),compareLeptons);

        double min = 91.2;
        TLorentzVector L1, L2, L3, L4, Z1, Z2;
        int id1, id2, id3, id4;
        do
        {
            // ensure opposite-charge-same-flavor pairs
            // permute through different combinations of the leptons to build Z candidates
            if ( leptons.at(0)->pdgId() == -leptons.at(1)->pdgId() && leptons.at(2)->pdgId() == -leptons.at(3)->pdgId() )
            {
                // build lepton 4-vectors from lepton candidates
                TLorentzVector l1, l2, l3, l4, z1, z2;
                l1.SetPtEtaPhiM(leptons.at(0)->pt(),leptons.at(0)->eta(),leptons.at(0)->phi(),leptons.at(0)->mass());
                l2.SetPtEtaPhiM(leptons.at(1)->pt(),leptons.at(1)->eta(),leptons.at(1)->phi(),leptons.at(1)->mass());
                l3.SetPtEtaPhiM(leptons.at(2)->pt(),leptons.at(2)->eta(),leptons.at(2)->phi(),leptons.at(2)->mass());
                l4.SetPtEtaPhiM(leptons.at(3)->pt(),leptons.at(3)->eta(),leptons.at(3)->phi(),leptons.at(3)->mass());

                z1 = l1 + l2; // create Z 4-vectors from leptons
                z2 = l3 + l4;

                // set Z1 to be closest to nominal Z mass
                if ( fabs(z1.M()-91.2) < min )
                {
                    min = fabs(z1.M()-91.2);
                    Z1 = z1;
                    Z2 = z2;
                    L1 = l1;
                    L2 = l2;
                    L3 = l3;
                    L4 = l4;
                    id1 = leptons.at(0)->pdgId();
                    id2 = leptons.at(1)->pdgId();
                    id3 = leptons.at(2)->pdgId();
                    id4 = leptons.at(3)->pdgId();
                }
            }
        }
        while ( next_permutation(leptons.begin(), leptons.end(), compareLeptons) );

        zPt[0]    = Z1.Pt();
        zEta[0]   = Z1.Eta();
        zPhi[0]   = Z1.Phi();
        zMass[0]  = Z1.M();
        zPt[1]    = Z2.Pt();
        zEta[1]   = Z2.Eta();
        zPhi[1]   = Z2.Phi();
        zMass[1]  = Z2.M();

        zzP4 = Z1+Z2;
        zzMass      = zzP4.M();
        zzEta       = zzP4.Eta();
        zzPhi       = zzP4.Phi();
        zzPt        = zzP4.Pt();

        lPt[0]    = L1.Pt();
        lEta[0]   = L1.Eta();
        lPhi[0]   = L1.Phi();
        lPdgId[0] = id1;

        lPt[1]    = L2.Pt();
        lEta[1]   = L2.Eta();
        lPhi[1]   = L2.Phi();
        lPdgId[1] = id2;

        lPt[2]    = L3.Pt();
        lEta[2]   = L3.Eta();
        lPhi[2]   = L3.Phi();
        lPdgId[2] = id3;

        lPt[3]    = L4.Pt();
        lEta[3]   = L4.Eta();
        lPhi[3]   = L4.Phi();
        lPdgId[3] = id4;
    }

    tree->Fill();
}

bool compareLeptons(std::vector<reco::GenParticle>::const_iterator i, std::vector<reco::GenParticle>::const_iterator j)
{
    return (i->pt() < j->pt());
}

DEFINE_FWK_MODULE(GenLevelFiller);
