/**
 * zzAcceptance.cc
 *
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

bool ptCut(int pdgId, double pt);
void zzAcceptance();
bool passPtCuts(double pt[], int pdgId[]);
set<string> genRecoEventIds(string treeName, TFile *f);
double recoEff(string histName, TFile *f);



int main()
{
    zzAcceptance();

    return 0;
}



void zzAcceptance()
{
    TFile *fGen = new TFile("/afs/hep.wisc.edu/cms/belknap/dataSamples/ZZGenLvl.root"); // gen level events only
    TFile *fRec = new TFile("/afs/hep.wisc.edu/cms/belknap/dataSamples/ZZGenReco.root"); // Reconstructed Monte Carlo
    
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

    // initialize counts to zero
    int startCounts[] = {0,0,0};
    int massCounts[]  = {0,0,0};
    int etaCounts[]   = {0,0,0};
    int ptCounts[]    = {0,0,0};
    int recoCounts[]  = {0,0,0};
    
    // create set of identifiers for the reco events
    set<string> eeeeId = genRecoEventIds("eleEleEleEleEventTree",fRec);

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

        // apply mass cuts to Z1 and Z2
        if ( 60 < z1Mass && z1Mass < 120 && 60 < z2Mass && z2Mass < 120 )
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

                    // create identifier for current gen event
                    stringstream ss;
                    ss << EVENT << LUMI;

                    // if the set of EEEE identifiers contains the gen identifier,
                    // then the event was reconstructed.
                    if ( eeeeId.count(ss.str()) == 1 )
                        recoCounts[channel]++;
                }
            }
        }
    }

    // Print the results to the console
    cout << setw(6) << "Name";
    cout << setw(10) << "BR";
    cout << setw(10) << "mass";
    cout << setw(10) << "etaCut";
    cout << setw(10) << "ptCut";
    cout << setw(10) << "recoMatch";
    cout << setw(10) << "recoEf";
    cout << endl;

    for (int i = 0; i < 3; ++i)
    {
        cout << setw(6) << channelNames.at(i);
        cout << setw(10) << fixed << setprecision(3) << double(startCounts[i])/double(nEntries);
        cout << setw(10) << fixed << setprecision(3) << double(massCounts[i])/double(nEntries);
        cout << setw(10) << fixed << setprecision(3) << double(etaCounts[i])/double(nEntries);
        cout << setw(10) << fixed << setprecision(3) << double(ptCounts[i])/double(nEntries);
        cout << setw(10) << fixed << setprecision(3) << double(recoCounts[i])/double(nEntries);
        cout << setw(10) << fixed << setprecision(3) << recoEff(channelNames.at(i),fRec);
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
double recoEff(string histName, TFile *f)
{
    string name = histName + "/results";
    TH1F* hist = (TH1F*)f->Get(name.c_str());

    double initEvents = hist->GetBinContent(1);
    double recoEvents = hist->GetBinContent(hist->GetMinimumBin());

    return recoEvents/initEvents;
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
 * One must pass pt > 20, another pt > 10,
 * and the remaining two must pass pt > 5 if muon and 7 if elec.
 */
bool passPtCuts(double pt[], int pdgId[])
{
    int cutId [] = {0,1,2,3};

    // try all permutations of cuts applied to leptons
    // if permutation works, then return true
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
 * Does the lepton (mu,e) pass trig. threshold?
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
