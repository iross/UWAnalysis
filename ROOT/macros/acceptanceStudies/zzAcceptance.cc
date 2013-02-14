/**
 * @file zzAcceptance.cc
 * @author D. Austin Belknap <dabelknap@wisc.edu>
 *
 * Runs over a ZZ MC sample with all gen level information stored.
 * Counts the events after a series of cuts are applied to estimate
 * efficiency and acceptance.
 */

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <iomanip>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

#include "TTree.h"
#include "TFile.h"
#include "TH1F.h"


using namespace std;


// Function prototypes
bool ptCut(int pdgId, double pt);
void zzAcceptance();
bool passPtCuts(double pt[], int pdgId[]);
set<string> genRecoEventIds(string treeName, TFile *f);
double recoEff(string histName, string treeName, TFile *f);
double recoYield(string treeName, double lumi, TFile *f);


// Global Constants
const double ZMASS = 91.1876;
const double HMASS = 125.0;


int main()
{
    zzAcceptance();

    return 0;
}



void zzAcceptance()
{
    // Pythia Sample 8 TeV
    // TFile *fGen = new TFile("/afs/hep.wisc.edu/cms/belknap/dataSamples/acceptanceStudy/ZZGenLvl.root"); // gen level events only
    // TFile *fRec = new TFile("/afs/hep.wisc.edu/cms/belknap/dataSamples/acceptanceStudy/ZZ4EReco.root"); // Reconstructed Monte Carlo
    
    // Powheg Sample 8 TeV
    // TFile *fGen = new TFile("/afs/hep.wisc.edu/cms/belknap/dataSamples/acceptanceStudy/ZZ2E2MGen.root"); // gen level events only
    // TFile *fRec = new TFile("/afs/hep.wisc.edu/cms/belknap/dataSamples/acceptanceStudy/ZZ2E2Mtest.root"); // Reconstructed Monte Carlo
    
    // Pythia ggZZ Sample 8 TeV
    // TFile *fGen = new TFile("/afs/hep.wisc.edu/cms/belknap/dataSamples/acceptanceStudy/ggZZ2L2LGen7reco.root"); // gen level events only
    // TFile *fRec = new TFile("/afs/hep.wisc.edu/cms/belknap/dataSamples/acceptanceStudy/ggZZ4LReco.root"); // Reconstructed Monte Carlo
    
    // Higgs ggH125 Sample 8 TeV
    TFile *fGen = new TFile("/afs/hep.wisc.edu/cms/belknap/dataSamples/acceptanceStudy/ggH125Gen.root");
    TFile *fRec = new TFile("/afs/hep.wisc.edu/cms/belknap/dataSamples/HZZ4l/ggH125.root");
    // TFile *fRec = new TFile("/afs/hep.wisc.edu/cms/belknap/dataSamples/acceptanceStudy/ggH125Reco.root");
    
    //TFile *f = new TFile("/afs/hep.wisc.edu/cms/belknap/UWTest/src/UWAnalysis/CRAB/LLLL/analysis.root");
    
    TTree *t = (TTree*)fGen->Get("genlevel/genEventTree");

    int z1l1pdgId;
    int z1l2pdgId;
    int z2l1pdgId;
    int z2l2pdgId;

    double z1l1Pt;
    double z1l2Pt;
    double z2l1Pt;
    double z2l2Pt;

    double z1l1Eta;
    double z1l2Eta;
    double z2l1Eta;
    double z2l2Eta;

    double z1Mass;
    double z2Mass;
    double Mass;

    int EVENT;
    int RUN;
    int LUMI;

    t->SetBranchAddress("z1l1pdgId",&z1l1pdgId);
    t->SetBranchAddress("z1l2pdgId",&z1l2pdgId);
    t->SetBranchAddress("z2l1pdgId",&z2l1pdgId);
    t->SetBranchAddress("z2l2pdgId",&z2l2pdgId);

    t->SetBranchAddress("z1l1Pt",&z1l1Pt);
    t->SetBranchAddress("z1l2Pt",&z1l2Pt);
    t->SetBranchAddress("z2l1Pt",&z2l1Pt);
    t->SetBranchAddress("z2l2Pt",&z2l2Pt);

    t->SetBranchAddress("z1l1Eta",&z1l1Eta);
    t->SetBranchAddress("z1l2Eta",&z1l2Eta);
    t->SetBranchAddress("z2l1Eta",&z2l1Eta);
    t->SetBranchAddress("z2l2Eta",&z2l2Eta);

    t->SetBranchAddress("z1Mass",&z1Mass);
    t->SetBranchAddress("z2Mass",&z2Mass);
    t->SetBranchAddress("hMass",&Mass);

    t->SetBranchAddress("EVENT",&EVENT);
    t->SetBranchAddress("RUN",&RUN);
    t->SetBranchAddress("LUMI",&LUMI);

    int pdgId[4];
    double pt[4];

    // 0: mmmm, 1:eeee, 2:eemm
    int channel;

    vector<string> channelNames;
    channelNames.push_back("MMMM");
    channelNames.push_back("EEEE");
    channelNames.push_back("MMEE");

    vector<string> treeNames;
    treeNames.push_back("muMuMuMuEventTreeFinal");
    treeNames.push_back("eleEleEleEleEventTreeFinal");
    treeNames.push_back("muMuEleEleEventTreeFinal");

    // initialize counts to zero
    int startCounts[] = {0,0,0};
    int massCounts[]  = {0,0,0};
    int etaCounts[]   = {0,0,0};
    int ptCounts[]    = {0,0,0};
    int recoCounts[]  = {0,0,0};
    int higgsCounts[] = {0,0,0};
    
    // create set of identifiers for the reco events
    set<string> eeeeId = genRecoEventIds("eleEleEleEleEventTreeFinal",fRec);
    set<string> mmmmId = genRecoEventIds("muMuMuMuEventTreeFinal",fRec);
    set<string> mmeeId = genRecoEventIds("muMuEleEleEventTreeFinal",fRec);

    int nEntries = t->GetEntries();

    for (int i = 0; i < nEntries; ++i)
    {
        t->GetEntry(i);

        bool mmmm = abs(z1l1pdgId) == 13 && abs(z1l2pdgId) == 13 && abs(z2l1pdgId) == 13 && abs(z2l2pdgId) == 13;
        bool mmee = ( abs(z1l1pdgId) == 11 && abs(z1l2pdgId) == 11 && abs(z2l1pdgId) == 13 && abs(z2l2pdgId) == 13 ) || ( abs(z1l1pdgId) == 13 && abs(z1l2pdgId) == 13 && abs(z2l1pdgId) == 11 && abs(z2l2pdgId) == 11 );
        bool eeee = abs(z1l1pdgId) == 11 && abs(z1l2pdgId) == 11 && abs(z2l1pdgId) == 11 && abs(z2l2pdgId) == 11;

        if (mmmm)
            channel = 0;
        else if (eeee)
            channel = 1;
        else if (mmee)
            channel = 2;
        else
            continue;

        // look at only muons and electrons
        startCounts[channel]++;

        if ( fabs(z1Mass - ZMASS) > fabs(z2Mass - ZMASS) )
        {
            double tmp = z2Mass;
            z2Mass = z1Mass;
            z1Mass = tmp;
        }

        // apply mass cuts to Z1 and Z2
        if ( 40 < z1Mass && z1Mass < 120 && 12 < z2Mass && z2Mass < 120 && 100 < Mass )
        {
            massCounts[channel]++;

            bool l1EtaPass = ( abs(z1l1pdgId) == 11 && abs(z1l1Eta) < 2.5 && abs(z1l2Eta) < 2.5 ) || ( abs(z1l1pdgId) == 13 && abs(z1l1Eta) < 2.4 && abs(z1l2Eta) < 2.4 );
            bool l2EtaPass = ( abs(z2l1pdgId) == 11 && abs(z2l1Eta) < 2.5 && abs(z2l2Eta) < 2.5 ) || ( abs(z2l1pdgId) == 13 && abs(z2l1Eta) < 2.4 && abs(z2l2Eta) < 2.4 );

            // apply eta cuts to leptons
            if ( l1EtaPass && l2EtaPass )
            {
                etaCounts[channel]++;

                // load lepton info into arrays
                pdgId[0] = z1l1pdgId;
                pdgId[1] = z1l2pdgId;
                pdgId[2] = z2l1pdgId;
                pdgId[3] = z2l2pdgId;

                pt[0] = z1l1Pt;
                pt[1] = z1l2Pt;
                pt[2] = z2l1Pt;
                pt[3] = z2l2Pt;

                // apply pt cuts to leptons
                if ( passPtCuts(pt, pdgId) )
                {
                    ptCounts[channel]++;

                    // Higgs phase-space
                    if ( 110 < Mass && Mass < 140 )
                    {
                        higgsCounts[channel]++;
                        // create identifier for current gen event
                        stringstream ss;
                        ss << EVENT << LUMI;

                        // if the set of EEEE identifiers contains the gen identifier,
                        // then the event was reconstructed.
                        if ( eeeeId.count(ss.str()) == 1 )
                            recoCounts[channel]++;

                        if ( mmmmId.count(ss.str()) == 1 )
                            recoCounts[channel]++;

                        if ( mmeeId.count(ss.str()) == 1 )
                            recoCounts[channel]++;
                    }
                }
            }
        }
    }

    int wordWidth = 10;

    // Print the results to the console
    cout << setw(6) << "Name";
    cout << setw(wordWidth) << "BR";
    cout << setw(wordWidth) << "mass";
    cout << setw(wordWidth) << "etaCut";
    cout << setw(wordWidth) << "ptCut";
    cout << setw(wordWidth) << "higgs";
    cout << setw(wordWidth) << "recoMatch";
    cout << setw(wordWidth) << "recoAcc";
    cout << setw(wordWidth) << "recoEff";
    cout << setw(wordWidth) << "yeild";
    cout << endl;

    double lumi = 5.26e3;

    for (int i = 0; i < 3; ++i)
    {
        cout << setw(6) << channelNames.at(i);
        cout << setw(wordWidth) << fixed << setprecision(4) << 100*double(startCounts[i])/double(nEntries);
        cout << setw(wordWidth) << fixed << setprecision(4) << 100*double(massCounts[i])/double(nEntries);
        cout << setw(wordWidth) << fixed << setprecision(4) << 100*double(etaCounts[i])/double(nEntries);
        cout << setw(wordWidth) << fixed << setprecision(4) << 100*double(ptCounts[i])/double(nEntries);
        cout << setw(wordWidth) << fixed << setprecision(4) << 100*double(higgsCounts[i])/double(nEntries);
        cout << setw(wordWidth) << fixed << setprecision(4) << 100*double(recoCounts[i])/double(nEntries);
        cout << setw(wordWidth) << fixed << setprecision(4) << 100*recoEff(channelNames.at(i),treeNames.at(i),fRec);
        cout << setw(wordWidth) << fixed << setprecision(4) << 100*recoEff(channelNames.at(i),treeNames.at(i),fRec)/(double(etaCounts[i])/double(nEntries));
        cout << setw(wordWidth) << fixed << setprecision(4) << recoYield(treeNames.at(i),lumi,fRec);
        cout << endl;
    }
}




