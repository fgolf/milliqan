{
    gROOT->ProcessLine(".L thresholds.C++");
    gROOT->ProcessLine(".L looper.C++");
    TChain *ch = new TChain("t");
    TString path_to_data = "/Users/fgolf/Dropbox/milliQan/analysis/trees/Run1078_Physics/UX5MilliQan_Run1078.*_Physics.root";
    ch->Add(path_to_data);
    std::string outfile = "test.root";
    std::string evt_categories[] = {"All","SPE","Small","SmallTag","Cosmic","CosmicTag","Thru","ThruTag"};
    std::string lhc_statuses[] = {"Beam","NoBeam"};
    std::string range_codes[] = {"A","B","C","D"};
    int run_number = 1078;
    tree1r(ch,outfile,evt_categories[0],lhc_statuses[0],range_codes[0],run_number);
    tree1r(ch,outfile,evt_categories[4],lhc_statuses[0],range_codes[0],run_number);
    tree1r(ch,outfile,evt_categories[5],lhc_statuses[0],range_codes[0],run_number);
}
