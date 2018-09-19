//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Oct  6 22:01:07 2017 by ROOT version 5.34/36
// from TTree t/t
// found on file: UX5MilliQan_Run25.root
//////////////////////////////////////////////////////////

#include <fstream>

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TString.h>

struct ChannelInfo {
    int chan;
    int layer;
    int row;
    int col;
    int type; 
    ChannelInfo() : chan(-99), layer(-99), row(-99), col(-99), type(-99) {}
    ChannelInfo(int ch) : chan(ch) {this->SetChannel(ch);}
    ChannelInfo(int l, int r, int c, int t) : layer(l), row(r), col(c), type(t) {this->SetLocation(l,r,c,t);}
    ChannelInfo(int ch, int l, int r, int c, int t) : chan(ch), layer(l), row(r), col(c), type(t) {}
    void SetChannel (int ch);
    void SetLocation(int layer, int row, int col, int type);
    int channelNumber ();
    static int channelNumber (int layer, int row, int col, int type);
    ChannelInfo channelLocation ();
    static ChannelInfo channelLocation (int ch);
    std::vector<ChannelInfo> neighbors();
    static std::vector<ChannelInfo> neighbors(int ch);
    static std::vector<ChannelInfo> neighbors(int l, int r, int c, int t);
};

void InitializeChain(TChain *fChain);
int bookHistograms(TString EventCategory, TString LHCStatus, TString RangeCode, int nentries, int maxFile, double minTime, double maxTime);
bool isGoodEvent(int nHits, bool *HitChan, float *maxSample, TString EventCategory, TString LHCStatus, int RunNum);
void NeighborHitMap(bool *NeighborHit, bool HitChan[], int RunNum, TString EventCategory);
int GetEventCategoryCode(TString EventCategoryName);

// Declaration of leaf types
Int_t           event;
Int_t           run;
Int_t           filenum;
Int_t           fillnum;
Bool_t          beam;
Float_t         fillAvgLumi;
Int_t           nRollOvers;
Bool_t          present_b0;
Bool_t          present_b1;
Long64_t        event_time_b0;
Long64_t        event_time_b1;
Double_t        event_time_fromTDC;
Int_t           t_since_fill_start;
string          *event_t_string;
Long64_t        event_trigger_time_tag_b0;
Long64_t        event_trigger_time_tag_b1;
vector<int>     *chan;
vector<float>   *triggerCandidates;
vector<float>   *triggerCandidatesEnd;
vector<int>     *triggerCandidatesChannel;
vector<int>     *layer;
vector<int>     *row;
vector<int>     *column;
vector<int>     *type;
vector<float>   *height;
vector<float>   *ptime;
vector<float>   *time_module_calibrated;
vector<float>   *delay;
vector<float>   *area;
vector<float>   *nPE;
vector<int>     *ipulse;
vector<int>     *npulses;
vector<float>   *duration;
vector<bool>    *quiet;
vector<float>   *presample_mean;
vector<float>   *presample_RMS;
vector<float>   *sideband_mean;
vector<float>   *sideband_RMS;
vector<Long64_t> *groupTDC_b0;
vector<Long64_t> *groupTDC_b1;
vector<float>   *bx;
vector<float>   *by;
vector<float>   *bz;
vector<float>   *max_sample;
vector<float>   *min_sample;

