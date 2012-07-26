void zzAcceptance()
{
    TFile *f = new TFile("/scratch/belknap/ZZGenLvl.root");
    
    TTree *t = (TTree*)f->Get("genlevel/genEventTree");

    // examine only electrons and muons
    std::string selection = "(abs(z1l1pdgId) == 11 || abs(z1l1pdgId) == 13) && (abs(z2l1pdgId) == 11 || abs(z2l1pdgId) == 13)";
    std::cout << "Starting Events: " << t->GetEntries(selection.c_str()) << std::endl;
    
    // apply mass cuts to both Z's
    selection += "&& 60 < z1Mass && z1Mass < 120 && 60 < z2Mass && z2Mass < 120";
    std::cout << "    Z Mass Cuts: " << t->GetEntries(selection.c_str()) << std::endl;

    // apply eta cuts to daughter leptons
    selection += "&& ( ( abs(z1l1pdgId) == 11 && abs(z1l1Eta) < 2.5 && abs(z1l2Eta) < 2.5 ) || ( abs(z2l1pdgId) == 13 && abs(z2l1Eta) < 2.4 && abs(z2l2Eta) < 2.4 ) )";
    std::cout << "        Eta Cut: " << t->GetEntries(selection.c_str()) << std::endl;

    //selection += "&& (";
    //selection += "( z1l1Pt > 20 && z1l2Pt > 10 && abs(z2l1pdgId) == 11 && z2l1Pt > 7 && z2l2Pt > 7 ) ||";
    //selection += "( z1l1Pt > 20 && z1l2Pt > 10 && abs(z2l1pdgId) == 13 && z2l1Pt > 5 && z2l2Pt > 5 ) ||";

    //selection += "( z1l1Pt > 20 && abs(z1l2pdgId) == 11 && z1l2Pt > 7 && z2l1Pt > 10 && abs(z2l2pdgId) == 11 && z2l2Pt > 7 ) ||";
    //selection += "( z1l1Pt > 20 && abs(z1l2pdgId) == 11 && z1l2Pt > 7 && z2l1Pt > 10 && abs(z2l2pdgId) == 13 && z2l2Pt > 5 ) ||";
    //selection += "( z1l1Pt > 20 && abs(z1l2pdgId) == 13 && z1l2Pt > 5 && z2l1Pt > 10 && abs(z2l2pdgId) == 11 && z2l2Pt > 7 ) ||";
    //selection += "( z1l1Pt > 20 && abs(z1l2pdgId) == 13 && z1l2Pt > 5 && z2l1Pt > 10 && abs(z2l2pdgId) == 13 && z2l2Pt > 5 ) ||";

    //selection += "( z1l1Pt > 20 && abs(z1l2pdgId) == 11 && z1l2Pt > 7 && z2l1Pt > 10 && abs(z2l2pdgId) == 11 && z2l2Pt > 7 ) ||";
    //selection += "( z1l1Pt > 20 && abs(z1l2pdgId) == 11 && z1l2Pt > 7 && z2l1Pt > 10 && abs(z2l2pdgId) == 13 && z2l2Pt > 5 ) ||";
    //selection += "( z1l1Pt > 20 && abs(z1l2pdgId) == 13 && z1l2Pt > 5 && z2l1Pt > 10 && abs(z2l2pdgId) == 11 && z2l2Pt > 7 ) ||";
    //selection += "( z1l1Pt > 20 && abs(z1l2pdgId) == 13 && z1l2Pt > 5 && z2l1Pt > 10 && abs(z2l2pdgId) == 13 && z2l2Pt > 5 ) ||";

    int z1l1pdgId;
    int z1l2pdgId;
    int z2l1pdgId;
    int z2l2pdgId;

    double z1l1Pt;
    double z1l2Pt;
    double z2l1Pt;
    double z2l2Pt;

    t->SetBranchAddress("z1l1Pt",&z1l1Pt);
    t->SetBranchAddress("z1l2Pt",&z1l2Pt);
    t->SetBranchAddress("z2l1Pt",&z2l1Pt);
    t->SetBranchAddress("z2l2Pt",&z2l2Pt);

    t->SetBranchAddress("z1l1pdgId",&z1l1pdgId);
    t->SetBranchAddress("z1l2pdgId",&z1l2pdgId);
    t->SetBranchAddress("z2l1pdgId",&z2l1pdgId);
    t->SetBranchAddress("z2l2pdgId",&z2l2pdgId);

    int pdgId[4];
    double pt[4];

    // permutations of the indicies for the four leptons
    int cutId [] = {1234,1243,1324,1342,1423,1432,2134,2143,2314,2341,2413,2431,3124,3142,3214,3241,3412,3421,4123,4132,4213,4231,4312,4321};

    int counts = 0;

    for (int i = 0; i < t->GetEntries(selection.c_str()); ++i)
    {
        t->GetEntry(i);

        // load lepton info into arrays
        pdgId[0] = z1l1pdgId;
        pdgId[1] = z1l2pdgId;
        pdgId[2] = z2l1pdgId;
        pdgId[3] = z2l2pdgId;

        pt[0] = z1l1Pt;
        pt[1] = z1l2Pt;
        pt[2] = z2l1Pt;
        pt[3] = z2l2Pt;

        // loop over permutations
        for (int j = 0; j < 24; ++j)
        {
            // extract indicies
            int id      = cutId[j];
            int first   = id%10; id /= 10;
            int second  = id%10; id /= 10;
            int third   = id%10; id /= 10;
            int fourth  = id%10;

            // Update counts if pT cuts are passed
            if ( pt[first] > 20 && pt[second] > 10 && ptCut(pdgId[third], pt[third]) && ptCut(pdgId[fourth], pt[fourth]) )
            {
                count++;
                break;
            }
        }
    }

    std::cout << "         pT Cut: " << counts << std::endl;
}

// does lepton pass pT cut?
bool ptCut(int pdgId, double pt)
{
    if ( pdgId == 11 || pdgId == -11 ) // electrons
    {
        if ( pt > 7 )
            return true;
    }
    else if ( pdgId == 13 || pdgId == -13 ) // muons
    {
        if ( pt > 5 )
            return true;
    }
    else
        return false;
}