/**
 * Calculates the reco efficiency
 *
 * @param histName The name of the histogram. e.g. EEEE, MMEE, etc.
 * @param *f Pointer the the file where the histograms are located
 * @return The reconstruction efficiency
 */
double recoEff(string histName, string treeName, TFile *f)
{
    string hName = histName + "/results";
    string tName = treeName + "/eventTree";
    TH1F* hist = (TH1F*)f->Get(hName.c_str());
    TTree* tree = (TTree*)f->Get(tName.c_str());

    double initEvents = hist->GetBinContent(1);
    // double recoEvents = tree->GetEntries("40 < bestZmass && bestZmass < 120 && 12 < subBestZmass && subBestZmass < 120 && 110 < mass && mass < 140");
    double recoEvents = tree->GetEntries("40 < bestZmass && bestZmass < 120 && 12 < subBestZmass && subBestZmass < 120 && 100 < mass");

    return recoEvents/initEvents;
}


/**
 * Calculates the yields from reco sample
 *
 * @param treeName The name of the tree to process
 * @param lumi Integrated luminosity given in pb-1
 * @param *f The ROOT file of the sample
 * @return The event yield
 */
double recoYield(string treeName, double lumi, TFile *f)
{
    string tName = treeName + "/eventTree";
    TTree* tree = (TTree*)f->Get(tName.c_str());

    int nEntries = tree->GetEntries();

    float weight;
    float bestZmass;
    float subBestZmass;
    float mass;

    tree->SetBranchAddress("__WEIGHT__",&weight);
    tree->SetBranchAddress("bestZmass",&bestZmass);
    tree->SetBranchAddress("subBestZmass",&subBestZmass);
    tree->SetBranchAddress("mass",&mass);

    double yield = 0;

    for (int i = 0; i < nEntries; ++i)
    {
        tree->GetEntry(i);
        if (40 < bestZmass && bestZmass < 120 && 12 < subBestZmass && subBestZmass < 120 && 100 < mass)
            yield += weight;
    }

    return yield*lumi;
}