// List of branches
TBranch        *b_event;   //!
TBranch        *b_run;   //!
TBranch        *b_filenum;   //!
TBranch        *b_fillnum;   //!
TBranch        *b_nRollOvers;   //!
TBranch        *b_beam;   //!
TBranch        *b_fillAvgLumi;   //!
TBranch        *b_present_b0;   //!
TBranch        *b_present_b1;   //!
TBranch        *b_event_time_b0;   //!
TBranch        *b_event_time_b1;   //!
TBranch        *b_event_time_fromTDC;   //!
TBranch        *b_t_since_fill_start;   //!
TBranch        *b_event_t_string;   //!
TBranch        *b_event_trigger_time_tag_b0;   //!
TBranch        *b_event_trigger_time_tag_b1;   //!
TBranch        *b_chan;   //!
TBranch        *b_triggerCandidates;   //!
TBranch        *b_triggerCandidatesEnd;   //!
TBranch        *b_triggerCandidatesChannel;   //!
TBranch        *b_layer;   //!
TBranch        *b_row;   //!
TBranch        *b_column;   //!
TBranch        *b_type;   //!
TBranch        *b_height;   //!
TBranch        *b_ptime;   //!
TBranch        *b_time_module_calibrated;   //!
TBranch        *b_delay;   //!
TBranch        *b_area;   //!
TBranch        *b_nPE;   //!
TBranch        *b_ipulse;   //!
TBranch        *b_npulses;   //!
TBranch        *b_duration;   //!
TBranch        *b_quiet;   //!
TBranch        *b_presample_mean;   //!
TBranch        *b_presample_RMS;   //!
TBranch        *b_sideband_mean;   //!
TBranch        *b_sideband_RMS;   //!
TBranch        *b_groupTDC_b0;   //!
TBranch        *b_groupTDC_b1;   //!
TBranch        *b_bx;   //!
TBranch        *b_by;   //!
TBranch        *b_bz;   //!
TBranch        *b_max;   //!
TBranch        *b_min;   //!

// Record the number of events with specific hit patterns. 
// These are used to validate the trigger efficiency.
// In particular, I count events with vertical cosmic like hits, two layer hits, and three layer hits.
// These are calculated and reported for each event category, which corresponds to different channel thresholds.
// First define the digitizer 0 sets, 2 hits and then 3 hits
int nCH0CH8; // Within a layer 
int nCH1CH9; 
int nCH0CH9;
int nCH1CH8;
int nCH6CH12; 
int nCH7CH13; 
int nCH6CH13; 
int nCH7CH12;
int nCH2CH4; 
int nCH3CH5; 
int nCH2CH5; 
int nCH3CH4; 
int nCH0CH6;   // Between layers
int nCH1CH7;
int nCH0CH7;
int nCH1CH6;
int nCH8CH12;
int nCH9CH13;
int nCH8CH13;
int nCH9CH12;
int nCH0CH12;
int nCH1CH13;
int nCH0CH13;
int nCH1CH12;
int nCH8CH6;
int nCH9CH7;
int nCH8CH7;
int nCH9CH6;
int nCH6CH2;
int nCH7CH3;
int nCH6CH3;
int nCH7CH2;
int nCH12CH4;
int nCH13CH5;
int nCH12CH5;
int nCH13CH4;
int nCH6CH4;
int nCH7CH5;
int nCH6CH5;
int nCH7CH4;
int nCH12CH2;
int nCH13CH3;
int nCH12CH3;
int nCH13CH2;
int nCH0CH8CH10; // 3 hits per layer
int nCH1CH9CH10;
int nCH0CH9CH10;
int nCH1CH8CH10;
int nCH6CH12CH30;
int nCH7CH13CH30;
int nCH2CH4CH14;
int nCH3CH5CH14;
int nCH2CH5CH14;
int nCH3CH4CH14;
int nCH0CH6CH2; // Hits across 3 layers
int nCH1CH7CH3;
int nCH0CH6CH3;
int nCH1CH7CH2;
int nCH0CH7CH2;
int nCH1CH6CH3;
int nCH8CH12CH4;
int nCH9CH13CH5;
int nCH8CH12CH5;
int nCH9CH13CH4;
int nCH8CH13CH4;
int nCH9CH12CH5;
int nCH0CH6CH4;
int nCH0CH6CH5;
int nCH1CH7CH5;
int nCH1CH7CH4;
// Now define the digitizer 1 sets, 2 hits and then 3 hits
int nCH11CH8; // Two hits in digitizer 1...
int nCH11CH9; 
int nCH13CH8; 
int nCH13CH9;
int nCH16CH30;
int nCH17CH30;
int nCH16CH19;
int nCH17CH19;
int nCH22CH15;
int nCH23CH15;
int nCH22CH10;
int nCH23CH10;
int nCH27CH24CH29; // Three hits within a layer
int nCH27CH25CH29;
int nCH30CH16CH19;
int nCH30CH17CH19;
int nCH31CH22CH26;
int nCH31CH23CH26;
int nCH24CH16CH22; // Hits across 3 layers
int nCH24CH16CH23;
int nCH24CH17CH23;
int nCH24CH17CH22;
int nCH25CH17CH23;
int nCH25CH16CH23;
int nCH25CH16CH22;
int nCH18CH20; // Two hits between slabs
int nCH20CH28;
int nCH28CH21;
int nCH18CH28;
int nCH20CH21;
int nCH18CH21;
int nCH18CH20CH28; // Hits across slab layers
int nCH20CH28CH21;
int nCH18CH20CH28CH21; 
int nCH18CH20CH28CH21CH0CH6CH2; // Thru-going
int nCH18CH20CH28CH21CH1CH7CH3;
int nCH18CH20CH28CH21CH24CH16CH22;
int nCH18CH20CH28CH21CH25CH17CH23;
int nCH18CH20CH28CH21CH12CH4;
int nCH18CH20CH28CH21CH9CH13CH5;
int nAllSlabsAllLayers; // All Slabs and a hit somewhere in each layer
int nAllSlabsAnyLayer; // All Slabs and a hit somewhere in any layer
int nAllLayersAnySlab; // All layers with at least one hit, and at least one slab hit

