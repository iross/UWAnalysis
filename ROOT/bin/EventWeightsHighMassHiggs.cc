/**
 * Apply weighiting for high-mass higgs MC samples.
 *
 * This code is based on Tongguang's code for applying high-mass weights.
 *
 * @author D. Austin Belknap
 */
#include <iostream>
#include <algorithm>
#include <cmath>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <unistd.h>

#include "TFile.h"
#include "TMath.h"
#include "TTree.h"

using namespace std;

void applyWeights(TTree *tree, int mass, int sqrts);

int main(int argc, char** argv)
{
    if (argc < 7)
    {
        cout << "Usage: EventWeightsHighMassHiggs -m <mass> -f <file.root> -e <energy = 8 or 7>" << endl;
        return 0;
    }

    // parse command-line arguments
    opterr = 0;

    int mass;
    int sqrts;
    string fileName;
    int c;

    while ((c = getopt (argc, argv, "f:m:")) != -1)
    {
        switch(c)
        {
            case 'f':
                fileName = string(optarg);
                break;

            case 'm':
                mass = atoi(optarg);
                break;

            case 'e':
                sqrts = atoi(optarg);
                break;

            case '?':
                cerr << "Unknown option" << endl;
                return 1;
        }
    }

    TFile *file = new TFile(fileName.c_str());
    TTree* EEEE = (TTree*)file->Get("eleEleEleEleEventTreeFinal/eventTree");
    TTree* MMEE = (TTree*)file->Get("muMuEleEleEventTreeFinal/eventTree");
    TTree* MMMM = (TTree*)file->Get("muMuMuMuEventTreeFinal/eventTree");

    applyWeights(EEEE, mass, sqrts);
    applyWeights(MMEE, mass, sqrts);
    applyWeights(MMMM, mass, sqrts);

    return 0;
}

void applyWeights(TTree *tree, int mass, int sqrts)
{
    // grab the right lineshape file based on mass and sqrt(s)
    stringstream ss;
    ss << "${CMSSW_BASE}/src/UWAnalysis/ROOT/bin/highMassLineshapes/" << "mZZ_Higgs" << mass << "_" << sqrts << "TeV_Lineshape+Interference.txt";
    string shapeFilename = ss.str();

    float weight = 1.0;
    float weightPlus = 1.0;
    float weightMinus = 1.0;
    float hMass;

    // Create new branches
    TBranch *weightBranch      = tree->Branch("__HIGGSWEIGHT__", &weight, "__HIGGSWEIGHT__/F");
    TBranch *weightPlusBranch  = tree->Branch("__HIGGSWEIGHT__Plus", &weightPlus, "__HIGGSWEIGHT__Plus/F");
    TBranch *weightMinusBranch = tree->Branch("__HIGGSWEIGHT__Minus", &weightMinus, "__HIGGSWEIGHT__Minus/F");

    tree->SetBranchAddress("hMass",&hMass);

    // book vectors
    vector<float> weight_;
    vector<float> weightPlus_;
    vector<float> weightMinus_;
    vector<float> bincenters_;

    float bincenter, initial, pow, powp, powm, out, outp, outm;

    ifstream shapeFile(shapeFilename.c_str());
    while( shapeFile.good() )
    {
        shapeFile >> bincenter >> initial >> pow >> powp >> powm >> out >> outp >> outm;

        bincenters_.push_back(bincenter);

        if(initial > 0)
        {
            weight_.push_back(TMath::Max(float(0.0),out/initial));
            weightPlus_.push_back(TMath::Max(float(0.0),outp/initial));
            weightMinus_.push_back(TMath::Max(float(0.0),outm/initial));
        }
        //weights are not defined if initial distribution is 0 => set weight to 0
        else
        {
            weight_.push_back(0.0);
            weightPlus_.push_back(0.0);
            weightMinus_.push_back(0.0);
        }
    }

    int nEntries = tree->GetEntries();
    for (int i = 0; i < nEntries; ++i)
    {
        weight = 1.0;
        weightPlus = 1.0;
        weightMinus = 1.0;

        // set weights to 0 if out of range
        if( hMass < bincenters_.front() || hMass >  bincenters_.back() )
        {
            weight      = 0.0;
            weightPlus  = 0.0;
            weightMinus = 0.0;

            weightBranch->Fill();
            weightPlusBranch->Fill();
            weightMinusBranch->Fill();

            continue;
        }

        vector<float>::iterator low = lower_bound( bincenters_.begin(), bincenters_.end(), hMass ); 
        int lowindex=(low - bincenters_.begin());

        // exact match
        if(hMass == *low )
        {
            weight      = weight_[lowindex];
            weightPlus  = weightPlus_[lowindex];
            weightMinus = weightMinus_[lowindex];
        }
        // linear interpolation
        else
        {
            lowindex--; // lower_bound finds the first element not smaller than X
            weight      = weight_[lowindex]      + (hMass - bincenters_[lowindex] )*(weight_[lowindex + 1] - weight_[lowindex])/(bincenters_[lowindex + 1] - bincenters_[lowindex]);
            weightPlus  = weightPlus_[lowindex]  + (hMass - bincenters_[lowindex] )*(weight_[lowindex + 1] - weight_[lowindex])/(bincenters_[lowindex + 1] - bincenters_[lowindex]);
            weightMinus = weightMinus_[lowindex] + (hMass - bincenters_[lowindex] )*(weight_[lowindex + 1] - weight_[lowindex])/(bincenters_[lowindex + 1] - bincenters_[lowindex]);
        }

        weightBranch->Fill();
        weightPlusBranch->Fill();
        weightMinusBranch->Fill();
    }
    tree->Write("",TObject::kOverwrite);
}