/**
 * Generates a set of identifies for reconstructed events in the given tree.
 * The identifier is the concatenation of EVENT and LUMI to avoid duplicates.
 */
set<string> genRecoEventIds(string treeName, TFile *f)
{
    string name = treeName + "/eventTree";
    TTree *t = (TTree*)f->Get(name.c_str());

    unsigned int EVENT;
    unsigned int LUMI;

    t->SetBranchAddress("EVENT",&EVENT);
    t->SetBranchAddress("LUMI",&LUMI);

    set<string> ids;

    for (int i = 0; i < t->GetEntries(); ++i)
    {
        t->GetEntry(i);

        stringstream ss;
        ss << EVENT << LUMI;

        ids.insert(ss.str());
    }

    return ids;
}



/**
 * Do the leptons pass the pt cuts?
 *
 * One must pass pt > 20, another pt > 10 (trigger thresholds)
 * and the remaining two must pass pt > 5 if muon and 7 if elec.
 */
bool passPtCuts(double pt[], int pdgId[])
{
    int cutId [] = {0,1,2,3};

    // try all permutations of cuts applied to leptons
    // if a permutation works, then return true
    do
    {
        int l1 = cutId[0];
        int l2 = cutId[1];
        int l3 = cutId[2];
        int l4 = cutId[3];

        if ( pt[l1] > 20 && pt[l2] > 10 && ptCut(pdgId[l3], pt[l3]) && ptCut(pdgId[l4], pt[l4]) )
            return true;
    }
    while ( next_permutation(cutId,cutId+4) );

    return false;
}



/**
 * Does the lepton (mu,e) pass pT cuts?
 */
bool ptCut(int pdgId, double pt)
{
    if ( abs(pdgId) == 11 ) // electrons
    {
        if ( pt > 7 )
            return true;
    }
    else if ( abs(pdgId) == 13 ) // muons
    {
        if ( pt > 5 )
            return true;
    }
    else
        return false;
}