// Histogram names are Cuts_LHCStatus_Variable_Chan_Range
TH1D *h_Max[32];
TH1D *h_AfterPulseArea[32];
TH1D *h_AfterPulseHeight[32];
TH1D *h_AfterPulseDuration[32];
TH1D *h_FirstPulseArea[32];
TH1D *h_FirstPulseNPE[32];
TH1D *h_AfterPulseTime[32];
TH1D *h_FirstPulseHeight[32];
TH1D *h_FirstDuration[32];
TH1D *h_FirstTime[32];
TH1D *h_LHCTime[32];
TH1D *h_LHCTimeCalib[32];
TH1D *h_TimeWRTCH18[32];
TH1D *h_TimeCalibWRTCH18[32];
TH1D *h_TimeWRTCH20[32];
TH1D *h_TimeCalibWRTCH20[32];
TH1D *h_TimeWRTCH28[32];
TH1D *h_TimeCalibWRTCH28[32];
TH1D *h_TimeWRTCH21[32];
TH1D *h_TimeCalibWRTCH21[32];
TH1D *h_TimeWRTCH7[32];
TH1D *h_TimeCalibWRTCH7[32];
TH1D *h_TimeWRTCH0[32];
TH1D *h_TimeCalibWRTCH0[32];
TH1D *h_TimeWRTCH1[32];
TH1D *h_TimeCalibWRTCH1[32];
TH1D *h_TimeWRTCH2[32];
TH1D *h_TimeCalibWRTCH2[32];
TH1D *h_TimeWRTCH3[32];
TH1D *h_TimeCalibWRTCH3[32];
TH1D *h_TimeWRTCH4[32];
TH1D *h_TimeCalibWRTCH4[32];
TH1D *h_TotalPulseArea[32];
TH1D *h_NPulses[32];
TH1D *h_NPairedHits[32];
TH1D *h_NTripletHits;
TH1D *h_NTripletHits3;
TH1D *h_NTripletHits4;
TH1D *h_NHitBars;
TH1D *h_NHitLayers;
TH1D *h_TotalGlobalPulseArea;
TH1D *h_EventNumberUnsynched;
TH1D *h_EventTime[32];
TH1D *h_EventTimeSeconds[32];
TH1D *h_EventTimeSynchedSeconds[32];
TH1D *h_EventTimeUnsynchedSeconds[32];
TH1D *h_FileNum[32];
TH1D *h_SidebandMean[32];
TH1D *h_SidebandRMS[32];
TH1D *h_TaggedMax[32];
TH1D *h_TaggedPulseArea[32];
TH1D *h_TaggedPulseNPE[32];
TH1D *h_TaggedTotalPulseArea[32];
TH1D *h_TaggedPulseHeight[32];
TH1D *h_TaggedDuration[32];
TH1D *h_TripleLayerMax[32];
TH1D *h_DoubleLayerMax[32];

TH1D *h_pulseHeight[32];
TH1D *h_pulseArea[32];
TH1D *h_pulseDuration[32];
TH1D *h_pulseNPE[32];
TH1D *h_pulseTime[32];
TH1D *h_firstPulseHeight[32];
TH1D *h_firstPulseArea[32];
TH1D *h_firstPulseDuration[32];
TH1D *h_firstPulseNPE[32];
TH1D *h_firstPulseTime[32];
TH1D *h_maxPulseHeight[32];
TH1D *h_maxPulseArea[32];
TH1D *h_maxPulseDuration[32];
TH1D *h_maxPulseNPE[32];
TH1D *h_maxPulseTime[32];
TH1D *h_npulsesPerChannel[32];
TH1D *h_nhitsPerChannel[32];
TH1D *h_diffTimeWithNeighboringMaxHit[32];
TH1D *h_diffTimeWithNeighboringMaxHitCalibrated[32];
TH1D *h_npulses[32];
TH1D *h_nhits[32];
TH1D *h_nchannelsWithAtLeastOnePulse[32];
TH1D *h_nchannelsWithAtLeastOneHit[32];
TH1D *h_ncosmics;

void InitializeChain(TChain *fChain)
{
   // Set object pointer
   event_t_string = 0;
   chan = 0;
   height = 0;
   ptime = 0;
   area = 0;
   ipulse = 0;
   npulses = 0;
   duration = 0;
   sideband_mean = 0;
   sideband_RMS = 0;
   bx = 0;
   by = 0;
   bz = 0;

   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("run", &run, &b_run);
   fChain->SetBranchAddress("file", &filenum, &b_filenum);
   fChain->SetBranchAddress("fill", &fillnum, &b_fillnum);
   fChain->SetBranchAddress("nRollOvers", &nRollOvers, &b_nRollOvers);
   fChain->SetBranchAddress("beam", &beam, &b_beam);
   fChain->SetBranchAddress("fillAvgLumi", &fillAvgLumi, &b_fillAvgLumi);
   fChain->SetBranchAddress("present_b0", &present_b0, &b_present_b0);
   fChain->SetBranchAddress("present_b1", &present_b1, &b_present_b1);
   fChain->SetBranchAddress("event_time_b0", &event_time_b0, &b_event_time_b0);
   fChain->SetBranchAddress("event_time_b1", &event_time_b1, &b_event_time_b1);
   fChain->SetBranchAddress("event_time_fromTDC", &event_time_fromTDC, &b_event_time_fromTDC);
   fChain->SetBranchAddress("t_since_fill_start", &t_since_fill_start, &b_t_since_fill_start);
   fChain->SetBranchAddress("event_t_string", &event_t_string, &b_event_t_string);
   fChain->SetBranchAddress("event_trigger_time_tag_b0", &event_trigger_time_tag_b0, &b_event_trigger_time_tag_b0);
   fChain->SetBranchAddress("event_trigger_time_tag_b1", &event_trigger_time_tag_b1, &b_event_trigger_time_tag_b1);
   fChain->SetBranchAddress("chan", &chan, &b_chan);
   fChain->SetBranchAddress("triggerCandidates", &triggerCandidates, &b_triggerCandidates);
   fChain->SetBranchAddress("triggerCandidatesEnd", &triggerCandidatesEnd, &b_triggerCandidatesEnd);
   fChain->SetBranchAddress("triggerCandidatesChannel", &triggerCandidatesChannel, &b_triggerCandidatesChannel);
   fChain->SetBranchAddress("layer", &layer, &b_layer);
   fChain->SetBranchAddress("row", &row, &b_row);
   fChain->SetBranchAddress("column", &column, &b_column);
   fChain->SetBranchAddress("type", &type, &b_type);
   fChain->SetBranchAddress("height", &height, &b_height);
   fChain->SetBranchAddress("time", &ptime, &b_ptime);
   fChain->SetBranchAddress("time_module_calibrated", &time_module_calibrated, &b_time_module_calibrated);
   fChain->SetBranchAddress("delay", &delay, &b_delay);
   fChain->SetBranchAddress("area", &area, &b_area);
   fChain->SetBranchAddress("nPE", &nPE, &b_nPE);
   fChain->SetBranchAddress("ipulse", &ipulse, &b_ipulse);
   fChain->SetBranchAddress("npulses", &npulses, &b_npulses);
   fChain->SetBranchAddress("duration", &duration, &b_duration);
   fChain->SetBranchAddress("quiet", &quiet, &b_quiet);
   fChain->SetBranchAddress("presample_mean", &presample_mean, &b_presample_mean);
   fChain->SetBranchAddress("presample_RMS", &presample_RMS, &b_presample_RMS);
   fChain->SetBranchAddress("sideband_mean", &sideband_mean, &b_sideband_mean);
   fChain->SetBranchAddress("sideband_RMS", &sideband_RMS, &b_sideband_RMS);
   fChain->SetBranchAddress("groupTDC_b0", &groupTDC_b0, &b_groupTDC_b0);
   fChain->SetBranchAddress("groupTDC_b1", &groupTDC_b1, &b_groupTDC_b1);
   fChain->SetBranchAddress("max", &max_sample, &b_max);
   fChain->SetBranchAddress("min", &min_sample, &b_min);
   fChain->SetBranchAddress("bx", &bx, &b_bx);
   fChain->SetBranchAddress("by", &by, &b_by);
   fChain->SetBranchAddress("bz", &bz, &b_bz);
}

void reset_counters () {
    nCH0CH8=0; // Within a layer
    nCH1CH9=0; 
    nCH0CH9=0;
    nCH1CH8=0;
    nCH6CH12=0; 
    nCH7CH13=0; 
    nCH6CH13=0; 
    nCH7CH12=0;
    nCH2CH4=0; 
    nCH3CH5=0; 
    nCH2CH5=0; 
    nCH3CH4=0; 
    nCH0CH6=0;   // Between layers
    nCH1CH7=0;
    nCH0CH7=0;
    nCH1CH6=0;
    nCH8CH12=0;
    nCH9CH13=0;
    nCH8CH13=0;
    nCH9CH12=0;
    nCH0CH12=0;
    nCH1CH13=0;
    nCH0CH13=0;
    nCH1CH12=0;
    nCH8CH6=0;
    nCH9CH7=0;
    nCH8CH7=0;
    nCH9CH6=0;
    nCH6CH2=0;
    nCH7CH3=0;
    nCH6CH3=0;
    nCH7CH2=0;
    nCH12CH4=0;
    nCH13CH5=0;
    nCH12CH5=0;
    nCH13CH4=0;
    nCH6CH4=0;
    nCH7CH5=0;
    nCH6CH5=0;
    nCH7CH4=0;
    nCH12CH2=0;
    nCH13CH3=0;
    nCH12CH3=0;
    nCH13CH2=0;
    nCH0CH8CH10=0; // 3 hits per layer
    nCH1CH9CH10=0;
    nCH0CH9CH10=0;
    nCH1CH8CH10=0;
    nCH6CH12CH30=0;
    nCH7CH13CH30=0;
    nCH2CH4CH14=0;
    nCH3CH5CH14=0;
    nCH2CH5CH14=0;
    nCH3CH4CH14=0;
    nCH0CH6CH2=0; // Hits across 3 layers
    nCH1CH7CH3=0;
    nCH0CH6CH3=0;
    nCH1CH7CH2=0;
    nCH0CH7CH2=0;
    nCH1CH6CH3=0;
    nCH8CH12CH4=0;
    nCH9CH13CH5=0;
    nCH8CH12CH5=0;
    nCH9CH13CH4=0;
    nCH8CH13CH4=0;
    nCH9CH12CH5=0;
    nCH0CH6CH4=0;
    nCH0CH6CH5=0;
    nCH1CH7CH5=0;
    nCH1CH7CH4=0;
    // now define the digitizer 1 sets, 2 hits and then 3 hits
    nCH11CH8=0; // Two hits in digitizer 1...
    nCH11CH9=0; 
    nCH13CH8=0; 
    nCH13CH9=0;
    nCH16CH30=0;
    nCH17CH30=0;
    nCH16CH19=0;
    nCH17CH19=0;
    nCH22CH15=0;
    nCH23CH15=0;
    nCH22CH10=0;
    nCH23CH10=0;
    nCH27CH24CH29=0; // Three hits within a layer
    nCH27CH25CH29=0;
    nCH30CH16CH19=0;
    nCH30CH17CH19=0;
    nCH31CH22CH26=0;
    nCH31CH23CH26=0;
    nCH24CH16CH22=0; // Hits across 3 layers
    nCH24CH16CH23=0;
    nCH24CH17CH23=0;
    nCH24CH17CH22=0;
    nCH25CH17CH23=0;
    nCH25CH16CH23=0;
    nCH25CH16CH22=0;
    nCH18CH20=0; // Two hits between slabs
    nCH20CH28=0;
    nCH28CH21=0;
    nCH18CH28=0;
    nCH20CH21=0;
    nCH18CH21=0;
    nCH18CH20CH28=0; // Hits across slab layers
    nCH20CH28CH21=0;
    nCH18CH20CH28CH21=0; 
    nCH18CH20CH28CH21CH0CH6CH2=0; // Thru-going
    nCH18CH20CH28CH21CH1CH7CH3=0;
    nCH18CH20CH28CH21CH24CH16CH22=0;
    nCH18CH20CH28CH21CH25CH17CH23=0;
    nCH18CH20CH28CH21CH12CH4=0;
    nCH18CH20CH28CH21CH9CH13CH5=0;
    nAllSlabsAllLayers=0; // All Slabs and a hit somewhere in each layer
    nAllSlabsAnyLayer=0; // All Slabs and a hit somewhere in any layer
    nAllLayersAnySlab=0; // All layers with at least one hit, and at least one slab hit
}

void ChannelInfo::SetChannel(int ch) {
    this->chan = ch;
    ChannelInfo tmp = this->channelLocation();
    this->layer = tmp.layer;
    this->row = tmp.row;
    this->col = tmp.col;
    this->type = tmp.type;
}

void ChannelInfo::SetLocation(int layer, int row, int col, int type) {
    this->layer= layer;
    this->row  = row;
    this->col  = col;
    this->type = type;
    this->chan = this->channelNumber();
}

int ChannelInfo::channelNumber () {
    if (this->chan > -99) return this->chan;
    else return this->channelNumber(this->layer,this->row,this->col,this->type); 
}

int ChannelInfo::channelNumber(int layer, int row, int col, int type) {
    if (type==0) {
        if (layer==1) {
            if (col==1) {
                if (row==1) return 8;
                if (row==2) return 24;
                if (row==3) return 0;
            }
            if (col==2) {
                if (row==1) return 9;
                if (row==2) return 25;
                if (row==3) return 1;
            }
        }
        if (layer==2) {
            if (col==1) {
                if (row==1) return 12;
                if (row==2) return 16;
                if (row==3) return 6;
            }
            if (col==2) {
                if (row==1) return 13;
                if (row==2) return 17;
                if (row==3) return 7;
            }
        }
        if (layer==3) {
            if (col==1) {
                if (row==1) return 4;
                if (row==2) return 22;
                if (row==3) return 2;
            }
            if (col==2) {
                if (row==1) return 5;
                if (row==2) return 23;
                if (row==3) return 3;
            }
        }
    }
    if (type==1) {
        if (layer==0) return 18;
        if (layer==1) return 20;
        if (layer==2) return 28;
        if (layer==3) return 21;
    }
    if (type==2) {
        if (layer==1) {
            if (col==-1) return 27;
            if (col==0) return 10;
            if (col==1) return 29;
        }
        if (layer==2) {
            if (col==-1) return 11;
            if (col==0) return 30;
            if (col==1) return 19;
        }
        if (layer==3) {
            if (col==-1) return 31;
            if (col==0) return 14;
            if (col==1) return 26;
        }
    }
}

ChannelInfo ChannelInfo::channelLocation() {
    if (this->layer > -99 and this->row > -99 and this->col > -99 and this->type > -99)
        return *this;
    else
        return this->channelLocation(this->chan); 
}

ChannelInfo ChannelInfo::channelLocation(int ch) {
    // ChannelInfo(channel, layer, row, col, type)
    if (ch == 0 ) return ChannelInfo(0 ,1,3,1,0);
    if (ch == 1 ) return ChannelInfo(1 ,1,3,2,0);
    if (ch == 2 ) return ChannelInfo(2 ,3,3,1,0);
    if (ch == 3 ) return ChannelInfo(3 ,3,3,2,0);
    if (ch == 4 ) return ChannelInfo(4 ,3,1,1,0);
    if (ch == 5 ) return ChannelInfo(5 ,3,1,2,0);
    if (ch == 6 ) return ChannelInfo(6 ,2,3,6,0);
    if (ch == 7 ) return ChannelInfo(7 ,2,3,2,0);
    if (ch == 8 ) return ChannelInfo(8 ,1,1,1,0);
    if (ch == 9 ) return ChannelInfo(9 ,1,1,2,0);
    if (ch == 10) return ChannelInfo(10,1,-2,0,2);
    if (ch == 11) return ChannelInfo(11,2,-2,-1,2);
    if (ch == 12) return ChannelInfo(12,2,1,1,0);
    if (ch == 13) return ChannelInfo(13,2,1,2,0);
    if (ch == 14) return ChannelInfo(14,3,-2,0,2);
    if (ch == 15) return ChannelInfo(15,-99,-1,0,0);
    if (ch == 16) return ChannelInfo(16,2,2,1,0);
    if (ch == 17) return ChannelInfo(17,2,2,2,0);
    if (ch == 18) return ChannelInfo(18,0,-1,0,1);
    if (ch == 19) return ChannelInfo(19,2,-2,1,2);
    if (ch == 20) return ChannelInfo(20,1,-1,0,1);
    if (ch == 21) return ChannelInfo(21,3,-1,0,1);
    if (ch == 22) return ChannelInfo(22,3,2,1,0);
    if (ch == 23) return ChannelInfo(23,3,2,2,0);
    if (ch == 24) return ChannelInfo(24,1,2,1,0);
    if (ch == 25) return ChannelInfo(25,1,2,2,0);
    if (ch == 26) return ChannelInfo(26,3,-2,1,2);
    if (ch == 27) return ChannelInfo(27,1,-2,-1,2);
    if (ch == 28) return ChannelInfo(28,2,-1,0,1);
    if (ch == 29) return ChannelInfo(29,1,-2,1,2);
    if (ch == 30) return ChannelInfo(30,2,-2,0,2);
    if (ch == 31) return ChannelInfo(31,3,-2,-1,2);
}

std::vector<ChannelInfo> ChannelInfo::neighbors()
{
    std::vector<ChannelInfo> ret;
    int l = this->layer;
    int r = this->row;
    int c = this->col;
    int t = this->type;
    
    // bars first
    if (t==0) { 
        for (int i=1;i<=3;i++) {
            if (i==r) continue;
            ret.push_back(ChannelInfo(layer,i,c,0));
        }
        ret.push_back(ChannelInfo(layer,-2,0,2));
    }
    return ret;
}

std::vector<ChannelInfo> ChannelInfo::neighbors(int ch)
{
    std::vector<ChannelInfo> ret;
    ChannelInfo tmp(ch);
    int l = tmp.layer;
    int r = tmp.row;
    int c = tmp.col;
    int t = tmp.type;
    
    // bars first
    if (t==0) { 
        for (int i=1;i<=3;i++) {
            if (i==r) continue;
            ret.push_back(ChannelInfo(l,i,c,0));
        }
        ret.push_back(ChannelInfo(l,-2,0,2));
    }
    return ret;
}

std::vector<ChannelInfo> ChannelInfo::neighbors(int layer, int row, int col, int type)
{
    std::vector<ChannelInfo> ret;
    ChannelInfo tmp(layer,row,col,type);
    int l = tmp.layer;
    int r = tmp.row;
    int c = tmp.col;
    int t = tmp.type;
    
    // bars first
    if (t==0) { 
        for (int i=1;i<=3;i++) {
            if (i==r) continue;
            ret.push_back(ChannelInfo(l,i,c,0));
        }
        ret.push_back(ChannelInfo(l,-2,0,2));
    }
    return ret;
}
