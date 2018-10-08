// Make milliqan validation plots. D. Stuart, Oct. 2017.

#include "TMath.h"
#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TH1F.h"
#include "TH1D.h"
#include "TH2F.h"
#include "TH3F.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include "TString.h"
#include "TVector3.h"

#include "thresholds.h"
#include "looper.h"

using namespace std;

void tree1r(TChain *chain, TString output_filename,TString EventCategory,TString LHCStatus,TString RangeCode, int RunNum, int Nevents=-1)
{
    int debug=0; // Debugging level. 0=none, 100=trace, 300=detailed trace

    // Fixed size dimensions of array or collections stored in the TTree if any.
    static const unsigned int NROWS = 32;
    static const unsigned int NCOLS = 5;
    float VThresholds[NROWS][NCOLS]; // Threshold for pulse height for each channel and event category (All,SPE,Small,Cosmic,Thru).
    float DThresholds[NROWS][NCOLS]; // Threshold for pulse duration for each channel and event category (All,SPE,Small,Cosmic,Thru).
    float AThresholds[NROWS][NCOLS]; // Threshold for pulse area for each channel and event category (All,SPE,Small,Cosmic,Thru).

    // Read the fill information.
    vector<int> fillNum;
    vector<Long64_t> fillStartTime; // in unix epoch time
    vector<Long64_t> fillEndTime; // in unix epoch time
    vector<float> fillLumi; // in pb^-1
    FILE *fillFile;
    fillFile = fopen("./data/processedFillList2018.txt","r");
    if (!fillFile) {
        cerr << "Could not open fill file.\n";
    }
    else { // Opened file successfully?  
        int ncol = 0;
        while (ncol >= 0) {
            int intVal; long dVal; float fVal;
            ncol=fscanf(fillFile,"%d", &intVal);
            fillNum.push_back(intVal);
            ncol=fscanf(fillFile,"%li", &dVal);
            fillStartTime.push_back(dVal);
            ncol=fscanf(fillFile,"%li", &dVal);
            fillEndTime.push_back(dVal);
            ncol=fscanf(fillFile,"%f", &fVal);
            fillLumi.push_back(fVal);
            char c;
            c = '0'; while (c != '\n' && ncol>0) ncol=fscanf(fillFile,"%c",&c);
        }
        fclose(fillFile);
    } // Opened file successfully?

    reset_counters();

    set_thresholds(&VThresholds[0][0],&DThresholds[0][0],&AThresholds[0][0],RunNum);

    if (debug>100) cout << "Initializing Chain for run number " << RunNum<<".\n";
    InitializeChain(chain);

    //Number of events to loop over
    Int_t nentries = (Nevents < 0) ? (Int_t)chain->GetEntries() : std::min(Nevents,(int)chain->GetEntries());
    cout<<"The number of entries is: "<<nentries<<endl;

    TFile *outFile = new TFile(output_filename.Data(),"UPDATE");
    outFile->cd();

    //Histogram Declarations
    if (debug>100) cout << "Booking histograms.\n";

    // Bins and ranges
    int nBins = 1; float minX = 0; float maxX = 0;
    if (RangeCode == "A") { nBins = nentries/10; minX = 0.; maxX = 1.*(nentries); }
    if (RangeCode == "B") { nBins = nentries/50; minX = 0.; maxX = 1.*(nentries); }
    if (RangeCode == "C") { nBins = nentries/100; minX = 0.; maxX = 1.*(nentries); }
    if (RangeCode == "D") { nBins = nentries/1000; minX = 0.; maxX = 1.*(nentries); }
    h_EventNumberUnsynched = new TH1D(EventCategory+"_"+LHCStatus+"_EventNumberUnsynched_"+RangeCode,"Unsynched event numbers",nBins,minX,maxX);

    // Plots of the event time.
    // First we need to find the min and max times and the total live time.
    // We also count the number of events with synched digitizers.
    int nSynched = 0, nUnSynched = 0;
    double minTime = 9.E15, maxTime = -9.E15;
    int firstEvt = 0, lastEvt = 0;
    int maxFile = 0;
    double SumTime = 0.; // Sum of all live time
    double SumSynchTime = 0.; // Sum of synched live time
    double prevTime = 0.;
    bool synched = false;
    string FirstTime="N/A", LastTime="N/A";
    for(int ia = 0; ia<nentries; ia++){ // Loop over all events
        chain->GetEntry(ia);
        if (filenum>maxFile) maxFile = filenum;
        if ((event>2 || filenum>1) && event_time_fromTDC>1.5E9) { // Ignore the first two events in file1 which can be leftover from previous run; ignore bad time measurements
            if ((event_trigger_time_tag_b1==event_trigger_time_tag_b0) || (groupTDC_b1->at(0) == groupTDC_b0->at(0))) {
                nSynched++;
                synched = true;
            }
            else {
                nUnSynched++;
                synched = false;
                h_EventNumberUnsynched->Fill(float(ia),1.);
            }
            if (prevTime>0 && ((filenum==1 && event>3) || (filenum>1 && event>1))) {
                SumTime += event_time_fromTDC-prevTime;
                if (synched) SumSynchTime += event_time_fromTDC-prevTime;
            }
            prevTime = event_time_fromTDC;
            if (event_time_fromTDC < minTime) { // New first event
                minTime = event_time_fromTDC;
                firstEvt = ia;
                if (RunNum>24) FirstTime = *event_t_string;
            } // New first event
            if (event_time_fromTDC > maxTime) { // New last event
                maxTime = event_time_fromTDC;
                lastEvt = ia;
                if (RunNum>24) LastTime = *event_t_string;
            } // New last event
        } // Ignore the first events, which may be buggy
    } // Loop over all events
    double minHour = minTime/3600; 
    double maxHour = maxTime/3600;
    double runTime = SumTime;

    // book histograms
    int nhists = bookHistograms(EventCategory, LHCStatus, RangeCode, maxFile, minTime, maxTime);

    // Determine the LHC fills present during this run. 
    // For now, only include fully contained fills...
    float totalLumi = 0.;
    cout << "Epoch time range = "<<Long64_t(minTime)<<" - "<<Long64_t(maxTime)<<"\n";
    for (unsigned int iFill=0; iFill<fillNum.size(); iFill++) {
        if (fillStartTime[iFill]>minTime && fillStartTime[iFill]<maxTime && fillEndTime[iFill]<maxTime) {
            // Make sure that we have not already used this fill.
            bool newFill = true;
            for (unsigned int iFill0 = 0; iFill0<iFill; iFill0++)
                if (fillNum[iFill0]==fillNum[iFill])
                    newFill = false;
            if (newFill) {
                cout << "Including lumi from fill "<<fillNum[iFill]<<" "<<fillStartTime[iFill]<<" "<<fillEndTime[iFill]<<" "<<fillLumi[iFill]<<"\n";
                totalLumi += fillLumi[iFill];
            }
        }
    }  

    // Print a summary of the run time and lumi
    cout << "Summary: Run "<<RunNum<<" "<<nentries<<" events over "<<setprecision(3)<<(maxTime-minTime)/3600.<<" hours between "<<FirstTime<<" and "<<LastTime;
    cout <<"; Trigger rate = "<<nentries/(maxTime-minTime)<<" Hz. Livetime="<<int(runTime)<<" sec = "<<setprecision(4)<<runTime/3600.<<" hr. Lumi="<<totalLumi<<"/pb. Scale to /hour = "<<setprecision(6)<<3600./(runTime)<<"\n";
    cout << "Synch: &epsilon;<sub>sync</sub> = " <<setprecision(3)<< (100.*nSynched)/(nSynched+nUnSynched) << " &plusmn; " << 100.*sqrt(nSynched)/(nSynched+nUnSynched) << " %";
    cout << "  T<sub>sync</sub> = "<<setprecision(3)<<SumSynchTime/3600.<<" hr\n";

    // Save information about the trigger rate for different threshold options.
    // The goal is to produce an ascii ntuple with the rate (events/hour) with different choices
    // of trigger thresholds for each channel. I measure this brute force by looping over all 16 threshold options
    // and count the number of events that would pass either a single channel or double coincidence trigger
    // using these thresholds.  There is no timing information used, just max>threshold.
    // Initialize the trigger emulation counters
    int nSingleChannel[32][600]; // 32 channels and thresholds from 0 to 600 mV
    int nDoubleCoincidence[32][600]; // 32 channels and thresholds from 0 to 600 mV
    for (int c=0; c<32; c++) {
        for (int iThr=0; iThr<600; iThr++) {
            nSingleChannel[c][iThr] = 0;
            nDoubleCoincidence[c][iThr] = 0;
        }
    }

    prevTime = 0.; // Initialize the previout event time; used to determine time between events
    long timeBetweenEvents = 0; // microseconds
    long prev_event_trigger_time_tag_b0 = 0;
    long prev_event_trigger_time_tag_b1 = 0;
    long prev_gTDC_b0 = 0;
    long prev_gTDC_b1 = 0;

    //Main Event loop
    for(int ia = 0; ia<nentries; ia++)
    {
        if (debug>100 || (ia%100000 == 0)) {cout << "Entry #"<<ia<<"\n"; cout.flush();}

        timeBetweenEvents = long(1000000*(event_time_fromTDC-prevTime));
        prevTime = event_time_fromTDC;

        chain->GetEntry(ia);

        synched = false;
        if (event_trigger_time_tag_b1==event_trigger_time_tag_b0)
            synched = true;

        int evtCategoryCode = GetEventCategoryCode(EventCategory);

        // Calculate total area of pulses and save a more convenient maxSample per channel
        float TotalArea[32]; // in nVs
        float TotalGlobalArea = 0.;
        float maxSample[32]; // in mV
        for (int c=0; c<32; c++) {
            TotalArea[c] = 0.; // Sum of area of pulses in the channel
            maxSample[c] = max_sample->at(c);
        }
        for (int i=0; i<int(chan->size()); i++) {
            TotalArea[int(chan->at(i))] += area->at(i)/1000.;
            TotalGlobalArea += area->at(i)/1000.;
        }

        // Build a map of hits above thresholds appropriate for the passed event category, and record the pulse number; consider only the first pulse in each channel.
        bool HitChan[32]; // Simple flag showing existence of a hit
        int ChanHitIndex[32]; // Index to the pulse with the hit
        int ChanHitCount[32]; // count of pulses per channel passing requirements for a hit
        int nHits=0; // Number of channels with hits
        for (int c=0; c<32; c++) {
            ChanHitIndex[c] = -1; // No hit
            ChanHitCount[c] = 0; // No hit
            HitChan[c] = false;
        }
        int PulseCount[32] = {0};
        for (int c=0; c<32; c++) {
            for (int i=0; i<int(chan->size()); i++) {// Pulse loop 
                if (chan->at(i) == c) {
                    PulseCount[c] += 1;
                    // hit in this channel?
                    if ((duration->at(i) > DThresholds[c][evtCategoryCode]) && (maxSample[c] > VThresholds[c][evtCategoryCode]) && (TotalArea[c] > AThresholds[c][evtCategoryCode])) { 
                        HitChan[c] = true;
                        ChanHitCount[c] += 1;
                        if (ChanHitIndex[c] == -1 or ptime->at(i) < ptime->at(ChanHitIndex[c]))
                            ChanHitIndex[c] = i;
                    }
                }
            }
            if (HitChan[c]) nHits++;
        }

        // Plot max pulse height for channels when they have hits in either of the nearest interlayer partners.
        // The threshold for the other partners varies with evtCategoryCode as 10mV*evtCategoryCode.
        // There is no timing cuts on this comparison.
        // IS THE MAPPING STILL CORRECT?
        bool partnersHit[32]; // True for each channel if there is a hit in its interlayer partners
        for (int c=0; c<32; c++)
            partnersHit[c] = false;
        float partnerThreshold = 10.*(evtCategoryCode+1); 
        if (maxSample[6]>partnerThreshold || maxSample[14]>partnerThreshold) partnersHit[0] = true;
        if (maxSample[7]>partnerThreshold || maxSample[15]>partnerThreshold) partnersHit[1] = true;
        if (maxSample[12]>partnerThreshold || maxSample[10]>partnerThreshold) partnersHit[2] = true;
        if (maxSample[13]>partnerThreshold || maxSample[11]>partnerThreshold) partnersHit[3] = true;
        if (maxSample[8]>partnerThreshold || maxSample[10]>partnerThreshold) partnersHit[4] = true;
        if (maxSample[9]>partnerThreshold || maxSample[11]>partnerThreshold) partnersHit[5] = true;
        if (maxSample[0]>partnerThreshold || maxSample[14]>partnerThreshold) partnersHit[6] = true;
        if (maxSample[1]>partnerThreshold || maxSample[15]>partnerThreshold) partnersHit[7] = true;
        if (maxSample[4]>partnerThreshold || maxSample[10]>partnerThreshold) partnersHit[8] = true;
        if (maxSample[5]>partnerThreshold || maxSample[11]>partnerThreshold) partnersHit[9] = true;
        if (maxSample[2]>partnerThreshold || maxSample[12]>partnerThreshold) partnersHit[10] = true;
        if (maxSample[3]>partnerThreshold || maxSample[13]>partnerThreshold) partnersHit[11] = true;
        if (maxSample[4]>partnerThreshold || maxSample[10]>partnerThreshold) partnersHit[12] = true;
        if (maxSample[3]>partnerThreshold || maxSample[11]>partnerThreshold) partnersHit[13] = true;
        if (maxSample[0]>partnerThreshold || maxSample[6]>partnerThreshold) partnersHit[14] = true;
        if (maxSample[1]>partnerThreshold || maxSample[7]>partnerThreshold) partnersHit[15] = true;

        // Plots of max sample for channels with 2-layer partner hits
        for (int c=0; c<32; c++)
            if (partnersHit[c] && maxSample[c]>7.) h_DoubleLayerMax[c]->Fill(maxSample[c],1.);

        // Plot of the number of hit bars
        h_NHitBars->Fill(1.*nHits,1.);

        // Plot of the global total pulse area (across all bars)
        h_TotalGlobalPulseArea->Fill(TotalGlobalArea,1.);

        bool GoodEvent = isGoodEvent(nHits, HitChan, maxSample, EventCategory, LHCStatus, RunNum);
        if (not GoodEvent) continue;
        if (evtCategoryCode == 4)
            std::cout << "Found good event" << std::endl;
        
        // loop over channels
        for (unsigned int c=0; c<32; c++) {
            // Plots of the raw MAX pulse height in each channel
            h_Max[c]->Fill(maxSample[c],1.);

            // Plots of the sideband mean
            if (c<sideband_mean->size())
                h_SidebandMean[c]->Fill(sideband_mean->at(c),1.);
            if (c<sideband_RMS->size())
                h_SidebandRMS[c]->Fill(sideband_RMS->at(c),1.);
            
            // Plots of event time and filenum for channels with hits
            if (HitChan[c]) {
                h_FileNum[c]->Fill(1.*filenum,1.);
                // DO WE NEED THESE SEPARATE FOR EVERY CHANNEL?
                h_EventTime[c]->Fill(event_time_fromTDC/3600.,1.);
                h_EventTimeSeconds[c]->Fill(event_time_fromTDC-minTime,1.);
                if (synched) 
                    h_EventTimeSynchedSeconds[c]->Fill(event_time_fromTDC-minTime,1.);
                else
                    h_EventTimeUnsynchedSeconds[c]->Fill(event_time_fromTDC-minTime,1.);
            }
        }

        // Figure out the event time as the time of the earliest pulse in any channel.
        float t0 = 9.E9;  
        for (int i=0; i<int(ptime->size()); i++) // Pulse loop 
            if (ipulse->at(i) == 0 ) // First pulse in this channel
                if (ptime->at(i)<t0) t0 = ptime->at(i);

        // Plots of the number of pulses, first pulse time and area in each channel
        for (int i=0; i<int(ptime->size()); i++) { // Pulse loop 
            if (ipulse->at(i) == 0 ) { // First pulse in this channel
                h_FirstTime[int(chan->at(i))]->Fill(float(ptime->at(i)),1.);
                h_FirstPulseArea[int(chan->at(i))]->Fill(float(area->at(i))/1000.,1.);
                h_FirstPulseNPE[int(chan->at(i))]->Fill(float(nPE->at(i)),1.);
                h_FirstPulseHeight[int(chan->at(i))]->Fill(float(height->at(i)),1.);
                h_FirstDuration[int(chan->at(i))]->Fill(float(duration->at(i)),1.);
                h_NPulses[int(chan->at(i))]->Fill(float(npulses->at(i)),1.);
            } // First pulse in this channel
        } // Pulse loop

        // Plot the pulse time relative to the closest LHC clock edge
        for (int c=0; c<32; c++) {
            if (c==15) continue;

            // First find the index of the largest pulse from this channel in the event
            // DO WE STORE MAX PULSE FOR EACH CHANNEL?
            int iLargest = -1;
            for (int i=0; i<int(ptime->size()); i++) 
                if (int(chan->at(i))==c) {
                    if (iLargest<0)
                        iLargest = i;
                    else if (area->at(i)>area->at(iLargest))
                        iLargest = i;
                }

            // Now find the nearest LHC clock edge (pulse)
            // WHAT DOES CALIBRATED MEAN HERE?
            // IS IT WORTH DOING SOME OF THIS WHEN WE PROCESS THE DATA?
            if (iLargest>=0 && area->at(iLargest)>AThresholds[c][evtCategoryCode] && 
                maxSample[c]>VThresholds[c][evtCategoryCode]) { // A pulse found?
                float dLHCtime = 999.;
                for (int iL=0; iL<int(ptime->size()); iL++) 
                    if (int(chan->at(iL)) == 15) { // LHC pulse loop
                        if (fabs(ptime->at(iLargest)-ptime->at(iL))<fabs(dLHCtime))
                            dLHCtime = ptime->at(iLargest)-ptime->at(iL);
                    } // LHC pulse loop
                h_LHCTime[c]->Fill(dLHCtime);
                // Repeat using calibrated time
                dLHCtime = 999.;
                for (int iL=0; iL<int(ptime->size()); iL++) 
                    if (int(chan->at(iL)) == 15) { // LHC pulse loop
                        if (fabs(time_module_calibrated->at(iLargest)-time_module_calibrated->at(iL))<fabs(dLHCtime))
                            dLHCtime = time_module_calibrated->at(iLargest)-time_module_calibrated->at(iL);
                    } // LHC pulse loop
                h_LHCTimeCalib[c]->Fill(dLHCtime);
            } // A pulse found?
        }

        // Plot the pulse time relative to the largest pulse in various channels
        for (int iprobe=0; iprobe<10; iprobe++) { // Loop through 1,7,3,18,20,28,21,0,2,4
            int prbCH = 1;
            if (iprobe==0) prbCH=1;
            if (iprobe==1) prbCH=7;
            if (iprobe==2) prbCH=3;
            if (iprobe==3) prbCH=18;
            if (iprobe==4) prbCH=20;
            if (iprobe==5) prbCH=28;
            if (iprobe==6) prbCH=21;
            if (iprobe==7) prbCH=0;
            if (iprobe==8) prbCH=2;
            if (iprobe==9) prbCH=4;
            // First find the index to the largest pulse in the probe channel
            int iCH = -1;
            for (int i=0; i<int(ptime->size()); i++) 
                if (int(chan->at(i))==prbCH) {
                    if (iCH<0 || area->at(i)>area->at(iCH))
                        iCH = i;
                }
            // Now loop over all channels
            if (iCH>=0 && area->at(iCH)>AThresholds[prbCH][evtCategoryCode] && 
                maxSample[prbCH]>VThresholds[prbCH][evtCategoryCode]) { // Found a pulse in probe channel?
                for (int c=0; c<32; c++)
                    if (c!=15 && c!=prbCH) { // Channel loop
                        // First find the index to the largest pulse from this channel in the event
                        int iLargest = -1;
                        for (int i=0; i<int(ptime->size()); i++) 
                            if (int(chan->at(i))==c) {
                                if (iLargest<0 || area->at(i)>area->at(iLargest))
                                    iLargest = i;
                            }
                        if (iLargest>=0 && area->at(iLargest)>AThresholds[c][evtCategoryCode] && maxSample[c]>VThresholds[c][evtCategoryCode]) {
                            if (iprobe==0) {
                                h_TimeWRTCH1[c]->Fill(ptime->at(iLargest)-ptime->at(iCH));
                                h_TimeCalibWRTCH1[c]->Fill(time_module_calibrated->at(iLargest)-time_module_calibrated->at(iCH));
                            }
                            if (iprobe==7) {
                                h_TimeWRTCH0[c]->Fill(ptime->at(iLargest)-ptime->at(iCH));
                                h_TimeCalibWRTCH0[c]->Fill(time_module_calibrated->at(iLargest)-time_module_calibrated->at(iCH));
                            }
                            if (iprobe==8) {
                                h_TimeWRTCH2[c]->Fill(ptime->at(iLargest)-ptime->at(iCH));
                                h_TimeCalibWRTCH2[c]->Fill(time_module_calibrated->at(iLargest)-time_module_calibrated->at(iCH));
                            }
                            if (iprobe==9) {
                                h_TimeWRTCH4[c]->Fill(ptime->at(iLargest)-ptime->at(iCH));
                                h_TimeCalibWRTCH4[c]->Fill(time_module_calibrated->at(iLargest)-time_module_calibrated->at(iCH));
                            }
                            if (iprobe==1) {
                                h_TimeWRTCH7[c]->Fill(ptime->at(iLargest)-ptime->at(iCH));
                                h_TimeCalibWRTCH7[c]->Fill(time_module_calibrated->at(iLargest)-time_module_calibrated->at(iCH));
                            }
                            if (iprobe==2) {
                                h_TimeWRTCH3[c]->Fill(ptime->at(iLargest)-ptime->at(iCH));
                                h_TimeCalibWRTCH3[c]->Fill(time_module_calibrated->at(iLargest)-time_module_calibrated->at(iCH));
                            }
                            if (iprobe==3) {
                                h_TimeWRTCH18[c]->Fill(ptime->at(iLargest)-ptime->at(iCH));
                                h_TimeCalibWRTCH18[c]->Fill(time_module_calibrated->at(iLargest)-time_module_calibrated->at(iCH));
                            }
                            if (iprobe==4) {
                                h_TimeWRTCH20[c]->Fill(ptime->at(iLargest)-ptime->at(iCH));
                                h_TimeCalibWRTCH20[c]->Fill(time_module_calibrated->at(iLargest)-time_module_calibrated->at(iCH));
                            }
                            if (iprobe==5) {
                                h_TimeWRTCH28[c]->Fill(ptime->at(iLargest)-ptime->at(iCH));
                                h_TimeCalibWRTCH28[c]->Fill(time_module_calibrated->at(iLargest)-time_module_calibrated->at(iCH));
                            }
                            if (iprobe==6) {
                                h_TimeWRTCH21[c]->Fill(ptime->at(iLargest)-ptime->at(iCH));
                                h_TimeCalibWRTCH21[c]->Fill(time_module_calibrated->at(iLargest)-time_module_calibrated->at(iCH));
                            }
                        }
                    } // Channel loop
            } // Found a pulse in probe channel?
        } // Loop through 1,7,3,18,20,28,21,0,2,4

        // Plots of afterpulses.
        // Only consider clean after pulses with at least 10 ns between it and the end of the previous pulse. 
        float firstTime[32]; // Time of first pulse in channel
        for (int i=0; i<int(ptime->size()); i++)
            if (ipulse->at(i)==0)
                firstTime[int(chan->at(i))] = ptime->at(i);
        for (int i=0; i<int(ptime->size()); i++) { // Pulse loop 
            if (ipulse->at(i) != 0 ) { // Not first pulse in this channel?
                if (ptime->at(i)>ptime->at(i-1)+duration->at(i-1)+20. &&
                    duration->at(i)>7.) { // Clean afterpulse
                    h_AfterPulseArea[int(chan->at(i))]->Fill(float(area->at(i))/1000.,1.);
                    h_AfterPulseHeight[int(chan->at(i))]->Fill(float(height->at(i)),1.);
                    h_AfterPulseDuration[int(chan->at(i))]->Fill(float(duration->at(i)),1.);
                    h_AfterPulseTime[int(chan->at(i))]->Fill(float(ptime->at(i))-firstTime[int(chan->at(i))],1.);
                } // Clean afterpulse?
            } // Not first pulse in this channel?
        } // Pulse loop

        // Plot charge, height, and duration of tagged channels.
        // Tagged channels are those with a cosmic partner containing a hit.

        bool NeighborHit[32]; // True for each channel if there is a hit in its neighbor
        for (int c=0; c<32; c++)
            NeighborHit[c] = false;

        // The channel mapping changed over time, e.g., in TS1
        NeighborHitMap(NeighborHit,HitChan,RunNum,EventCategory);

        // Determine which layers and slabs are hit
        bool layHit[3]; bool slabHit[4]; 
        layHit[0] = false; layHit[1] = false; layHit[2] = false;
        slabHit[0] = false; slabHit[1] = false; slabHit[2] = false; slabHit[3] = false; 
        if (HitChan[18]) slabHit[0] = true;
        if (HitChan[20]) slabHit[1] = true;
        if (HitChan[28]) slabHit[2] = true;
        if (HitChan[21]) slabHit[3] = true;
        if (HitChan[0] || HitChan[1] || HitChan[24] || HitChan[25] || HitChan[8] || HitChan[9]) layHit[0] = true;
        if (HitChan[6] || HitChan[7] || HitChan[16] || HitChan[17] || HitChan[12] || HitChan[13]) layHit[1] = true;
        if (HitChan[2] || HitChan[3] || HitChan[22] || HitChan[23] || HitChan[4] || HitChan[5]) layHit[2] = true;
        int nSlabHits = 0;
        for (int i=0; i<4; i++)
            if (slabHit[i])
                nSlabHits++;
        int nLayHits = 0;
        for (int i=0; i<3; i++)
            if (layHit[i])
                nLayHits++;

        // Plot number of layers hit
        h_NHitLayers->Fill(1.*nLayHits,1.);

        // Dump some crude event displays for cosmics
        bool showDisplay = true;
        if (showDisplay && evtCategoryCode==3 && (HitChan[10] || HitChan[11] || HitChan[14])) { // Cosmic step
            if (nHits>=3) { // At least 3 hits?
                cout << "\n";
                cout << "Display: file="<<filenum<<" event="<<event<<"\n";
                cout << "Display: nS="<<nSlabHits<<" nL="<<nLayHits<<" "<<layHit[0]<<layHit[1]<<layHit[2]<<" "<<filenum<<" "<<event<<" L2: ";
                cout << "     ["<<HitChan[21] <<"]\n"; 
                cout << "Display: nS="<<nSlabHits<<" nL="<<nLayHits<<" "<<layHit[0]<<layHit[1]<<layHit[2]<<" "<<filenum<<" "<<event<<" L2: ";
                cout << "  --" << HitChan[14]<< HitChan[14]<< HitChan[14]<< HitChan[14]<< HitChan[14]<<"--\n"; 
                cout << "Display: nS="<<nSlabHits<<" nL="<<nLayHits<<" "<<layHit[0]<<layHit[1]<<layHit[2]<<" "<<filenum<<" "<<event<<" L2: ";
                cout << "  /"<<HitChan[31] << "/" << HitChan[2] <<" "<< HitChan[3] <<"\\"<<HitChan[26]<<"\\ \n"; 
                cout << "Display: nS="<<nSlabHits<<" nL="<<nLayHits<<" "<<layHit[0]<<layHit[1]<<layHit[2]<<" "<<filenum<<" "<<event<<" L2: ";
                cout << " /"<<HitChan[31] << "/ " << HitChan[22] <<" "<< HitChan[23] <<" \\"<<HitChan[26]<<"\\ \n"; 
                cout << "Display: nS="<<nSlabHits<<" nL="<<nLayHits<<" "<<layHit[0]<<layHit[1]<<layHit[2]<<" "<<filenum<<" "<<event<<" L2: ";
                cout << "/"<<HitChan[31] << "/  " << HitChan[4] <<" "<< HitChan[5] <<"  \\"<<HitChan[26]<<"\\ \n"; 

                cout << "Display: nS="<<nSlabHits<<" nL="<<nLayHits<<" "<<layHit[0]<<layHit[1]<<layHit[2]<<" "<<filenum<<" "<<event<<" L1: ";
                cout << "     ["<<HitChan[28] <<"]\n"; 
                cout << "Display: nS="<<nSlabHits<<" nL="<<nLayHits<<" "<<layHit[0]<<layHit[1]<<layHit[2]<<" "<<filenum<<" "<<event<<" L1: ";
                cout << "  --" << HitChan[11]<< HitChan[11]<< HitChan[11]<< HitChan[11]<< HitChan[11]<<"--\n"; 
                cout << "Display: nS="<<nSlabHits<<" nL="<<nLayHits<<" "<<layHit[0]<<layHit[1]<<layHit[2]<<" "<<filenum<<" "<<event<<" L1: ";
                cout << "  /"<<HitChan[30] << "/" << HitChan[6] <<" "<< HitChan[7] <<"\\"<<HitChan[19]<<"\\ \n"; 
                cout << "Display: nS="<<nSlabHits<<" nL="<<nLayHits<<" "<<layHit[0]<<layHit[1]<<layHit[2]<<" "<<filenum<<" "<<event<<" L1: ";
                cout << " /"<<HitChan[30] << "/ " << HitChan[16] <<" "<< HitChan[17] <<" \\"<<HitChan[19]<<"\\ \n"; 
                cout << "Display: nS="<<nSlabHits<<" nL="<<nLayHits<<" "<<layHit[0]<<layHit[1]<<layHit[2]<<" "<<filenum<<" "<<event<<" L1: ";
                cout << "/"<<HitChan[30] << "/  " << HitChan[12] <<" "<< HitChan[13] <<"  \\"<<HitChan[19]<<"\\ \n"; 

                cout << "Display: nS="<<nSlabHits<<" nL="<<nLayHits<<" "<<layHit[0]<<layHit[1]<<layHit[2]<<" "<<filenum<<" "<<event<<" L0: ";
                cout << "     ["<<HitChan[20] <<"]\n"; 
                cout << "Display: nS="<<nSlabHits<<" nL="<<nLayHits<<" "<<layHit[0]<<layHit[1]<<layHit[2]<<" "<<filenum<<" "<<event<<" L0: ";
                cout << "  --" << HitChan[10]<< HitChan[10]<< HitChan[10]<< HitChan[10]<< HitChan[10]<<"--\n"; 
                cout << "Display: nS="<<nSlabHits<<" nL="<<nLayHits<<" "<<layHit[0]<<layHit[1]<<layHit[2]<<" "<<filenum<<" "<<event<<" L0: ";
                cout << "  /"<<HitChan[27] << "/" << HitChan[0] <<" "<< HitChan[1] <<"\\"<<HitChan[29]<<"\\ \n"; 
                cout << "Display: nS="<<nSlabHits<<" nL="<<nLayHits<<" "<<layHit[0]<<layHit[1]<<layHit[2]<<" "<<filenum<<" "<<event<<" L0: ";
                cout << " /"<<HitChan[27] << "/ " << HitChan[24] <<" "<< HitChan[25] <<" \\"<<HitChan[29]<<"\\ \n"; 
                cout << "Display: nS="<<nSlabHits<<" nL="<<nLayHits<<" "<<layHit[0]<<layHit[1]<<layHit[2]<<" "<<filenum<<" "<<event<<" L0: ";
                cout << "/"<<HitChan[27] << "/  " << HitChan[8] <<" "<< HitChan[9] <<"  \\"<<HitChan[29]<<"\\ \n"; 
                cout << "Display: nS="<<nSlabHits<<" nL="<<nLayHits<<" "<<layHit[0]<<layHit[1]<<layHit[2]<<" "<<filenum<<" "<<event<<" L0: ";
                cout << "     ["<<HitChan[18] <<"]\n"; 
            } // nHits>=4
        } // Cosmic step

        /******************************************************************************************************************************************************
        **** Insert cosmics study code here                                                                                                                ****
        ****                                                                                                                                               ****
        **** 1. Require event is good                                                                                                                      ****
        **** 2. Require event pass selection                                                                                                               ****
        ****    - look at bars in middle row of each layer, these are the "probes"                                                                         ****
        ****    - "Cosmic": require bars on either side (bottom,top rows) in same column have a hit                                                        ****
        ****    - "CosmicTag": "Cosmic" selection AND require that "top" sheet also has a hit                                                              ****
        **** 3. Fill histograms:                                                                                                                           ****
        ****    - height, area, duration, NPE per pulse per channel                                                                                        ****
        ****    - height, area, duration, NPE first pulse per channel                                                                                      ****
        ****    - height, area, duration, NPE max pulse per channel                                                                                        ****
        ****    - number of pulses, per channel and whole detector                                                                                         ****
        ****    - time relative to pulses in neighboring channels                                                                                          ****
        ****    - compare beam and non-beam periods                                                                                                        ****
        ****                                                                                                                                               ****
        ******************************************************************************************************************************************************/

        // check if event is good
        if (not GoodEvent) continue;
    
        //int middleChannels[] = {16,17,22,23,24,25}; // channel numbers of bars in middle rows

        // get index of max pulse in each channel
        int num_pulses = int(ipulse->size());
        int npulses_tot = 0;
        int nhits_tot = 0;
        int nchannels_with_hit = 0;
        int nchannels_with_pulse = 0;
        int max_pulse_index[32] = {-1};
        bool found_chan[32] = {false};
        int ncosmictags = 0;
        for (int c=0; c<32; c++) {
            nhits_tot += ChanHitCount[c];
            for (int i=0; i<num_pulses; i++) {
                if (chan->at(i) != c) continue;
                if (not found_chan[c]) {
                    found_chan[c] = true;
                    npulses_tot += npulses->at(i);
                    ++nchannels_with_pulse;
                }
                if (max_pulse_index[c] == -1)
                    max_pulse_index[c] = i;
                else {
                    if (area->at(i) > area->at(max_pulse_index[c]))
                        max_pulse_index[c] = i;
                }
            } // pulse loop

            if (HitChan[c]) ++nchannels_with_hit;

            // fill histograms for maximum pulse (height) in each channel c
            if (NeighborHit[c]) {
                ++ncosmictags;
                h_nhitsPerChannel[c]->Fill(ChanHitCount[c]);
                if (max_pulse_index[c] >= 0) {
                    int index = max_pulse_index[c];
                    h_maxPulseHeight[c]->Fill(height->at(index));
                    h_maxPulseArea[c]->Fill(area->at(index)/1000.);
                    h_maxPulseDuration[c]->Fill(duration->at(index));
                    h_maxPulseNPE[c]->Fill(nPE->at(index));
                    h_maxPulseTime[c]->Fill(ptime->at(index));
                    h_npulsesPerChannel[c]->Fill(npulses->at(index));
                    if (npulses->at(index) != PulseCount[c])
                        std::cout << "Problem counting number of pulses." << std::endl;
                }
                else
                    h_npulsesPerChannel[c]->Fill(0);
            }
        } // channel loop

        h_ncosmics->Fill(ncosmictags);

        for (int c=0; c<32; c++) {
            if (max_pulse_index[c] < 0) continue;
            if (not NeighborHit[c]) continue;

            h_npulses[c]->Fill(npulses_tot);
            h_nhits[c]->Fill(nhits_tot);
            h_nchannelsWithAtLeastOnePulse[c]->Fill(nchannels_with_pulse);
            h_nchannelsWithAtLeastOneHit[c]->Fill(nchannels_with_hit);

            std::vector<ChannelInfo> neighbors = ChannelInfo::neighbors(c);
            for (auto chinfo : neighbors) {
                if (EventCategory == "Cosmics" and chinfo.type != 0) continue; // only consider pulses in bars for event category "Cosmics"
                if (not HitChan[chinfo.chan]) continue; // require that there is a hit in the neighboring channel
                if (c==chinfo.chan) {
                    std::cout << "Found hit in chan " << c << " with hit in neighboring element with same channel number." << std::endl;
                    continue;
                }
                if (chinfo.chan < 0) {
                    std::cout << "Found hit in chan " << c << " with hit in neighboring element with negative channel number: " << chinfo.chan << "." << std::endl;
                    continue;
                } 
                if (max_pulse_index[c] < 0 or max_pulse_index[chinfo.chan] < 0) {
                    std::cout << "Did not find a maximum pulse in channel " << c << " or channel " << chinfo.chan << std::endl;
                    continue;
                }
                double tdiff = ptime->at(max_pulse_index[c]) - ptime->at(max_pulse_index[chinfo.chan]);
                h_diffTimeWithNeighboringMaxHit[c]->Fill(tdiff);                
    
                double tdiff_calib = time_module_calibrated->at(max_pulse_index[c]) - time_module_calibrated->at(max_pulse_index[chinfo.chan]);
                h_diffTimeWithNeighboringMaxHitCalibrated[c]->Fill(tdiff_calib); 
            } // neighbor loop
        } // channel loop

        for (int i=0; i<num_pulses; i++) {
            int c = int(chan->at(i));
            if (not NeighborHit[c]) continue;
             
            // fill histograms for each pulse in channel c
            h_pulseHeight[c]->Fill(height->at(i));
            h_pulseArea[c]->Fill(area->at(i)/1000.);
            h_pulseDuration[c]->Fill(duration->at(i));
            h_pulseNPE[c]->Fill(nPE->at(i));
            h_pulseTime[c]->Fill(ptime->at(i));
    
            // fill histograms for first pulse in channel c
            if (ipulse->at(i) == 0) {
                h_firstPulseHeight[c]->Fill(height->at(i));
                h_firstPulseArea[c]->Fill(area->at(i)/1000.);
                h_firstPulseDuration[c]->Fill(duration->at(i));
                h_firstPulseNPE[c]->Fill(nPE->at(i));
                h_firstPulseTime[c]->Fill(ptime->at(i));
            } 
        }

        /*******************************************************************************************************************************************************
        ****                                                                                                                                                ****
        ****                                              END OF COSMICS STUDY                                                                              ****
        ****                                                                                                                                                ****
        *******************************************************************************************************************************************************/
    
        // Plots of max sample for tagged channels
        for (int c=0; c<32; c++)
            if (NeighborHit[c] && maxSample[c]>0.5*VThresholds[c][evtCategoryCode]) h_TaggedMax[c]->Fill(maxSample[c],1.);

        // Now make plots of pulse area, height, and duration for tagged channels.
        float TotalPulseArea[32];
        for (int c=0; c<32; c++)
            TotalPulseArea[c] = 0.; // Sum of area of pulses in the channel
        for (int i=0; i<int(chan->size()); i++) { // Pulse loop 
            TotalPulseArea[int(chan->at(i))] += area->at(i)/1000.;
            if (ipulse->at(i) == 0 ) { // First pulse in this channel
                if ((NeighborHit[int(chan->at(i))]) &&
                    (((area->at(i))/1000.>0.5*AThresholds[chan->at(i)][evtCategoryCode])) &&
                    (height->at(i)>0.5*VThresholds[chan->at(i)][evtCategoryCode]) &&
                    (duration->at(i)>DThresholds[chan->at(i)][evtCategoryCode])) { // Tagged by neighbor hit?
                    h_TaggedPulseArea[int(chan->at(i))]->Fill(float(area->at(i))/1000.,1.);
                    h_TaggedPulseNPE[int(chan->at(i))]->Fill(float(nPE->at(i)),1.);
                    h_TaggedPulseHeight[int(chan->at(i))]->Fill(float(height->at(i)),1.);
                    h_TaggedDuration[int(chan->at(i))]->Fill(float(duration->at(i)),1.);
                } // Tagged by neighbor hit?
            } // First pulse in this channel?
        } // Pluse loop

        // Histograms of total pulse area for all channels
        for (int c=0; c<32; c++)
            if (TotalPulseArea[c]>1.E-5) h_TotalPulseArea[c]->Fill(TotalArea[c],1.);

        // Histograms of total pulse area for channels with a tagging neighbor hit
        for (int c=0; c<32; c++)
            if (NeighborHit[c] && TotalPulseArea[c]>0.5*AThresholds[c][evtCategoryCode])
                h_TaggedTotalPulseArea[c]->Fill(TotalPulseArea[c],1.);

        // Plot max pulse height for channels when they have hits in the two straight line interlayer partners.
        // The threshold for the other partners varies with evtCategoryCode as 10mV*evtCategoryCode.
        // There is no timing cuts on this comparison.
        // IS THE MAPPING STILL CORRECT?
/*
        bool partnersHit[32]; // True for each channel if there is a hit in its interlayer partners
        for (int c=0; c<32; c++)
            partnersHit[c] = false;
        float partnerThreshold = 10.*(1+evtCategoryCode); 
        if (maxSample[6]>partnerThreshold && maxSample[14]>partnerThreshold) partnersHit[0] = true;
        if (maxSample[7]>partnerThreshold && maxSample[15]>partnerThreshold) partnersHit[1] = true;
        if (maxSample[12]>partnerThreshold && maxSample[10]>partnerThreshold) partnersHit[2] = true;
        if (maxSample[13]>partnerThreshold && maxSample[11]>partnerThreshold) partnersHit[3] = true;
        if (maxSample[8]>partnerThreshold && maxSample[10]>partnerThreshold) partnersHit[4] = true;
        if (maxSample[9]>partnerThreshold && maxSample[11]>partnerThreshold) partnersHit[5] = true;
        if (maxSample[0]>partnerThreshold && maxSample[14]>partnerThreshold) partnersHit[6] = true;
        if (maxSample[1]>partnerThreshold && maxSample[15]>partnerThreshold) partnersHit[7] = true;
        if (maxSample[4]>partnerThreshold && maxSample[10]>partnerThreshold) partnersHit[8] = true;
        if (maxSample[5]>partnerThreshold && maxSample[11]>partnerThreshold) partnersHit[9] = true;
        if (maxSample[2]>partnerThreshold && maxSample[12]>partnerThreshold) partnersHit[10] = true;
        if (maxSample[3]>partnerThreshold && maxSample[13]>partnerThreshold) partnersHit[11] = true;
        if (maxSample[4]>partnerThreshold && maxSample[10]>partnerThreshold) partnersHit[12] = true;
        if (maxSample[3]>partnerThreshold && maxSample[11]>partnerThreshold) partnersHit[13] = true;
        if (maxSample[0]>partnerThreshold && maxSample[6]>partnerThreshold) partnersHit[14] = true;
        if (maxSample[1]>partnerThreshold && maxSample[7]>partnerThreshold) partnersHit[15] = true;
*/
        // Plots of max sample for channels with 3-layer partner hits
        for (int c=0; c<32; c++)
            if (partnersHit[c] && maxSample[c]>7.) h_TripleLayerMax[c]->Fill(maxSample[c],1.);

        // Plots of coincidence rates with other channels
        for (int c = 0; c<32; c++)
            for (int c2 = 0; c2<32; c2++) 
                if ( (c2 != c) && HitChan[c] && HitChan[c2] )
                    h_NPairedHits[c]->Fill(float(c2),1.);

        // Plots of triplet hits
        //  1 = CH0-6-2
        //  2 = CH1-7-3
        //  3 = CH24-16-22
        //  4 = CH25-17-23
        //  5 = CH8-12-4
        //  6 = CH9-13-5
        //  7 = CH10-30-14
        //  8 = CH29-19-26
        //  9 = CH27-11-31
        // 10 = CH18-20-28
        // 11 = CH18-21-28
        if (HitChan[0] && HitChan[6] && HitChan[2]) h_NTripletHits->Fill(1.,1.);
        if (HitChan[1] && HitChan[7] && HitChan[3]) h_NTripletHits->Fill(2.,1.);
        if (HitChan[24] && HitChan[16] && HitChan[22]) h_NTripletHits->Fill(3.,1.);
        if (HitChan[25] && HitChan[17] && HitChan[23]) h_NTripletHits->Fill(4.,1.);
        if (HitChan[8] && HitChan[12] && HitChan[4]) h_NTripletHits->Fill(5.,1.);
        if (HitChan[9] && HitChan[13] && HitChan[5]) h_NTripletHits->Fill(6.,1.);
        if (HitChan[10] && HitChan[30] && HitChan[14]) h_NTripletHits->Fill(7.,1.);
        if (HitChan[29] && HitChan[19] && HitChan[26]) h_NTripletHits->Fill(8.,1.);
        if (HitChan[27] && HitChan[11] && HitChan[31]) h_NTripletHits->Fill(9.,1.);
        if (HitChan[18] && HitChan[20] && HitChan[28]) h_NTripletHits->Fill(10.,1.);
        if (HitChan[18] && HitChan[21] && HitChan[28]) h_NTripletHits->Fill(11.,1.);
        // Triplet hits with no other hits present
        if (nHits == 3) { // 3 hits?
            if (HitChan[0] && HitChan[6] && HitChan[2]) h_NTripletHits3->Fill(1.,1.);
            if (HitChan[1] && HitChan[7] && HitChan[3]) h_NTripletHits3->Fill(2.,1.);
            if (HitChan[24] && HitChan[16] && HitChan[22]) h_NTripletHits3->Fill(3.,1.);
            if (HitChan[25] && HitChan[17] && HitChan[23]) h_NTripletHits3->Fill(4.,1.);
            if (HitChan[8] && HitChan[12] && HitChan[4]) h_NTripletHits3->Fill(5.,1.);
            if (HitChan[9] && HitChan[13] && HitChan[5]) h_NTripletHits3->Fill(6.,1.);
            if (HitChan[10] && HitChan[30] && HitChan[14]) h_NTripletHits3->Fill(7.,1.);
            if (HitChan[29] && HitChan[19] && HitChan[26]) h_NTripletHits3->Fill(8.,1.);
            if (HitChan[27] && HitChan[11] && HitChan[31]) h_NTripletHits3->Fill(9.,1.);
            if (HitChan[18] && HitChan[20] && HitChan[28]) h_NTripletHits3->Fill(10.,1.);
            if (HitChan[18] && HitChan[21] && HitChan[28]) h_NTripletHits3->Fill(11.,1.);
        } // 3 hits?
        if (nHits == 4) { // 4 hits?
            if (HitChan[0] && HitChan[6] && HitChan[2]) h_NTripletHits4->Fill(1.,1.);
            if (HitChan[1] && HitChan[7] && HitChan[3]) h_NTripletHits4->Fill(2.,1.);
            if (HitChan[24] && HitChan[16] && HitChan[22]) h_NTripletHits4->Fill(3.,1.);
            if (HitChan[25] && HitChan[17] && HitChan[23]) h_NTripletHits4->Fill(4.,1.);
            if (HitChan[8] && HitChan[12] && HitChan[4]) h_NTripletHits4->Fill(5.,1.);
            if (HitChan[9] && HitChan[13] && HitChan[5]) h_NTripletHits4->Fill(6.,1.);
            if (HitChan[10] && HitChan[30] && HitChan[14]) h_NTripletHits4->Fill(7.,1.);
            if (HitChan[29] && HitChan[19] && HitChan[26]) h_NTripletHits4->Fill(8.,1.);
            if (HitChan[27] && HitChan[11] && HitChan[31]) h_NTripletHits4->Fill(9.,1.);
            if (HitChan[18] && HitChan[20] && HitChan[28]) h_NTripletHits4->Fill(10.,1.);
            if (HitChan[18] && HitChan[21] && HitChan[28]) h_NTripletHits4->Fill(11.,1.);
        } // 4 hits?

        // Fill counters of hit pairs within and between layers, which are used to determine rates and validate the trigger.
        if (HitChan[0]&&HitChan[8]) nCH0CH8++;
        if (HitChan[1]&&HitChan[9]) nCH1CH9++; 
        if (HitChan[0]&&HitChan[9]) nCH0CH9++;
        if (HitChan[1]&&HitChan[8]) nCH1CH8++;
        if (HitChan[6]&&HitChan[12]) nCH6CH12++; 
        if (HitChan[7]&&HitChan[13]) nCH7CH13++; 
        if (HitChan[6]&&HitChan[13]) nCH6CH13++; 
        if (HitChan[7]&&HitChan[12]) nCH7CH12++;
        if (HitChan[2]&&HitChan[4]) nCH2CH4++; 
        if (HitChan[3]&&HitChan[5]) nCH3CH5++; 
        if (HitChan[2]&&HitChan[5]) nCH2CH5++; 
        if (HitChan[3]&&HitChan[4]) nCH3CH4++; 
        if (HitChan[0]&&HitChan[6]) nCH0CH6++;
        if (HitChan[1]&&HitChan[7]) nCH1CH7++;
        if (HitChan[0]&&HitChan[7]) nCH0CH7++;
        if (HitChan[1]&&HitChan[6]) nCH1CH6++;
        if (HitChan[8]&&HitChan[12]) nCH8CH12++;
        if (HitChan[9]&&HitChan[13]) nCH9CH13++;
        if (HitChan[8]&&HitChan[13]) nCH8CH13++;
        if (HitChan[9]&&HitChan[12]) nCH9CH12++;
        if (HitChan[0]&&HitChan[12]) nCH0CH12++;
        if (HitChan[1]&&HitChan[13]) nCH1CH13++;
        if (HitChan[0]&&HitChan[13]) nCH0CH13++;
        if (HitChan[1]&&HitChan[12]) nCH1CH12++;
        if (HitChan[8]&&HitChan[6]) nCH8CH6++;
        if (HitChan[9]&&HitChan[7]) nCH9CH7++;
        if (HitChan[8]&&HitChan[7]) nCH8CH7++;
        if (HitChan[9]&&HitChan[6]) nCH9CH6++;
        if (HitChan[6]&&HitChan[2]) nCH6CH2++;
        if (HitChan[7]&&HitChan[3]) nCH7CH3++;
        if (HitChan[6]&&HitChan[3]) nCH6CH3++;
        if (HitChan[7]&&HitChan[2]) nCH7CH2++;
        if (HitChan[12]&&HitChan[4]) nCH12CH4++;
        if (HitChan[13]&&HitChan[5]) nCH13CH5++;
        if (HitChan[12]&&HitChan[5]) nCH12CH5++;
        if (HitChan[13]&&HitChan[4]) nCH13CH4++;
        if (HitChan[6]&&HitChan[4]) nCH6CH4++;
        if (HitChan[7]&&HitChan[5]) nCH7CH5++;
        if (HitChan[6]&&HitChan[5]) nCH6CH5++;
        if (HitChan[7]&&HitChan[4]) nCH7CH4++;
        if (HitChan[12]&&HitChan[2]) nCH12CH2++;
        if (HitChan[13]&&HitChan[3]) nCH13CH3++;
        if (HitChan[12]&&HitChan[3]) nCH12CH3++;
        if (HitChan[13]&&HitChan[2]) nCH13CH2++;
        if (HitChan[0]&&HitChan[8]&&HitChan[10]) nCH0CH8CH10++; // 3 hits per layer
        if (HitChan[1]&&HitChan[9]&&HitChan[10]) nCH1CH9CH10++;
        if (HitChan[0]&&HitChan[9]&&HitChan[10]) nCH0CH9CH10++;
        if (HitChan[1]&&HitChan[8]&&HitChan[10]) nCH1CH8CH10++;
        if (HitChan[6]&&HitChan[12]&&HitChan[30]) nCH6CH12CH30++;
        if (HitChan[7]&&HitChan[13]&&HitChan[30]) nCH7CH13CH30++;
        if (HitChan[2]&&HitChan[4]&&HitChan[14]) nCH2CH4CH14++;
        if (HitChan[3]&&HitChan[5]&&HitChan[14]) nCH3CH5CH14++;
        if (HitChan[2]&&HitChan[5]&&HitChan[14]) nCH2CH5CH14++;
        if (HitChan[3]&&HitChan[4]&&HitChan[14]) nCH3CH4CH14++;
        if (HitChan[0]&&HitChan[6]&&HitChan[2]) nCH0CH6CH2++; // Hits across 3 layers
        if (HitChan[1]&&HitChan[7]&&HitChan[3]) nCH1CH7CH3++;
        if (HitChan[0]&&HitChan[6]&&HitChan[3]) nCH0CH6CH3++;
        if (HitChan[1]&&HitChan[7]&&HitChan[2]) nCH1CH7CH2++;
        if (HitChan[0]&&HitChan[7]&&HitChan[2]) nCH0CH7CH2++;
        if (HitChan[1]&&HitChan[6]&&HitChan[3]) nCH1CH6CH3++;
        if (HitChan[8]&&HitChan[12]&&HitChan[4]) nCH8CH12CH4++;
        if (HitChan[9]&&HitChan[13]&&HitChan[5]) nCH9CH13CH5++;
        if (HitChan[8]&&HitChan[12]&&HitChan[5]) nCH8CH12CH5++;
        if (HitChan[9]&&HitChan[13]&&HitChan[4]) nCH9CH13CH4++;
        if (HitChan[8]&&HitChan[13]&&HitChan[4]) nCH8CH13CH4++;
        if (HitChan[9]&&HitChan[12]&&HitChan[5]) nCH9CH12CH5++;
        if (HitChan[0]&&HitChan[6]&&HitChan[4]) nCH0CH6CH4++;
        if (HitChan[0]&&HitChan[6]&&HitChan[5]) nCH0CH6CH5++;
        if (HitChan[1]&&HitChan[7]&&HitChan[5]) nCH1CH7CH5++;
        if (HitChan[1]&&HitChan[7]&&HitChan[4]) nCH1CH7CH4++;
        if (HitChan[11]&&HitChan[8]) nCH11CH8++; // Two hits in digitizer 1...
        if (HitChan[11]&&HitChan[9]) nCH11CH9++; 
        if (HitChan[13]&&HitChan[8]) nCH13CH8++; 
        if (HitChan[13]&&HitChan[9]) nCH13CH9++;
        if (HitChan[16]&&HitChan[30]) nCH16CH30++;
        if (HitChan[17]&&HitChan[30]) nCH17CH30++;
        if (HitChan[16]&&HitChan[19]) nCH16CH19++;
        if (HitChan[17]&&HitChan[19]) nCH17CH19++;
        if (HitChan[22]&&HitChan[15]) nCH22CH15++;
        if (HitChan[23]&&HitChan[15]) nCH23CH15++;
        if (HitChan[22]&&HitChan[10]) nCH22CH10++;
        if (HitChan[23]&&HitChan[10]) nCH23CH10++;
        if (HitChan[27]&&HitChan[24]&&HitChan[29]) nCH27CH24CH29++; // Three hits within a layer
        if (HitChan[27]&&HitChan[25]&&HitChan[29]) nCH27CH25CH29++;
        if (HitChan[30]&&HitChan[16]&&HitChan[19]) nCH30CH16CH19++;
        if (HitChan[30]&&HitChan[17]&&HitChan[19]) nCH30CH17CH19++;
        if (HitChan[31]&&HitChan[22]&&HitChan[26]) nCH31CH22CH26++;
        if (HitChan[31]&&HitChan[23]&&HitChan[26]) nCH31CH23CH26++;
        if (HitChan[24]&&HitChan[16]&&HitChan[22]) nCH24CH16CH22++; // Hits across 3 layers
        if (HitChan[24]&&HitChan[16]&&HitChan[23]) nCH24CH16CH23++;
        if (HitChan[24]&&HitChan[17]&&HitChan[23]) nCH24CH17CH23++;
        if (HitChan[24]&&HitChan[17]&&HitChan[22]) nCH24CH17CH22++;
        if (HitChan[25]&&HitChan[17]&&HitChan[23]) nCH25CH17CH23++;
        if (HitChan[25]&&HitChan[16]&&HitChan[23]) nCH25CH16CH23++;
        if (HitChan[25]&&HitChan[16]&&HitChan[22]) nCH25CH16CH22++;
        if (HitChan[18]&&HitChan[20]) nCH18CH20++; // Two hits between slabs
        if (HitChan[20]&&HitChan[28]) nCH20CH28++;
        if (HitChan[28]&&HitChan[21]) nCH28CH21++;
        if (HitChan[18]&&HitChan[28]) nCH18CH28++;
        if (HitChan[20]&&HitChan[21]) nCH20CH21++;
        if (HitChan[18]&&HitChan[21]) nCH18CH21++;
        if (HitChan[18]&&HitChan[20]&&HitChan[28]) nCH18CH20CH28++; // Hits across slab layers
        if (HitChan[20]&&HitChan[28]&&HitChan[21]) nCH20CH28CH21++;
        if (HitChan[18]&&HitChan[20]&&HitChan[28]&&HitChan[21]) nCH18CH20CH28CH21++; 
        if (HitChan[18]&&HitChan[20]&&HitChan[28]&&HitChan[21]&&
            HitChan[0]&&HitChan[6]&&HitChan[2]) nCH18CH20CH28CH21CH0CH6CH2++; 
        if (HitChan[18]&&HitChan[20]&&HitChan[28]&&HitChan[21]&&
            HitChan[1]&&HitChan[7]&&HitChan[3]) nCH18CH20CH28CH21CH1CH7CH3++; 
        if (HitChan[18]&&HitChan[20]&&HitChan[28]&&HitChan[21]&&
            HitChan[24]&&HitChan[16]&&HitChan[22]) nCH18CH20CH28CH21CH24CH16CH22++; 
        if (HitChan[18]&&HitChan[20]&&HitChan[28]&&HitChan[21]&&
            HitChan[25]&&HitChan[17]&&HitChan[23]) nCH18CH20CH28CH21CH25CH17CH23++; 
        if (HitChan[18]&&HitChan[20]&&HitChan[28]&&HitChan[21]&&
            HitChan[12]&&HitChan[4]) nCH18CH20CH28CH21CH12CH4++; 
        if (HitChan[18]&&HitChan[20]&&HitChan[28]&&HitChan[21]&&
            HitChan[9]&&HitChan[13]&&HitChan[5]) nCH18CH20CH28CH21CH9CH13CH5++; 
        if (HitChan[18]&&HitChan[20]&&HitChan[28]&&HitChan[21]&&
            (HitChan[0]||HitChan[1]||HitChan[24]||HitChan[25]||HitChan[8]||HitChan[9])&&
            (HitChan[6]||HitChan[7]||HitChan[16]||HitChan[17]||HitChan[12]||HitChan[13])&&
            (HitChan[2]||HitChan[3]||HitChan[22]||HitChan[23]||HitChan[4]||HitChan[5]) ) {
            nAllSlabsAllLayers++;
            if (evtCategoryCode==4) 
                cout << "AllSlabsAllLayers event: makeDisplays.py "<<RunNum<<" 1 -s "<<'"'<<"file=="<<filenum<<"&&event=="<<event<<'"'<<" -r 0 640 --noBounds --tag AllSlabsAllLayers\n";
        }
        if (HitChan[18]&&HitChan[20]&&HitChan[28]&&HitChan[21]&&
            (HitChan[0]||HitChan[1]||HitChan[24]||HitChan[25]||HitChan[8]||HitChan[9]||
             HitChan[6]||HitChan[7]||HitChan[16]||HitChan[17]||HitChan[12]||HitChan[13]||
             HitChan[2]||HitChan[3]||HitChan[22]||HitChan[23]||HitChan[4]||HitChan[5]) )
            nAllSlabsAnyLayer++;
        if ((HitChan[18]||HitChan[20]||HitChan[28]||HitChan[21])&&
            (HitChan[0]||HitChan[1]||HitChan[24]||HitChan[25]||HitChan[8]||HitChan[9])&&
            (HitChan[6]||HitChan[7]||HitChan[16]||HitChan[17]||HitChan[12]||HitChan[13])&&
            (HitChan[2]||HitChan[3]||HitChan[22]||HitChan[23]||HitChan[4]||HitChan[5]) )
            nAllLayersAnySlab++;
 


        // Dump an ANT for mergine with the hodoscope data
        if (evtCategoryCode==0 && RangeCode == "A") { // TS1 ANT
            cout <<setprecision(4);
            cout << "\nTS1:";
            cout << run<<" "; // 1
            cout << filenum<<" "; // 2
            cout << event<<" "; // 3
            cout << ia<<" "; // 4
            cout <<beam<<" "; // 5
            cout << long(1000*(event_time_fromTDC))<<" "; // 6; Event time in milliseconds
            cout << timeBetweenEvents<<" "; // 7; Time between events in microseconds
            cout << event_trigger_time_tag_b0 << " "; // 8; Time for digitizer 0
            cout << event_trigger_time_tag_b1 << " "; // 9; Time for digitizer 1
            cout << event_trigger_time_tag_b0-prev_event_trigger_time_tag_b0 << " "; // 10; Time between events for dig0
            cout << event_trigger_time_tag_b1-prev_event_trigger_time_tag_b1 << " "; // 11; Time between events for dig0
            prev_event_trigger_time_tag_b0 = event_trigger_time_tag_b0;
            prev_event_trigger_time_tag_b1 = event_trigger_time_tag_b1;
            cout << event_trigger_time_tag_b1-event_trigger_time_tag_b0<<" "; // 12; TTT mismatch between boards

            cout << groupTDC_b0->at(0) << " "; // 13; gTDC for digitizer 0
            cout << groupTDC_b1->at(0) << " "; // 14; gTDC for digitizer 1
            cout << groupTDC_b0->at(0)-prev_gTDC_b0 << " "; // 15; gTDC diff from prev event for dig 0
            cout << groupTDC_b1->at(0)-prev_gTDC_b1 << " "; // 16; gTDC diff from prev event for dig 0
            prev_gTDC_b0 = groupTDC_b0->at(0);
            prev_gTDC_b1 = groupTDC_b1->at(0);
            cout << groupTDC_b1->at(0)-groupTDC_b0->at(0) << " "; // 17; gTDC mismatch between boards

            for (int c=0; c<32; c++) {
                cout << " "<<maxSample[c];
                cout << " "<<TotalArea[c];
            }
            cout << "\n";
        } // TS1 ANT
    } //end over loop over all the events

    outFile->cd();
    outFile->Write();
    outFile->Close();

    if (RangeCode == "A") { // Report the rates for each combination of hits
        int nSeconds = int(0.5+runTime);
        int nX;
        nX = nCH0CH8; // Within a layer
        cout << "CombinedHits: "<<EventCategory<<" CH0+CH8 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH1CH9; 
        cout << "CombinedHits: "<<EventCategory<<" CH1+CH9 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH0CH9;
        cout << "CombinedHits: "<<EventCategory<<" CH0+CH9 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH1CH8;
        cout << "CombinedHits: "<<EventCategory<<" CH1+CH8 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH6CH12; 
        cout << "CombinedHits: "<<EventCategory<<" CH6+CH12 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH7CH13; 
        cout << "CombinedHits: "<<EventCategory<<" CH7+CH13 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH6CH13; 
        cout << "CombinedHits: "<<EventCategory<<" CH6+CH13 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH7CH12;
        cout << "CombinedHits: "<<EventCategory<<" CH7+CH12 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH2CH4; 
        cout << "CombinedHits: "<<EventCategory<<" CH2+CH4 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH3CH5; 
        cout << "CombinedHits: "<<EventCategory<<" CH3+CH5 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH2CH5; 
        cout << "CombinedHits: "<<EventCategory<<" CH2+CH5 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH3CH4; 
        cout << "CombinedHits: "<<EventCategory<<" CH3+CH4 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH0CH6;   // Between layers
        cout << "CombinedHits: "<<EventCategory<<" CH0+CH6 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH1CH7;
        cout << "CombinedHits: "<<EventCategory<<" CH1+CH7 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH0CH7;
        cout << "CombinedHits: "<<EventCategory<<" CH0+CH7 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH1CH6;
        cout << "CombinedHits: "<<EventCategory<<" CH1+CH6 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH8CH12;
        cout << "CombinedHits: "<<EventCategory<<" CH8+CH12 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH9CH13;
        cout << "CombinedHits: "<<EventCategory<<" CH9+CH13 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH8CH13;
        cout << "CombinedHits: "<<EventCategory<<" CH8+CH13 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH9CH12;
        cout << "CombinedHits: "<<EventCategory<<" CH9+CH12 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH0CH12;
        cout << "CombinedHits: "<<EventCategory<<" CH0+CH12 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH1CH13;
        cout << "CombinedHits: "<<EventCategory<<" CH1+CH13 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH0CH13;
        cout << "CombinedHits: "<<EventCategory<<" CH0+CH13 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH1CH12;
        cout << "CombinedHits: "<<EventCategory<<" CH1+CH12 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH8CH6;
        cout << "CombinedHits: "<<EventCategory<<" CH8+CH6 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH9CH7;
        cout << "CombinedHits: "<<EventCategory<<" CH9+CH7 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH8CH7;
        cout << "CombinedHits: "<<EventCategory<<" CH8+CH7 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH9CH6;
        cout << "CombinedHits: "<<EventCategory<<" CH9+CH6 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH6CH2;
        cout << "CombinedHits: "<<EventCategory<<" CH6+CH2 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH7CH3;
        cout << "CombinedHits: "<<EventCategory<<" CH7+CH3 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH6CH3;
        cout << "CombinedHits: "<<EventCategory<<" CH6+CH3 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH7CH2;
        cout << "CombinedHits: "<<EventCategory<<" CH7+CH2 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH12CH4;
        cout << "CombinedHits: "<<EventCategory<<" CH12+CH4 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH13CH5;
        cout << "CombinedHits: "<<EventCategory<<" CH13+CH5 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH12CH5;
        cout << "CombinedHits: "<<EventCategory<<" CH12+CH5 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH13CH4;
        cout << "CombinedHits: "<<EventCategory<<" CH13+CH4 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH6CH4;
        cout << "CombinedHits: "<<EventCategory<<" CH6+CH4 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH7CH5;
        cout << "CombinedHits: "<<EventCategory<<" CH7+CH5 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH6CH5;
        cout << "CombinedHits: "<<EventCategory<<" CH6+CH5 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH7CH4;
        cout << "CombinedHits: "<<EventCategory<<" CH7+CH4 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH12CH2;
        cout << "CombinedHits: "<<EventCategory<<" CH12+CH2 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH13CH3;
        cout << "CombinedHits: "<<EventCategory<<" CH13+CH3 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH12CH3;
        cout << "CombinedHits: "<<EventCategory<<" CH12+CH3 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH13CH2;
        cout << "CombinedHits: "<<EventCategory<<" CH13+CH2 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH0CH8CH10; // 3 hits per layer
        cout << "CombinedHits: "<<EventCategory<<" CH0+CH8+CH10 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH1CH9CH10;
        cout << "CombinedHits: "<<EventCategory<<" CH1+CH9+CH10 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH0CH9CH10;
        cout << "CombinedHits: "<<EventCategory<<" CH0+CH9+CH10 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH1CH8CH10;
        cout << "CombinedHits: "<<EventCategory<<" CH1+CH8+CH10 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH6CH12CH30;
        cout << "CombinedHits: "<<EventCategory<<" CH6+CH12+CH30 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH7CH13CH30;
        cout << "CombinedHits: "<<EventCategory<<" CH7+CH13+CH30 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH2CH4CH14;
        cout << "CombinedHits: "<<EventCategory<<" CH2+CH4+CH14 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH3CH5CH14;
        cout << "CombinedHits: "<<EventCategory<<" CH3+CH5+CH14 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH2CH5CH14;
        cout << "CombinedHits: "<<EventCategory<<" CH2+CH5+CH14 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH3CH4CH14;
        cout << "CombinedHits: "<<EventCategory<<" CH3+CH4+CH14 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH0CH6CH2; // Hits across 3 layers
        cout << "CombinedHits: "<<EventCategory<<" CH0+CH6+CH2 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH1CH7CH3;
        cout << "CombinedHits: "<<EventCategory<<" CH1+CH7+CH3 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH0CH6CH3;
        cout << "CombinedHits: "<<EventCategory<<" CH0+CH6+CH3 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH1CH7CH2;
        cout << "CombinedHits: "<<EventCategory<<" CH1+CH7+CH2 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH0CH7CH2;
        cout << "CombinedHits: "<<EventCategory<<" CH0+CH7+CH2 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH1CH6CH3;
        cout << "CombinedHits: "<<EventCategory<<" CH1+CH6+CH3 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH8CH12CH4;
        cout << "CombinedHits: "<<EventCategory<<" CH8+CH12+CH4 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH9CH13CH5;
        cout << "CombinedHits: "<<EventCategory<<" CH9+CH13+CH5 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH8CH12CH5;
        cout << "CombinedHits: "<<EventCategory<<" CH8+CH12+CH5 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH9CH13CH4;
        cout << "CombinedHits: "<<EventCategory<<" CH9+CH13+CH4 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH8CH13CH4;
        cout << "CombinedHits: "<<EventCategory<<" CH8+CH13+CH4 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH9CH12CH5;
        cout << "CombinedHits: "<<EventCategory<<" CH9+CH12+CH5 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH0CH6CH4;
        cout << "CombinedHits: "<<EventCategory<<" CH0+CH6+CH4 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH0CH6CH5;
        cout << "CombinedHits: "<<EventCategory<<" CH0+CH6+CH5 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH1CH7CH5;
        cout << "CombinedHits: "<<EventCategory<<" CH1+CH7+CH5 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH1CH7CH4;
        cout << "CombinedHits: "<<EventCategory<<" CH1+CH7+CH4 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH11CH8;
        cout << "CombinedHits: "<<EventCategory<<" CH11+CH8 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH11CH9; 
        cout << "CombinedHits: "<<EventCategory<<" CH11+CH9 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH13CH8; 
        cout << "CombinedHits: "<<EventCategory<<" CH13+CH8 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH13CH9;
        cout << "CombinedHits: "<<EventCategory<<" CH13+CH9 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH16CH30;
        cout << "CombinedHits: "<<EventCategory<<" CH16+CH30 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH17CH30;
        cout << "CombinedHits: "<<EventCategory<<" CH17+CH30 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH16CH19;
        cout << "CombinedHits: "<<EventCategory<<" CH16+CH19 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH17CH19;
        cout << "CombinedHits: "<<EventCategory<<" CH17+CH19 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH22CH15;
        cout << "CombinedHits: "<<EventCategory<<" CH22+CH15 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH23CH15;
        cout << "CombinedHits: "<<EventCategory<<" CH23+CH15 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH22CH10;
        cout << "CombinedHits: "<<EventCategory<<" CH22+CH10 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH23CH10;
        cout << "CombinedHits: "<<EventCategory<<" CH23+CH10 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH27CH24CH29; // Three hits within a layer
        cout << "CombinedHits: "<<EventCategory<<" CH27+CH24+CH29 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH27CH25CH29;
        cout << "CombinedHits: "<<EventCategory<<" CH27+CH25+CH29 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH30CH16CH19;
        cout << "CombinedHits: "<<EventCategory<<" CH30+CH16+CH19 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH30CH17CH19;
        cout << "CombinedHits: "<<EventCategory<<" CH30+CH17+CH19 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH31CH22CH26;
        cout << "CombinedHits: "<<EventCategory<<" CH31+CH22+CH26 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH31CH23CH26;
        cout << "CombinedHits: "<<EventCategory<<" CH31+CH23+CH26 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH24CH16CH22; // Hits across 3 layers
        cout << "CombinedHits: "<<EventCategory<<" CH24+CH16+CH22 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH24CH16CH23;
        cout << "CombinedHits: "<<EventCategory<<" CH24+CH16+CH23 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH24CH17CH23;
        cout << "CombinedHits: "<<EventCategory<<" CH24+CH17+CH23 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH24CH17CH22;
        cout << "CombinedHits: "<<EventCategory<<" CH24+CH17+CH22 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH25CH17CH23;
        cout << "CombinedHits: "<<EventCategory<<" CH25+CH17+CH23 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH25CH16CH23;
        cout << "CombinedHits: "<<EventCategory<<" CH25+CH16+CH23 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH25CH16CH22;
        cout << "CombinedHits: "<<EventCategory<<" CH25+CH16+CH22 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH18CH20; // Two hits between slabs
        cout << "CombinedHits: "<<EventCategory<<" CH18+CH20 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH20CH28;
        cout << "CombinedHits: "<<EventCategory<<" CH20+CH28 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH28CH21;
        cout << "CombinedHits: "<<EventCategory<<" CH28+CH21 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH18CH28;
        cout << "CombinedHits: "<<EventCategory<<" CH18+CH28 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH20CH21;
        cout << "CombinedHits: "<<EventCategory<<" CH20+CH21 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH18CH21;
        cout << "CombinedHits: "<<EventCategory<<" CH18+CH21 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH18CH20CH28; // Hits across slab layers
        cout << "CombinedHits: "<<EventCategory<<" CH18+CH20+CH28 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH20CH28CH21;
        cout << "CombinedHits: "<<EventCategory<<" CH20+CH28+CH21 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH18CH20CH28CH21; 
        cout << "CombinedHits: "<<EventCategory<<" CH18+CH20+CH28+CH21 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour. = "<<nX/totalLumi<<" +- "<<sqrt(nX)/totalLumi<<" per ipb.\n";
        nX = nCH18CH20CH28CH21CH0CH6CH2; 
        cout << "CombinedHits: "<<EventCategory<<" CH18+CH20+CH28+CH21+CH0+CH6+CH2 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH18CH20CH28CH21CH1CH7CH3; 
        cout << "CombinedHits: "<<EventCategory<<" CH18+CH20+CH28+CH21+CH1+CH7+CH3 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH18CH20CH28CH21CH24CH16CH22; 
        cout << "CombinedHits: "<<EventCategory<<" CH18+CH20+CH28+CH21+CH24+CH16+CH22 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH18CH20CH28CH21CH25CH17CH23; 
        cout << "CombinedHits: "<<EventCategory<<" CH18+CH20+CH28+CH21+CH25+CH17+CH23 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH18CH20CH28CH21CH12CH4; 
        cout << "CombinedHits: "<<EventCategory<<" CH18+CH20+CH28+CH21+CH12+CH4 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nCH18CH20CH28CH21CH9CH13CH5; 
        cout << "CombinedHits: "<<EventCategory<<" CH18+CH20+CH28+CH21+CH9+CH13+CH5 "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour.\n";
        nX = nAllSlabsAllLayers; 
        cout << "CombinedHits: "<<EventCategory<<" AllSlabsAllLayers "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour. = "<<nX/totalLumi<<" +- "<<sqrt(nX)/totalLumi<<" per ipb.\n";
        nX = nAllSlabsAnyLayer; 
        cout << "CombinedHits: "<<EventCategory<<" AllSlabsAnyLayer "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour. = "<<nX/totalLumi<<" +- "<<sqrt(nX)/totalLumi<<" per ipb.\n";
        nX = nAllLayersAnySlab; 
        cout << "CombinedHits: "<<EventCategory<<" AllLayersAnySlab "<<nX<<"/"<<nSeconds<<" = "<<nX*3600./nSeconds<<" +- "<<sqrt(nX)*3600./nSeconds<<" per hour. = "<<nX/totalLumi<<" +- "<<sqrt(nX)/totalLumi<<" per ipb.\n";
    }
}


bool isGoodEvent(int nHits, bool *HitChan, float *maxSample, TString EventCategory, TString LHCStatus, int RunNum) 
{
    bool GoodEvent = true;
    if (run==24 && event<20) GoodEvent = false;
    if (event==0 && filenum==1) GoodEvent = false; // The first event is sometimes buggy

    // Temporary code for veto panel stack test
    // Count the number of channels that have more than 7 mV in them. Mark the event as good for CosmicTag if there are at least 6 such channels.
    if ((EventCategory=="CosmicTag") && (RunNum>231 && RunNum<246)) {
        int nStackHits = 0;
        for (int c=0; c<32; c++)
            if (maxSample[c]>7.)
                nStackHits++;
        if (nStackHits>=6)
            GoodEvent = true;
        else
            GoodEvent = false;
    }

    if ((EventCategory == "All") && (nHits<1)) GoodEvent = false; // All category
    if ((EventCategory == "SPE") && (nHits>0)) GoodEvent = false; // SPE category; No hits above the threshold
    if ((EventCategory == "Small") && (nHits<2)) GoodEvent = false; // Small category
    if ((EventCategory == "SmallTag") && (nHits<1)) GoodEvent = false; // SmallTag category
    if ((EventCategory == "Cosmic" || EventCategory == "CosmicTag") && (nHits<2)) GoodEvent = false; // Cosmic category
    if ((EventCategory == "Thru" || EventCategory == "ThruTag") && !(HitChan[18] && HitChan[20] && HitChan[28] && HitChan[21])) GoodEvent = false; // Through going particle category
    
    // Veto events based on the LHCStatus string
    if (LHCStatus=="Beam" && !beam) GoodEvent = false;
    if (LHCStatus=="NoBeam" && beam) GoodEvent = false;
    return GoodEvent;
}

int bookHistograms(TString EventCategory, TString LHCStatus, TString RangeCode, int maxFile, double minTime, double maxTime) {
    int nhists = 0;

    TString ChStr[32];
    for (int c=0; c<32; c++) {
        std::ostringstream os;
        os << c;
        ChStr[c] = os.str();
    }

    // Bins and ranges
    double minHour = minTime/3600;
    double maxHour = maxTime/3600;
    int nBins = 0;
    float minX = 0, maxX = 0;

    // h_Max[32]
    // Plots of the max sample height, with several different range choices
    if (RangeCode == "A") { nBins = 140; minX = 0.; maxX = 1400.; }
    if (RangeCode == "B") { nBins = 50; minX = 0.; maxX = 500.; }
    if (RangeCode == "C") { nBins = 50; minX = 0.; maxX = 100.; }
    if (RangeCode == "D") { nBins = 40; minX = 0.; maxX = 40.; }
    for (int c=0; c<32; c++)
        h_Max[c] = new TH1D(EventCategory+"_"+LHCStatus+"_Max_"+ChStr[c]+"_"+RangeCode,"Max sample in Channel "+ChStr[c],nBins,minX,maxX);
    nhists += 32;

    // h_AfterPulseArea[32]
    // Plots of the after pulse area (1/1000) per channel, with several different range choices
    if (RangeCode == "A") { nBins = 200; minX = 0.; maxX = 100.; }
    if (RangeCode == "B") { nBins = 200; minX = 0.; maxX = 50.; }
    if (RangeCode == "C") { nBins = 50; minX = 0.; maxX = 2.; }
    if (RangeCode == "D") { nBins = 50; minX = 0.; maxX = 0.2; }
    for (int c=0; c<32; c++)
        h_AfterPulseArea[c] = new TH1D(EventCategory+"_"+LHCStatus+"_AfterPulseArea_"+ChStr[c]+"_"+RangeCode,"Area of afterpulses in Channel "+ChStr[c],nBins,minX,maxX);
    nhists += 32;

    // h_AfterPulseHeight[32]
    // Plots of the after pulse height per channel, with several different range choices
    if (RangeCode == "A") { nBins = 60; minX = 0.; maxX = 240.; }
    if (RangeCode == "B") { nBins = 60; minX = 0.; maxX = 60.; }
    if (RangeCode == "C") { nBins = 40; minX = 0.; maxX = 20.; }
    if (RangeCode == "D") { nBins = 45; minX = 0.; maxX = 15.; }
    for (int c=0; c<32; c++)
        h_AfterPulseHeight[c] = new TH1D(EventCategory+"_"+LHCStatus+"_AfterPulseHeight_"+ChStr[c]+"_"+RangeCode,"Height of afterpulses in Channel "+ChStr[c],nBins,minX,maxX);
    nhists += 32;

    // h_AfterPulseDuration[32]
    // Plots of the after pulse duration per channel, with several different range choices
    if (RangeCode == "A") { nBins = 128; minX = 0.; maxX = 640.; }
    if (RangeCode == "B") { nBins = 64; minX = 0.; maxX = 160.; }
    if (RangeCode == "C") { nBins = 32; minX = 0.; maxX = 40.; }
    if (RangeCode == "D") { nBins = 32; minX = 0.; maxX = 20.; }
    for (int c=0; c<32; c++)
        h_AfterPulseDuration[c] = new TH1D(EventCategory+"_"+LHCStatus+"_AfterPulseDuration_"+ChStr[c]+"_"+RangeCode,"Duration of afterpulses in Channel "+ChStr[c],nBins,minX,maxX);
    nhists += 32;

    // h_FirstPulseArea[32]
    // Plots of the first pulse area (1/1000) per channel, with several different range choices
    if (RangeCode == "A") { nBins = 400; minX = 0.; maxX = 200.; }
    if (RangeCode == "B") { nBins = 200; minX = 0.; maxX = 40.; }
    if (RangeCode == "C") { nBins = 250; minX = 0.; maxX = 5.; }
    if (RangeCode == "D") { nBins = 100; minX = 0.; maxX = 0.5; }
    for (int c=0; c<32; c++)
        h_FirstPulseArea[c] = new TH1D(EventCategory+"_"+LHCStatus+"_FirstPulseArea_"+ChStr[c]+"_"+RangeCode,"Area of first pulse in Channel "+ChStr[c],nBins,minX,maxX);
    nhists += 32;

    // h_FirstPulseNPE[32]
    // Plots of the first pulse NPE per channel, with several different range choices
    if (RangeCode == "A") { nBins = 400; minX = 0.; maxX = 1000.; }
    if (RangeCode == "B") { nBins = 200; minX = 0.; maxX = 100.; }
    if (RangeCode == "C") { nBins = 250; minX = 0.; maxX = 10.; }
    if (RangeCode == "D") { nBins = 60; minX = 0.; maxX = 3.; }
    for (int c=0; c<32; c++)
        h_FirstPulseNPE[c] = new TH1D(EventCategory+"_"+LHCStatus+"_FirstPulseNPE_"+ChStr[c]+"_"+RangeCode,"NPE of first pulse in Channel "+ChStr[c],nBins,minX,maxX);
    nhists += 32;

    // h_AfterPulseTime[32]
    // Plots of the afterpulse time, wrt first pulse, per channel, with several different range choices
    if (RangeCode == "A") { nBins = 1024; minX = 0.; maxX = 2*1024*0.625; }
    if (RangeCode == "B") { nBins = 512; minX = 0.; maxX = 2*1024*0.625; }
    if (RangeCode == "C") { nBins = 128; minX = 0.; maxX = 1024*0.625; }
    if (RangeCode == "D") { nBins = 100; minX = 100.; maxX = 300.; }
    for (int c=0; c<32; c++)
        h_AfterPulseTime[c] = new TH1D(EventCategory+"_"+LHCStatus+"_AfterPulseTime_"+ChStr[c]+"_"+RangeCode,"Time delay of afterpulses in Channel "+ChStr[c],nBins,minX,maxX);
    nhists += 32;

    // h_FirstPulseHeight[32]
    // Plots of the first pulse height per channel, with several different range choices
    if (RangeCode == "A") { nBins = 260; minX = 0.; maxX = 1300.; }
    if (RangeCode == "B") { nBins = 200; minX = 0.; maxX = 500.; }
    if (RangeCode == "C") { nBins = 150; minX = 0.; maxX = 150.; }
    if (RangeCode == "D") { nBins = 120; minX = 0.; maxX = 40.; }
    for (int c=0; c<32; c++)
        h_FirstPulseHeight[c] = new TH1D(EventCategory+"_"+LHCStatus+"_FirstPulseHeight_"+ChStr[c]+"_"+RangeCode,"Height of first pulse in Channel "+ChStr[c],nBins,minX,maxX);
    nhists += 32;

    // h_FirstDuration[32]
    // Plots of the first pulse duration per channel, with several different range choices
    if (RangeCode == "A") { nBins = 128; minX = 0.; maxX = 640.; }
    if (RangeCode == "B") { nBins = 64; minX = 0.; maxX = 160.; }
    if (RangeCode == "C") { nBins = 32; minX = 0.; maxX = 40.; }
    if (RangeCode == "D") { nBins = 32; minX = 0.; maxX = 20.; }
    for (int c=0; c<32; c++)
        h_FirstDuration[c] = new TH1D(EventCategory+"_"+LHCStatus+"_FirstPulseDuration_"+ChStr[c]+"_"+RangeCode,"Duration of first pulse in Channel "+ChStr[c],nBins,minX,maxX);
    nhists += 32;

    // Plots of the first pulse time per channel, with several different range choices
    // h_FirstTime[32]
    if (RangeCode == "A") { nBins = 512; minX = 0.; maxX = 1024*0.625; }
    if (RangeCode == "B") { nBins = 50; minX = 0.; maxX = 200.; }
    if (RangeCode == "C") { nBins = 50; minX = 150.; maxX = 300.; }
    if (RangeCode == "D") { nBins = 50; minX = 300.; maxX = 450.; }
    for (int c=0; c<32; c++)
        h_FirstTime[c] = new TH1D(EventCategory+"_"+LHCStatus+"_FirstPulseTime_"+ChStr[c]+"_"+RangeCode,"Time of first pulse in Channel "+ChStr[c],nBins,minX,maxX);
    nhists += 32;

    // h_LHCTime[32]
    // h_LHCTimeCalib[32]
    // Plots of the time difference wrt the closest LHC clock pulse
    if (RangeCode == "A") { nBins = 50; minX = -25.; maxX = 25.; }
    if (RangeCode == "B") { nBins = 30; minX = -15.; maxX = 15.; }
    if (RangeCode == "C") { nBins = 15; minX = -15.; maxX = 15.; }
    if (RangeCode == "D") { nBins = 10; minX = -15.; maxX = 15.; }
    for (int c=0; c<32; c++) {
        h_LHCTime[c] = new TH1D(EventCategory+"_"+LHCStatus+"_LHCTime_"+ChStr[c]+"_"+RangeCode,"Time wrt LHC clock of largest pulse in Channel "+ChStr[c],nBins,minX,maxX);
        h_LHCTimeCalib[c] = new TH1D(EventCategory+"_"+LHCStatus+"_LHCTimeCalib_"+ChStr[c]+"_"+RangeCode,"Calibrated time wrt LHC clock of largest pulse in Channel "+ChStr[c],nBins,minX,maxX);
    }
    nhists += 32*2;

    // h_TimeWRTCH18[32], h_TimeCalibWRTCH18[32], h_TimeWRTCH20[32], h_TimeCalibWRTCH20[32]
    // h_TimeWRTCH28[32], h_TimeCalibWRTCH28[32], h_TimeWRTCH21[32], h_TimeCalibWRTCH21[32]
    // h_TimeWRTCH7[32], h_TimeCalibWRTCH7[32], h_TimeWRTCH0[32], h_TimeCalibWRTCH0[32]
    // h_TimeWRTCH1[32], h_TimeCalibWRTCH1[32], h_TimeWRTCH2[32], h_TimeCalibWRTCH2[32]
    // h_TimeWRTCH3[32], h_TimeCalibWRTCH3[32], h_TimeWRTCH4[32], h_TimeCalibWRTCH4[32]
    // Plots of the time difference between each channel's hit and a hit in specific other channels.
    // I compare to each of the slabs (18,20,28,21) and to the top right corner bar in each layer (1,7,3)
    // Compare only the largest pulse in each channel.
    if (RangeCode == "A") { nBins = 200; minX = -200.; maxX = 200.; }
    if (RangeCode == "B") { nBins = 50; minX = -200.; maxX = 200.; }
    if (RangeCode == "C") { nBins = 50; minX = -50.; maxX = 50.; }
    if (RangeCode == "D") { nBins = 30; minX = -30.; maxX = 30.; }
    for (int c=0; c<32; c++) {
        h_TimeWRTCH18[c] = new TH1D(EventCategory+"_"+LHCStatus+"_TimeWRTCH18_"+ChStr[c]+"_"+RangeCode,"Time wrt CH18 for largest pulse in Channel "+ChStr[c],nBins,minX,maxX);
        h_TimeCalibWRTCH18[c] = new TH1D(EventCategory+"_"+LHCStatus+"_TimeCalibWRTCH18_"+ChStr[c]+"_"+RangeCode,"Calibrated time wrt CH18 for largest pulse in Channel "+ChStr[c],nBins,minX,maxX);
        h_TimeWRTCH20[c] = new TH1D(EventCategory+"_"+LHCStatus+"_TimeWRTCH20_"+ChStr[c]+"_"+RangeCode,"Time wrt CH20 for largest pulse in Channel "+ChStr[c],nBins,minX,maxX);
        h_TimeCalibWRTCH20[c] = new TH1D(EventCategory+"_"+LHCStatus+"_TimeCalibWRTCH20_"+ChStr[c]+"_"+RangeCode,"Calibrated time wrt CH20 for largest pulse in Channel "+ChStr[c],nBins,minX,maxX);
        h_TimeWRTCH28[c] = new TH1D(EventCategory+"_"+LHCStatus+"_TimeWRTCH28_"+ChStr[c]+"_"+RangeCode,"Time wrt CH28 for largest pulse in Channel "+ChStr[c],nBins,minX,maxX);
        h_TimeCalibWRTCH28[c] = new TH1D(EventCategory+"_"+LHCStatus+"_TimeCalibWRTCH28_"+ChStr[c]+"_"+RangeCode,"Calibrated time wrt CH28 for largest pulse in Channel "+ChStr[c],nBins,minX,maxX);
        h_TimeWRTCH21[c] = new TH1D(EventCategory+"_"+LHCStatus+"_TimeWRTCH21_"+ChStr[c]+"_"+RangeCode,"Time wrt CH21 for largest pulse in Channel "+ChStr[c],nBins,minX,maxX);
        h_TimeCalibWRTCH21[c] = new TH1D(EventCategory+"_"+LHCStatus+"_TimeCalibWRTCH21_"+ChStr[c]+"_"+RangeCode,"Calibrated time wrt CH21 for largest pulse in Channel "+ChStr[c],nBins,minX,maxX);
        h_TimeWRTCH7[c] = new TH1D(EventCategory+"_"+LHCStatus+"_TimeWRTCH7_"+ChStr[c]+"_"+RangeCode,"Time wrt CH7 for largest pulse in Channel "+ChStr[c],nBins,minX,maxX);
        h_TimeCalibWRTCH7[c] = new TH1D(EventCategory+"_"+LHCStatus+"_TimeCalibWRTCH7_"+ChStr[c]+"_"+RangeCode,"Calibrated time wrt CH7 for largest pulse in Channel "+ChStr[c],nBins,minX,maxX);
        h_TimeWRTCH0[c] = new TH1D(EventCategory+"_"+LHCStatus+"_TimeWRTCH0_"+ChStr[c]+"_"+RangeCode,"Time wrt CH0 for largest pulse in Channel "+ChStr[c],nBins,minX,maxX);
        h_TimeCalibWRTCH0[c] = new TH1D(EventCategory+"_"+LHCStatus+"_TimeCalibWRTCH0_"+ChStr[c]+"_"+RangeCode,"Calibrated time wrt CH0 for largest pulse in Channel "+ChStr[c],nBins,minX,maxX);
        h_TimeWRTCH1[c] = new TH1D(EventCategory+"_"+LHCStatus+"_TimeWRTCH1_"+ChStr[c]+"_"+RangeCode,"Time wrt CH1 for largest pulse in Channel "+ChStr[c],nBins,minX,maxX);
        h_TimeCalibWRTCH1[c] = new TH1D(EventCategory+"_"+LHCStatus+"_TimeCalibWRTCH1_"+ChStr[c]+"_"+RangeCode,"Calibrated time wrt CH1 for largest pulse in Channel "+ChStr[c],nBins,minX,maxX);
        h_TimeWRTCH2[c] = new TH1D(EventCategory+"_"+LHCStatus+"_TimeWRTCH2_"+ChStr[c]+"_"+RangeCode,"Time wrt CH2 for largest pulse in Channel "+ChStr[c],nBins,minX,maxX);
        h_TimeCalibWRTCH2[c] = new TH1D(EventCategory+"_"+LHCStatus+"_TimeCalibWRTCH2_"+ChStr[c]+"_"+RangeCode,"Calibrated time wrt CH2 for largest pulse in Channel "+ChStr[c],nBins,minX,maxX);
        h_TimeWRTCH3[c] = new TH1D(EventCategory+"_"+LHCStatus+"_TimeWRTCH3_"+ChStr[c]+"_"+RangeCode,"Time wrt CH3 for largest pulse in Channel "+ChStr[c],nBins,minX,maxX);
        h_TimeCalibWRTCH3[c] = new TH1D(EventCategory+"_"+LHCStatus+"_TimeCalibWRTCH3_"+ChStr[c]+"_"+RangeCode,"Calibrated time wrt CH3 for largest pulse in Channel "+ChStr[c],nBins,minX,maxX);
        h_TimeWRTCH4[c] = new TH1D(EventCategory+"_"+LHCStatus+"_TimeWRTCH4_"+ChStr[c]+"_"+RangeCode,"Time wrt CH4 for largest pulse in Channel "+ChStr[c],nBins,minX,maxX);
        h_TimeCalibWRTCH4[c] = new TH1D(EventCategory+"_"+LHCStatus+"_TimeCalibWRTCH4_"+ChStr[c]+"_"+RangeCode,"Calibrated time wrt CH4 for largest pulse in Channel "+ChStr[c],nBins,minX,maxX);
    }
    nhists += 32*20;

    // h_TotalPulseArea[32]
    // Plots of the total pulse area (1/1000) per channel, with several different range choices
    if (RangeCode == "A") { nBins = 100; minX = 0.; maxX = 300.; }
    if (RangeCode == "B") { nBins = 100; minX = 0.; maxX = 80.; }
    if (RangeCode == "C") { nBins = 100; minX = 0.; maxX = 10.; }
    if (RangeCode == "D") { nBins = 100; minX = 0.; maxX = 2.; }
    for (int c=0; c<32; c++)
        h_TotalPulseArea[c] = new TH1D(EventCategory+"_"+LHCStatus+"_TotalPulseArea_"+ChStr[c]+"_"+RangeCode,"Total area of pulses in Channel "+ChStr[c],nBins,minX,maxX);

    // h_NPulses[32]
    // Plots of the number of pulses per channel, with several different range choices
    if (RangeCode == "A") { nBins = 20; minX = 0.; maxX = 20.; }
    if (RangeCode == "B") { nBins = 10; minX = 0.; maxX = 10.; }
    if (RangeCode == "C") { nBins = 5; minX = 0.; maxX = 5.; }
    if (RangeCode == "D") { nBins = 3; minX = 0.; maxX = 3.; }
    for (int c=0; c<32; c++)
        h_NPulses[c] = new TH1D(EventCategory+"_"+LHCStatus+"_NPulses_"+ChStr[c]+"_"+RangeCode,"Number of pulses in Channel "+ChStr[c],nBins,minX,maxX);
    nhists += 32;

    // h_NPairedHits[32]
    // Plots of paired hits in other channels when this channel is hit
    if (RangeCode == "A") { nBins = 34; minX = -0.5; maxX = 33.5; }
    if (RangeCode == "B") { nBins = 18; minX = -0.5; maxX = 17.5; }
    if (RangeCode == "C") { nBins = 18; minX = 15.5; maxX = 33.5; }
    if (RangeCode == "D") { nBins = 36; minX = -0.5; maxX = 35.5; }
    for (int c=0; c<32; c++)
        h_NPairedHits[c] = new TH1D(EventCategory+"_"+LHCStatus+"_NPairedHits_"+ChStr[c]+"_"+RangeCode,"Number of coincident hits in other channels for Channel "+ChStr[c],nBins,minX,maxX);
    nhists += 32;

    ///////////// Plots that are not channel dependent
    // Plots of hit triplets when no other channel is hit
    // Bins are as follows:
    //  1 = CH0-6-2
    //  2 = CH1-7-3
    //  3 = CH24-16-22
    //  4 = CH25-17-23
    //  5 = CH8-12-4
    //  6 = CH9-13-5
    //  7 = CH10-30-14
    //  8 = CH29-19-26
    //  9 = CH27-11-31
    // 10 = CH18-20-28
    // 11 = CH18-21-28

    // h_NTripletHits
    // h_NTripletHits3
    // h_NTripletHits4
    if (RangeCode == "A") { nBins = 15; minX = -0.5; maxX = 14.5; }
    if (RangeCode == "B") { nBins = 30; minX = -0.5; maxX = 14.5; }
    if (RangeCode == "C") { nBins = 15; minX = -0.5; maxX = 14.5; }
    if (RangeCode == "D") { nBins = 15; minX = -0.5; maxX = 14.5; }
    h_NTripletHits = new TH1D(EventCategory+"_"+LHCStatus+"_NTripletHits_"+RangeCode,"Number of triplet hits ",nBins,minX,maxX);
    h_NTripletHits3 = new TH1D(EventCategory+"_"+LHCStatus+"_NTripletHits3_"+RangeCode,"Number of triplet hits in 3 hit events ",nBins,minX,maxX);
    h_NTripletHits4 = new TH1D(EventCategory+"_"+LHCStatus+"_NTripletHits4_"+RangeCode,"Number of triplet hits in 4 hit events",nBins,minX,maxX);
    nhists += 3;

    // h_NHitBars
    // Plots of number of hit bars
    if (RangeCode == "A") { nBins = 34; minX = -0.5; maxX = 33.5; }
    if (RangeCode == "B") { nBins = 18; minX = -0.5; maxX = 17.5; }
    if (RangeCode == "C") { nBins = 18; minX = 15.5; maxX = 33.5; }
    if (RangeCode == "D") { nBins = 36; minX = -0.5; maxX = 35.5; }
    h_NHitBars = new TH1D(EventCategory+"_"+LHCStatus+"_NHitBars_"+RangeCode,"Number of hit bars",nBins,minX,maxX);
    ++nhists;

    // h_NHitLayers
    // Plots of number of hit layers (bars only, not slabs or panels)
    if (RangeCode == "A") { nBins = 4; minX = -0.5; maxX = 3.5; }
    if (RangeCode == "B") { nBins = 4; minX = -0.5; maxX = 3.5; }
    if (RangeCode == "C") { nBins = 4; minX = -0.5; maxX = 3.5; }
    if (RangeCode == "D") { nBins = 4; minX = -0.5; maxX = 3.5; }
    h_NHitLayers = new TH1D(EventCategory+"_"+LHCStatus+"_NHitLayers_"+RangeCode,"Number of layers with hit bars",nBins,minX,maxX);
    ++nhists;

    // h_TotalGlobalPulseArea
    // Plots of the total pulse area (1/1000) across the whole detector
    if (RangeCode == "A") { nBins = 100; minX = 0.; maxX = 2000.; }
    if (RangeCode == "B") { nBins = 100; minX = 0.; maxX = 500.; }
    if (RangeCode == "C") { nBins = 100; minX = 0.; maxX = 200.; }
    if (RangeCode == "D") { nBins = 100; minX = 0.; maxX = 50.; }
    h_TotalGlobalPulseArea = new TH1D(EventCategory+"_"+LHCStatus+"_TotalGlobalPulseArea_"+RangeCode,"Total area of all pulses across detector",nBins,minX,maxX);
    ++nhists;

    // h_EventTime[32]
    if (RangeCode == "A") { nBins = 1000; minX = minHour - 0.5; maxX = maxHour + 2.; }
    if (RangeCode == "B") { nBins = 200; minX = minHour - 0.5; maxX = maxHour + 2.; }
    if (RangeCode == "C") { nBins = 60; minX = minHour - 0.5; maxX = maxHour + 2.; }
    if (RangeCode == "D") { nBins = 10; minX = minHour - 0.5; maxX = maxHour + 2.; }
    for (int c=0; c<32; c++)
        h_EventTime[c] = new TH1D(EventCategory+"_"+LHCStatus+"_EventTime_"+ChStr[c]+"_"+RangeCode,"Time of events with a hit in Channel "+ChStr[c],nBins,minX,maxX);
    nhists += 32;

    // h_EventTimeSeconds[32]
    if (RangeCode == "A") { nBins = 500; minX = 0.; maxX = 1.2*(maxTime-minTime); }
    if (RangeCode == "B") { nBins = 200; minX = 0.; maxX = 1.2*(maxTime-minTime); }
    if (RangeCode == "C") { nBins = 60; minX = 0.; maxX = 1.2*(maxTime-minTime); }
    if (RangeCode == "D") { nBins = 10; minX = 0.; maxX = 1.2*(maxTime-minTime); }
    for (int c=0; c<32; c++)
        h_EventTimeSeconds[c] = new TH1D(EventCategory+"_"+LHCStatus+"_EventTimeSeconds_"+ChStr[c]+"_"+RangeCode,"Seconds into run for events with a hit in Channel"+ChStr[c],nBins,minX,maxX);
    nhists += 32;

    // h_EventTimeSynchedSeconds[32]
    if (RangeCode == "A") { nBins = 500; minX = 0.; maxX = 1.2*(maxTime-minTime); }
    if (RangeCode == "B") { nBins = 200; minX = 0.; maxX = 1.2*(maxTime-minTime); }
    if (RangeCode == "C") { nBins = 60; minX = 0.; maxX = 1.2*(maxTime-minTime); }
    if (RangeCode == "D") { nBins = 10; minX = 0.; maxX = 1.2*(maxTime-minTime); }
    for (int c=0; c<32; c++)
        h_EventTimeSynchedSeconds[c] = new TH1D(EventCategory+"_"+LHCStatus+"_EventTimeSynchedSeconds_"+ChStr[c]+"_"+RangeCode,"Seconds into run for synched events with a hit in Channel"+ChStr[c],nBins,minX,maxX);
    nhists += 32;

    // h_EventTimeUnsynchedSeconds[32]
    if (RangeCode == "A") { nBins = 500; minX = 0.; maxX = 1.2*(maxTime-minTime); }
    if (RangeCode == "B") { nBins = 200; minX = 0.; maxX = 1.2*(maxTime-minTime); }
    if (RangeCode == "C") { nBins = 60; minX = 0.; maxX = 1.2*(maxTime-minTime); }
    if (RangeCode == "D") { nBins = 10; minX = 0.; maxX = 1.2*(maxTime-minTime); }
    for (int c=0; c<32; c++)
        h_EventTimeUnsynchedSeconds[c] = new TH1D(EventCategory+"_"+LHCStatus+"_EventTimeUnsynchedSeconds_"+ChStr[c]+"_"+RangeCode,"Seconds into run for unsynched events with a hit in Channel"+ChStr[c],nBins,minX,maxX);
    nhists += 32;

    // h_FileNum[32]
    if (RangeCode == "A") { nBins = maxFile+5; minX = - 0.5; maxX = maxFile + 4.5; }
    if (RangeCode == "B") { nBins = maxFile+5; minX = - 0.5; maxX = maxFile + 4.5; }
    if (RangeCode == "C") { nBins = maxFile+5; minX = - 0.5; maxX = maxFile + 4.5; }
    if (RangeCode == "D") { nBins = maxFile+5; minX = - 0.5; maxX = maxFile + 4.5; }
    for (int c=0; c<32; c++)
        h_FileNum[c] = new TH1D(EventCategory+"_"+LHCStatus+"_FileNum_"+ChStr[c]+"_"+RangeCode,"Filenumber of events with a hit in Channel "+ChStr[c],nBins,minX,maxX);
    nhists += 32;

    // Histograms of the sideband mean
    // h_SidebandMean[32]
    if (RangeCode == "A") { nBins = 1000; minX = -20.; maxX = 20.; }
    if (RangeCode == "B") { nBins = 200; minX = -10.; maxX = 10.; }
    if (RangeCode == "C") { nBins = 100; minX = -5.; maxX = 5.; }
    if (RangeCode == "D") { nBins = 80; minX = -2.; maxX = 2.; }
    for (int c=0; c<32; c++)
        h_SidebandMean[c] = new TH1D(EventCategory+"_"+LHCStatus+"_SidebandMean_"+ChStr[c]+"_"+RangeCode,"Sideband mean in Channel "+ChStr[c],nBins,minX,maxX);
    nhists += 32;

    // Histograms of the sideband RMS
    // h_SidebandRMS[32]
    if (RangeCode == "A") { nBins = 1000; minX = 0.; maxX = 20.; }
    if (RangeCode == "B") { nBins = 200; minX = 0.; maxX = 10.; }
    if (RangeCode == "C") { nBins = 100; minX = 0.; maxX = 5.; }
    if (RangeCode == "D") { nBins = 80; minX = 0.; maxX = 2.; }
    for (int c=0; c<32; c++)
        h_SidebandRMS[c] = new TH1D(EventCategory+"_"+LHCStatus+"_SidebandRMS_"+ChStr[c]+"_"+RangeCode,"Sideband RMS in Channel "+ChStr[c],nBins,minX,maxX);
    nhists += 32;

    // Plots of the max sample height for tagged channels, with several different range choices
    // h_TaggedMax[32]
    if (RangeCode == "A") { nBins = 70; minX = 0.; maxX = 1400.; }
    if (RangeCode == "B") { nBins = 50; minX = 0.; maxX = 500.; }
    if (RangeCode == "C") { nBins = 25; minX = 0.; maxX = 100.; }
    if (RangeCode == "D") { nBins = 20; minX = 0.; maxX = 40.; }
    for (int c=0; c<32; c++)
        h_TaggedMax[c] = new TH1D(EventCategory+"_"+LHCStatus+"_TaggedMax_"+ChStr[c]+"_"+RangeCode,"Max sample in tagged Channel "+ChStr[c],nBins,minX,maxX);
    nhists += 32;

    // Plots of the tagged pulse area (1/1000) per channel, with several different range choices
    // h_TaggedPulseArea[32]
    if (RangeCode == "A") { nBins = 100; minX = 0.; maxX = 200.; }
    if (RangeCode == "B") { nBins = 100; minX = 0.; maxX = 100.; }
    if (RangeCode == "C") { nBins = 50; minX = 0.; maxX = 25.; }
    if (RangeCode == "D") { nBins = 50; minX = 0.; maxX = 5.; }
    for (int c=0; c<32; c++)
        h_TaggedPulseArea[c] = new TH1D(EventCategory+"_"+LHCStatus+"_TaggedPulseArea_"+ChStr[c]+"_"+RangeCode,"Area of neighbor tagged pulse in Channel "+ChStr[c],nBins,minX,maxX);
    nhists += 32;

    // Plots of the NPE for tagged channels, with several different range choices
    // h_TaggedPulseNPE[32]
    if (RangeCode == "A") { nBins = 100; minX = 0.; maxX = 10000.; }
    if (RangeCode == "B") { nBins = 50; minX = 0.; maxX = 200.; }
    if (RangeCode == "C") { nBins = 50; minX = 0.; maxX = 50.; }
    if (RangeCode == "D") { nBins = 50; minX = 0.; maxX = 10.; }
    for (int c=0; c<32; c++)
        h_TaggedPulseNPE[c] = new TH1D(EventCategory+"_"+LHCStatus+"_TaggedPulseNPE_"+ChStr[c]+"_"+RangeCode,"NPE of tagged pulse in Channel "+ChStr[c],nBins,minX,maxX);
    nhists += 32;

    // Plots of the tagged total pulse area (1/1000) per channel, with several different range choices
    // h_TaggedTotalPulseArea[32]
    if (RangeCode == "A") { nBins = 100; minX = 0.; maxX = 200.; }
    if (RangeCode == "B") { nBins = 100; minX = 0.; maxX = 100.; }
    if (RangeCode == "C") { nBins = 100; minX = 0.; maxX = 25.; }
    if (RangeCode == "D") { nBins = 100; minX = 0.; maxX = 5.; }
    for (int c=0; c<32; c++)
        h_TaggedTotalPulseArea[c] = new TH1D(EventCategory+"_"+LHCStatus+"_TaggedTotalPulseArea_"+ChStr[c]+"_"+RangeCode,"Total area of neighbor tagged pulses in Channel "+ChStr[c],nBins,minX,maxX);
    nhists += 32;

    // Plots of the tagged pulse height per channel, with several different range choices
    // h_TaggedPulseHeight[32]
    if (RangeCode == "A") { nBins = 130; minX = 0.; maxX = 1300.; }
    if (RangeCode == "B") { nBins = 100; minX = 0.; maxX = 500.; }
    if (RangeCode == "C") { nBins = 50; minX = 0.; maxX = 150.; }
    if (RangeCode == "D") { nBins = 40; minX = 0.; maxX = 40.; }
    for (int c=0; c<32; c++) {
        h_TaggedPulseHeight[c] = new TH1D(EventCategory+"_"+LHCStatus+"_TaggedPulseHeight_"+ChStr[c]+"_"+RangeCode,"Height of neighbor tagged pulse in Channel "+ChStr[c],nBins,minX,maxX);
    }
    nhists += 32;

    // Plots of the tagged pulse duration per channel, with several different range choices
    // h_TaggedDuration[32]
    if (RangeCode == "A") { nBins = 128; minX = 0.; maxX = 640.; }
    if (RangeCode == "B") { nBins = 64; minX = 0.; maxX = 160.; }
    if (RangeCode == "C") { nBins = 32; minX = 0.; maxX = 40.; }
    if (RangeCode == "D") { nBins = 32; minX = 0.; maxX = 20.; }
    for (int c=0; c<32; c++)
        h_TaggedDuration[c] = new TH1D(EventCategory+"_"+LHCStatus+"_TaggedPulseDuration_"+ChStr[c]+"_"+RangeCode,"Duration of neighbor tagged pulse in Channel "+ChStr[c],nBins,minX,maxX);
    nhists += 32;

    // Plots of the pulse height in each channel that is part of a three-fold coincidence with its inter-layer partners
    // h_TripleLayerMax[32]
    if (RangeCode == "A") { nBins = 140; minX = 0.; maxX = 1400.; }
    if (RangeCode == "B") { nBins = 50; minX = 0.; maxX = 500.; }
    if (RangeCode == "C") { nBins = 50; minX = 0.; maxX = 100.; }
    if (RangeCode == "D") { nBins = 40; minX = 0.; maxX = 40.; }

    TString partnerThresholdStr = " 10mVPartnerThreshold";
    if (EventCategory == "SPE") partnerThresholdStr = " 20mVPartnerThreshold";
    if (EventCategory == "Small" || EventCategory == "SmallTag") partnerThresholdStr = " 30mVPartnerThreshold";
    if (EventCategory == "Cosmic" || EventCategory == "CosmicTag") partnerThresholdStr = " 40mVPartnerThreshold";
    if (EventCategory == "Thru" || EventCategory == "ThruTag") partnerThresholdStr = " 50mVPartnerThreshold";
    for (int c=0; c<32; c++)
        h_TripleLayerMax[c] = new TH1D(EventCategory+"_"+LHCStatus+"_TripleLayerMax_"+ChStr[c]+"_"+RangeCode,"Max sample in TripleLayer Channel "+ChStr[c]+partnerThresholdStr,nBins,minX,maxX);
    nhists += 32;

    // Plots of the pulse height in each channel that is part of a two-fold coincidence with its inter-layer partners
    // h_DoubleLayerMax[32]
    if (RangeCode == "A") { nBins = 140; minX = 0.; maxX = 1400.; }
    if (RangeCode == "B") { nBins = 50; minX = 0.; maxX = 500.; }
    if (RangeCode == "C") { nBins = 50; minX = 0.; maxX = 100.; }
    if (RangeCode == "D") { nBins = 40; minX = 0.; maxX = 40.; }
    for (int c=0; c<32; c++)
        h_DoubleLayerMax[c] = new TH1D(EventCategory+"_"+LHCStatus+"_DoubleLayerMax_"+ChStr[c]+"_"+RangeCode,"Max sample in DoubleLayer Channel "+ChStr[c]+partnerThresholdStr,nBins,minX,maxX);
    nhists += 32;

    
    /*******************************************************************************************************************************************************
    ****                                                                                                                                                ****
    ****                                              BOOK HISTOS FOR COSMICS STUDY                                                                     ****
    ****                                                                                                                                                ****
    *******************************************************************************************************************************************************/

    if (RangeCode == "A") { nBins = 140; minX = 0.; maxX = 1400.; }
    if (RangeCode == "B") { nBins = 50; minX = 0.; maxX = 500.; }
    if (RangeCode == "C") { nBins = 50; minX = 0.; maxX = 100.; }
    if (RangeCode == "D") { nBins = 40; minX = 0.; maxX = 40.; }
    for (int c=0; c<32; c++) {
        h_pulseHeight[c] = new TH1D(EventCategory+"_"+LHCStatus+"_pulseHeight_"+ChStr[c]+"_"+RangeCode,"Height of each pulse in channel"+ChStr[c]+partnerThresholdStr,nBins,minX,maxX);;
        h_firstPulseHeight[c] = new TH1D(EventCategory+"_"+LHCStatus+"_firstPulseHeight_"+ChStr[c]+"_"+RangeCode,"Height of first pulse in channel"+ChStr[c]+partnerThresholdStr,nBins,minX,maxX);;
        h_maxPulseHeight[c] = new TH1D(EventCategory+"_"+LHCStatus+"_maxPulseHeight_"+ChStr[c]+"_"+RangeCode,"Height of max (area) pulse in channel"+ChStr[c]+partnerThresholdStr,nBins,minX,maxX);;
    }
    nhists += 32*3;

    if (RangeCode == "A") { nBins = 400; minX = 0.; maxX = 200.; }
    if (RangeCode == "B") { nBins = 200; minX = 0.; maxX = 40.; }
    if (RangeCode == "C") { nBins = 250; minX = 0.; maxX = 5.; }
    if (RangeCode == "D") { nBins = 100; minX = 0.; maxX = 0.5; }
    for (int c=0; c<32; c++) {
        h_pulseArea[c] = new TH1D(EventCategory+"_"+LHCStatus+"_pulseArea_"+ChStr[c]+"_"+RangeCode,"Area of each pulse in channel"+ChStr[c],nBins,minX,maxX);
        h_firstPulseArea[c] = new TH1D(EventCategory+"_"+LHCStatus+"_firstPulseArea_"+ChStr[c]+"_"+RangeCode,"Area of first pulse in channel"+ChStr[c],nBins,minX,maxX);
        h_maxPulseArea[c] = new TH1D(EventCategory+"_"+LHCStatus+"_maxPulseArea_"+ChStr[c]+"_"+RangeCode,"Area of max (area) pulse in channel"+ChStr[c],nBins,minX,maxX);
    }
    nhists += 32*3;

    if (RangeCode == "A") { nBins = 128; minX = 0.; maxX = 640.; }
    if (RangeCode == "B") { nBins = 64; minX = 0.; maxX = 160.; }
    if (RangeCode == "C") { nBins = 32; minX = 0.; maxX = 40.; }
    if (RangeCode == "D") { nBins = 32; minX = 0.; maxX = 20.; }
    for (int c=0; c<32; c++) {
        h_pulseDuration[c] = new TH1D(EventCategory+"_"+LHCStatus+"_pulseDuration_"+ChStr[c]+"_"+RangeCode,"Duration of each pulse in channel"+ChStr[c],nBins,minX,maxX);
        h_firstPulseDuration[c] = new TH1D(EventCategory+"_"+LHCStatus+"_firstPulseDuration_"+ChStr[c]+"_"+RangeCode,"Duration of first pulse in channel"+ChStr[c],nBins,minX,maxX);
        h_maxPulseDuration[c] = new TH1D(EventCategory+"_"+LHCStatus+"_maxPulseDuration_"+ChStr[c]+"_"+RangeCode,"Duration of max (area) pulse in channel"+ChStr[c],nBins,minX,maxX);
    }
    nhists += 32*3;

    if (RangeCode == "A") { nBins = 400; minX = 0.; maxX = 1000.; }
    if (RangeCode == "B") { nBins = 200; minX = 0.; maxX = 100.; }
    if (RangeCode == "C") { nBins = 250; minX = 0.; maxX = 10.; }
    if (RangeCode == "D") { nBins = 60; minX = 0.; maxX = 3.; }
    for (int c=0; c<32; c++) {
        h_pulseNPE[c] = new TH1D(EventCategory+"_"+LHCStatus+"_pulseNPE_"+ChStr[c]+"_"+RangeCode,"NPE of each pulse in channel"+ChStr[c],nBins,minX,maxX);
        h_firstPulseNPE[c] = new TH1D(EventCategory+"_"+LHCStatus+"_firstPulseNPE_"+ChStr[c]+"_"+RangeCode,"NPE of first pulse in channel"+ChStr[c],nBins,minX,maxX);
        h_maxPulseNPE[c] = new TH1D(EventCategory+"_"+LHCStatus+"_maxPulseNPE_"+ChStr[c]+"_"+RangeCode,"NPE of max (area) pulse in channel"+ChStr[c],nBins,minX,maxX);
    }
    nhists += 32*3;

    if (RangeCode == "A") { nBins = 512; minX = 0.; maxX = 1024*0.625; }
    if (RangeCode == "B") { nBins = 50; minX = 0.; maxX = 200.; }
    if (RangeCode == "C") { nBins = 50; minX = 150.; maxX = 300.; }
    if (RangeCode == "D") { nBins = 50; minX = 300.; maxX = 450.; }
    for (int c=0; c<32; c++) {
        h_pulseTime[c] = new TH1D(EventCategory+"_"+LHCStatus+"_pulseTime_"+ChStr[c]+"_"+RangeCode,"Time of each pulse in channel "+ChStr[c],nBins,minX,maxX);
        h_firstPulseTime[c] = new TH1D(EventCategory+"_"+LHCStatus+"_firstPulseTime_"+ChStr[c]+"_"+RangeCode,"Time of first pulse in channel "+ChStr[c],nBins,minX,maxX);
        h_maxPulseTime[c] = new TH1D(EventCategory+"_"+LHCStatus+"_maxPulseTime_"+ChStr[c]+"_"+RangeCode,"Time of max (area) pulse in channel "+ChStr[c],nBins,minX,maxX);
    }
    nhists += 32*3;

    if (RangeCode == "A") { nBins = 21; minX = -0.5; maxX = 20.5; }
    if (RangeCode == "B") { nBins = 11; minX = -0.5; maxX = 10.5; }
    if (RangeCode == "C") { nBins = 6; minX = -0.5; maxX = 5.5; }
    if (RangeCode == "D") { nBins = 4; minX = -0.5; maxX = 3.5; }
    for (int c=0; c<32; c++) {
        h_npulsesPerChannel[c] = new TH1D(EventCategory+"_"+LHCStatus+"_npulsesPerChannel_"+ChStr[c]+"_"+RangeCode,"Number of pulses in channel "+ChStr[c],nBins,minX,maxX);
        h_nhitsPerChannel[c] = new TH1D(EventCategory+"_"+LHCStatus+"_nhitsPerChannel_"+ChStr[c]+"_"+RangeCode,"Number of hits in channel "+ChStr[c],nBins,minX,maxX);
        h_npulses[c] = new TH1D(EventCategory+"_"+LHCStatus+"_npulses_"+ChStr[c]+"_"+RangeCode,"Number of pulses in detector when tagged channel"+ChStr[c],nBins,minX,maxX);
        h_nhits[c] = new TH1D(EventCategory+"_"+LHCStatus+"_nhits_"+ChStr[c]+"_"+RangeCode,"Number of hits in detector when tagged channel "+ChStr[c],nBins,minX,maxX);
        h_nchannelsWithAtLeastOnePulse[c] = new TH1D(EventCategory+"_"+LHCStatus+"_nchannelsWithAtLeastOnePulse_"+ChStr[c]+"_"+RangeCode,"Number of channels with at least one pulse when tagged channel"+ChStr[c],nBins,minX,maxX);
        h_nchannelsWithAtLeastOneHit[c] = new TH1D(EventCategory+"_"+LHCStatus+"_nchannelsWithAtLeastOneHit_"+ChStr[c]+"_"+RangeCode,"Number of channels with at least one hitwhen tagged channel"+ChStr[c],nBins,minX,maxX);
    }
    nhists += 32*6;

    if (RangeCode == "A") { nBins = 200; minX = -200.; maxX = 200.; }
    if (RangeCode == "B") { nBins = 50; minX = -200.; maxX = 200.; }
    if (RangeCode == "C") { nBins = 50; minX = -50.; maxX = 50.; }
    if (RangeCode == "D") { nBins = 30; minX = -30.; maxX = 30.; }
    for (int c=0; c<32; c++) {
        h_diffTimeWithNeighboringMaxHit[c] = new TH1D(EventCategory+"_"+LHCStatus+"_diffTimeWithNeighborMaxHit_"+ChStr[c]+"_"+RangeCode,"Time difference between hits in this and neighboring channels"+ChStr[c],nBins,minX,maxX);
        h_diffTimeWithNeighboringMaxHitCalibrated[c] = new TH1D(EventCategory+"_"+LHCStatus+"_diffTimeWithNeighborMaxHitCalibrated_"+ChStr[c]+"_"+RangeCode,"Calibrated time difference between hits in this and neighboring channels"+ChStr[c],nBins,minX,maxX);
    }
    nhists += 32*2;

    if (RangeCode == "A") { nBins = 21; minX = -0.5; maxX = 20.5; }
    if (RangeCode == "B") { nBins = 11; minX = -0.5; maxX = 10.5; }
    if (RangeCode == "C") { nBins = 6; minX = -0.5; maxX = 5.5; }
    if (RangeCode == "D") { nBins = 4; minX = -0.5; maxX = 3.5; }
    h_ncosmics = new TH1D(EventCategory+"_"+LHCStatus+"_ncosmics_"+RangeCode,"Number of cosmic muon tags",nBins,minX,maxX);
    ++nhists;

    /*******************************************************************************************************************************************************
    ****                                                                                                                                                ****
    ****                                              END HISTOS FOR COSMICS STUDY                                                                      ****
    ****                                                                                                                                                ****
    *******************************************************************************************************************************************************/

    return nhists;
}

// The channel mapping changed over time, e.g., in TS1, so the code below is run dependent.
void NeighborHitMap(bool *NeighborHit, bool HitChan[], int RunNum, TString EventCategory)
{
    if (RunNum <= 863) { // Pre TS1
        // Cosmic tags; loose selection for Cosmics and tighter selection later for CosmicTag
        if (EventCategory == "CosmicTag") { // Tighter selection for CosmicTag category
            // Here we use tight requirements of 3 hits around the channel (except slabs, which require 2) to obtain a pure sample.
            if ((HitChan[24] && HitChan[8] && HitChan[10]) ||
                    (run>817 && HitChan[24] && HitChan[10])) // CH8 dies after run 817
                NeighborHit[0] = true;
            if (HitChan[25] && HitChan[9] && HitChan[10])
                NeighborHit[1] = true;
            if (HitChan[22] && HitChan[4] && HitChan[14])
                NeighborHit[2] = true ;
            if (HitChan[23] && HitChan[5] && HitChan[14])
                NeighborHit[3] = true;
            if (HitChan[2] && HitChan[22] && HitChan[14])
                NeighborHit[4] = true;
            if (HitChan[3] && HitChan[23] && HitChan[14])
                NeighborHit[5] = true;
            if (HitChan[16] && HitChan[12] && ((HitChan[30]&&RunNum<900)||(HitChan[11]&&RunNum>900)))
                NeighborHit[6] = true;
            if (HitChan[17] && HitChan[13] && ((HitChan[30]&&RunNum<900)||(HitChan[11]&&RunNum>900)))
                NeighborHit[7] = true;
            if (HitChan[0] && HitChan[24] && HitChan[10])
                NeighborHit[8] = true;
            if (HitChan[1] && HitChan[25] && HitChan[10])
                NeighborHit[9] = true;
            if (HitChan[6] && HitChan[16] && ((HitChan[30]&&RunNum<900)||(HitChan[11]&&RunNum>900)))
                NeighborHit[12] = true;
            if (HitChan[7] && HitChan[17] && ((HitChan[30]&&RunNum<900)||(HitChan[11]&&RunNum>900)))
                NeighborHit[13] = true;
            if (HitChan[6] && HitChan[12] && ((HitChan[30]&&RunNum<900)||(HitChan[11]&&RunNum>900)))
                NeighborHit[16] = true;
            if (HitChan[7] && HitChan[13] && ((HitChan[30]&&RunNum<900)||(HitChan[11]&&RunNum>900)))
                NeighborHit[17] = true;
            if (HitChan[2] && HitChan[4] && HitChan[14])
                NeighborHit[22] = true;
            if (HitChan[3] && HitChan[5] && HitChan[14])
                NeighborHit[22] = true;
            if (HitChan[3] && HitChan[5] && HitChan[14])
                NeighborHit[23] = true;
            if ((HitChan[0] && HitChan[8] && HitChan[10]) ||
                    (run>817 && HitChan[0] && HitChan[10])) // CH8 dies after run 817
                NeighborHit[24] = true;
            if (HitChan[1] && HitChan[9] && HitChan[10])
                NeighborHit[25] = true;
    
            // Top veto panels
            if ((HitChan[0]&&HitChan[24]&&HitChan[8]) || (HitChan[1]&&HitChan[25]&&HitChan[9]))
                NeighborHit[10] = true; // Panel L0 top
            if ((HitChan[6]&&HitChan[16]&&HitChan[12]) || (HitChan[7]&&HitChan[17]&&HitChan[13]))
                NeighborHit[30] = true; // Panel L1 top
            if ((HitChan[2]&&HitChan[22]&&HitChan[4]) || (HitChan[3]&&HitChan[23]&&HitChan[5]))
                NeighborHit[14] = true; // Panel L2 top
    
            // Side veto panels
            if (HitChan[29] &&
                    (HitChan[0]||HitChan[24]||HitChan[8]) &&
                    (HitChan[1]||HitChan[25]||HitChan[9]))
                NeighborHit[27] = true; // Panel L0 left
            if (HitChan[27] &&
                    (HitChan[0]||HitChan[24]||HitChan[8]) &&
                    (HitChan[1]||HitChan[25]||HitChan[9]))
                NeighborHit[29] = true; // Panel L0 right
            if (HitChan[19] &&
                    (HitChan[6]||HitChan[16]||HitChan[12]) &&
                    (HitChan[7]||HitChan[17]||HitChan[13]))
                NeighborHit[11] = true; // Panel L1 left
            if (((HitChan[30]&&RunNum>900)||(HitChan[11]&&RunNum<900)) &&
                    (HitChan[6]||HitChan[16]||HitChan[12]) &&
                    (HitChan[7]||HitChan[17]||HitChan[13]))
                NeighborHit[19] = true; // Panel L1 right
            if ((HitChan[31] &&
                        (HitChan[2]||HitChan[22]||HitChan[4]) &&
                        (HitChan[3]||HitChan[23]||HitChan[5])) ||
                    (run>833 && (HitChan[2]||HitChan[22]||HitChan[4]) &&
                     (HitChan[3]||HitChan[23]||HitChan[5])))
                NeighborHit[26] = true; // Panel L2 right
            if (HitChan[26] &&
                    (HitChan[2]||HitChan[22]||HitChan[4]) &&
                    (HitChan[3]||HitChan[23]||HitChan[5]))
                NeighborHit[31] = true; // Pannel L2 left
    
            // Slabs
            if ( (HitChan[24] && HitChan[8]) || (HitChan[25] && HitChan[9]) ||
                    (HitChan[0] && HitChan[24]) || (HitChan[1] && HitChan[25]) ) {
                NeighborHit[18] = true; // Slab1
                NeighborHit[20] = true; // Slab0
            }
            if ( (HitChan[16] && HitChan[12]) || (HitChan[17] && HitChan[13]) ||
                    (HitChan[6] && HitChan[16]) || (HitChan[7] && HitChan[17]) ) {
                NeighborHit[20] = true; // Slab0
                NeighborHit[28] = true; // Slab2
            }
            if ( (HitChan[22] && HitChan[4]) || (HitChan[23] && HitChan[5]) ||
                    (HitChan[2] && HitChan[22]) || (HitChan[3] && HitChan[23]) ) {
                NeighborHit[28] = true; // Slab2
                NeighborHit[21] = true; // Slab3
            }
        } // Tighter selection for CosmicTag category
        else { // Looser selection for categories other than CosmicTag
            // Here we require ANY TWO hits in line with the probe channel
            // Used to obtain an efficient sample, and in particular one that tests trigger validity
            if ((HitChan[24] && HitChan[8]) || (HitChan[24] && HitChan[10]) || (HitChan[8] && HitChan[10]))
                NeighborHit[0] = true;
            if ((HitChan[25] && HitChan[9]) || (HitChan[25] && HitChan[10]) || (HitChan[9] && HitChan[10]))
                NeighborHit[1] = true;
            if ((HitChan[22] && HitChan[4]) || (HitChan[22] && HitChan[14]) || (HitChan[4] && HitChan[14]))
                NeighborHit[2] = true;
            if ((HitChan[23] && HitChan[5]) || (HitChan[23] && HitChan[14]) || (HitChan[5] && HitChan[14]))
                NeighborHit[3] = true;
            if ((HitChan[2] && HitChan[22]) || (HitChan[22] && HitChan[14]) || (HitChan[2] && HitChan[14]))
                NeighborHit[4] = true;
            if ((HitChan[3] && HitChan[23]) || (HitChan[23] && HitChan[14]) || (HitChan[3] && HitChan[14]))
                NeighborHit[5] = true;
            if ((HitChan[16] && HitChan[12]) ||
                    (HitChan[16] && ((HitChan[30]&&RunNum<900)||(HitChan[11]&&RunNum>900))) ||
                    (HitChan[12] && ((HitChan[30]&&RunNum<900)||(HitChan[11]&&RunNum>900))))
                NeighborHit[6] = true;
            if ((HitChan[17] && HitChan[13]) ||
                    (HitChan[17] && ((HitChan[30]&&RunNum<900)||(HitChan[11]&&RunNum>900))) ||
                    (HitChan[13] && ((HitChan[30]&&RunNum<900)||(HitChan[11]&&RunNum>900))))
                NeighborHit[7] = true;
            if ((HitChan[0] && HitChan[24]) || (HitChan[10] && HitChan[24]) || (HitChan[10] && HitChan[0]))
                NeighborHit[8] = true;
            if ((HitChan[1] && HitChan[25]) || (HitChan[10] && HitChan[25]) || (HitChan[10] && HitChan[1]))
                NeighborHit[9] = true;
            if ((HitChan[6] && HitChan[16]) ||
                    (((HitChan[30]&&RunNum<900)||(HitChan[11]&&RunNum>900)) && HitChan[16]) ||
                    (((HitChan[30]&&RunNum<900)||(HitChan[11]&&RunNum>900)) && HitChan[6]))
                NeighborHit[12] = true;
            if ((HitChan[7] && HitChan[17]) ||
                    (((HitChan[30]&&RunNum<900)||(HitChan[11]&&RunNum>900)) && HitChan[17]) ||
                    (((HitChan[30]&&RunNum<900)||(HitChan[11]&&RunNum>900)) && HitChan[7]))
                NeighborHit[13] = true;
            if ((HitChan[6] && HitChan[12]) ||
                    (((HitChan[30]&&RunNum<900)||(HitChan[11]&&RunNum>900)) && HitChan[12]) ||
                    (((HitChan[30]&&RunNum<900)||(HitChan[11]&&RunNum>900)) && HitChan[6]))
                NeighborHit[16] = true;
            if ((HitChan[7] && HitChan[13]) ||
                    (((HitChan[30]&&RunNum<900)||(HitChan[11]&&RunNum>900)) && HitChan[13]) ||
                    (((HitChan[30]&&RunNum<900)||(HitChan[11]&&RunNum>900)) && HitChan[7]))
                NeighborHit[17] = true;
            if ((HitChan[2] && HitChan[4]) || (HitChan[14] && HitChan[4]) || (HitChan[14] && HitChan[2]))
                NeighborHit[22] = true;
            if ((HitChan[3] && HitChan[5]) || (HitChan[14] && HitChan[5]) || (HitChan[14] && HitChan[3]))
                NeighborHit[23] = true;
            if ((HitChan[0] && HitChan[8]) || (HitChan[10] && HitChan[8]) || (HitChan[10] && HitChan[0]))
                NeighborHit[24] = true;
            if ((HitChan[1] && HitChan[9]) || (HitChan[10] && HitChan[9]) || (HitChan[10] && HitChan[1]))
                NeighborHit[25] = true;
    
            // Veto panels
            if ((HitChan[0]&&HitChan[24]) || (HitChan[0]&&HitChan[8])  ||
                    (HitChan[24]&&HitChan[8]) || (HitChan[1]&&HitChan[25]) ||
                    (HitChan[1]&&HitChan[9]) || (HitChan[25]&&HitChan[9]))
                NeighborHit[10] = true; // Panel L0 top
            if ((HitChan[6]&&HitChan[16]) || (HitChan[6]&&HitChan[12])  ||
                    (HitChan[16]&&HitChan[12]) || (HitChan[7]&&HitChan[17]) ||
                    (HitChan[7]&&HitChan[13]) || (HitChan[17]&&HitChan[13])) {
                if (RunNum<900)
                    NeighborHit[30] = true; // Panel L1 top
                else
                    NeighborHit[11] = true; // Panel L1 top
            }
            if ((HitChan[2]&&HitChan[22]) || (HitChan[2]&&HitChan[4])  ||
                    (HitChan[22]&&HitChan[4]) || (HitChan[3]&&HitChan[23]) ||
                    (HitChan[3]&&HitChan[5]) || (HitChan[23]&&HitChan[5]))
                NeighborHit[14] = true; // Panel L2 top
    
            // Side veto panels
            if ((HitChan[0]||HitChan[24]||HitChan[8]) && (HitChan[1]||HitChan[25]||HitChan[9])) {
                NeighborHit[27] = true; // Panel L0 left
                NeighborHit[29] = true; // Panel L0 right
            }
            if ((HitChan[6]||HitChan[16]||HitChan[12]) && (HitChan[7]||HitChan[17]||HitChan[13])) {
                NeighborHit[19] = true; // Panel L1 right
                if (RunNum<900)
                    NeighborHit[11] = true; // Panel L1 left
                else
                    NeighborHit[30] = true; // Panel L1 left
            }
            if ((HitChan[2]||HitChan[22]||HitChan[4]) && (HitChan[3]||HitChan[23]||HitChan[5])) {
                NeighborHit[31] = true; // Panel L2 left
                NeighborHit[26] = true; // Panel L2 right
            }
    
            // Slabs
            if ( (HitChan[24] && HitChan[8]) || (HitChan[25] && HitChan[9]) ||
                    (HitChan[0] && HitChan[24]) || (HitChan[1] && HitChan[25]) ) {
                NeighborHit[18] = true; // Slab 0
                NeighborHit[20] = true; // Slab 1
            }
            if ( (HitChan[16] && HitChan[12]) || (HitChan[17] && HitChan[13]) ||
                    (HitChan[6] && HitChan[16]) || (HitChan[7] && HitChan[17]) ) {
                NeighborHit[20] = true; // Slab 1
                NeighborHit[28] = true; // Slab 2
            }
            if ( (HitChan[22] && HitChan[4]) || (HitChan[23] && HitChan[5]) ||
                    (HitChan[2] && HitChan[22]) || (HitChan[3] && HitChan[23]) ) {
                NeighborHit[28] = true; // Slab 2
                NeighborHit[21] = true; // Slab 3
            }
        } // Looser selection for categories other than CosmicTag
    } // Run <= 863 (pre TS1)
    
    else if (RunNum>=864 && RunNum<911) { // Special selection for TS1 runs
        // Here we require ANY two hits in the L1 channels placed below L2
        if ((HitChan[10] && HitChan[27]) ||
                ((HitChan[10]||HitChan[27]) && (HitChan[0]||HitChan[1]||HitChan[24]||HitChan[25]))) {
            NeighborHit[0] = true;
            NeighborHit[1] = true;
            NeighborHit[2] = true;
            NeighborHit[3] = true;
            NeighborHit[4] = true;
            NeighborHit[5] = true;
            NeighborHit[6] = true;
            NeighborHit[7] = true;
            NeighborHit[8] = true;
            NeighborHit[9] = true;
            NeighborHit[10] = true;
            NeighborHit[11] = true;
            NeighborHit[12] = true;
            NeighborHit[13] = true;
            NeighborHit[14] = true;
            NeighborHit[13] = true;
            NeighborHit[14] = true;
            NeighborHit[16] = true;
            NeighborHit[17] = true;
            NeighborHit[18] = true;
            NeighborHit[19] = true;
            NeighborHit[20] = true;
            NeighborHit[21] = true;
            NeighborHit[22] = true;
            NeighborHit[23] = true;
            NeighborHit[24] = true;
            NeighborHit[25] = true;
            NeighborHit[26] = true;
            NeighborHit[27] = true;
            NeighborHit[28] = true;
            NeighborHit[29] = true;
            NeighborHit[30] = true;
            NeighborHit[31] = true;
        }
    } // Special selection for TS1 runs
    
    else { // Post TS1 runs?
        // Cosmic tags; loose selection for Cosmics and tighter selection later for CosmicTag
        if (EventCategory == "CosmicTag") { // Tighter selection for CosmicTag category
            // Here we use tight requirements of 3 hits around the channel (except slabs, which require 2) to obtain a pure sample.
            if (HitChan[24] && HitChan[8] && HitChan[10])
                NeighborHit[0] = true;
            if (HitChan[25] && HitChan[9] && HitChan[10])
                NeighborHit[1] = true;
            if (HitChan[22] && HitChan[4] && HitChan[14])
                NeighborHit[2] = true ;
            if (HitChan[23] && HitChan[5] && HitChan[14])
                NeighborHit[3] = true;
            if (HitChan[2] && HitChan[22] && HitChan[14])
                NeighborHit[4] = true;
            if (HitChan[3] && HitChan[23] && HitChan[14])
                NeighborHit[5] = true;
            if (HitChan[16] && HitChan[12] && HitChan[30])
                NeighborHit[6] = true;
            if (HitChan[17] && HitChan[13] && HitChan[30])
                NeighborHit[7] = true;
            if (HitChan[0] && HitChan[24] && HitChan[10])
                NeighborHit[8] = true;
            if (HitChan[1] && HitChan[25] && HitChan[10])
                NeighborHit[9] = true;
            if (HitChan[6] && HitChan[16] && HitChan[30])
                NeighborHit[12] = true;
            if (HitChan[7] && HitChan[17] && HitChan[30])
                NeighborHit[13] = true;
            if (HitChan[6] && HitChan[12] && HitChan[30])
                NeighborHit[16] = true;
            if (HitChan[7] && HitChan[13] && HitChan[30])
                NeighborHit[17] = true;
            if (HitChan[2] && HitChan[4] && HitChan[14])
                NeighborHit[22] = true;
            if (HitChan[3] && HitChan[5] && HitChan[14])
                NeighborHit[23] = true;
            if (HitChan[0] && HitChan[8] && HitChan[10])
                NeighborHit[24] = true;
            if (HitChan[1] && HitChan[9] && HitChan[10])
                NeighborHit[25] = true;
    
            // Top veto panels
            if ((HitChan[0]&&HitChan[24]&&HitChan[8]) || (HitChan[1]&&HitChan[25]&&HitChan[9]))
            // Top veto panels
            if ((HitChan[0]&&HitChan[24]&&HitChan[8]) || (HitChan[1]&&HitChan[25]&&HitChan[9]))
                NeighborHit[10] = true; // Panel L0 top
            if ((HitChan[6]&&HitChan[16]&&HitChan[12]) || (HitChan[7]&&HitChan[17]&&HitChan[13]))
                NeighborHit[30] = true; // Panel L1 top
            if ((HitChan[2]&&HitChan[22]&&HitChan[4]) || (HitChan[3]&&HitChan[23]&&HitChan[5]))
                NeighborHit[14] = true; // Panel L2 top
    
            // Side veto panels
            if (HitChan[29] &&
                    (HitChan[0]||HitChan[24]||HitChan[8]) &&
                    (HitChan[1]||HitChan[25]||HitChan[9]))
                NeighborHit[27] = true; // Panel L0 left
            if (HitChan[27] &&
                    (HitChan[0]||HitChan[24]||HitChan[8]) &&
                    (HitChan[1]||HitChan[25]||HitChan[9]))
                NeighborHit[29] = true; // Panel L0 right
            if (HitChan[19] &&
                    (HitChan[6]||HitChan[16]||HitChan[12]) &&
                    (HitChan[7]||HitChan[17]||HitChan[13]))
                NeighborHit[11] = true; // Panel L1 left
            if (HitChan[30] &&
                    (HitChan[6]||HitChan[16]||HitChan[12]) &&
                    (HitChan[7]||HitChan[17]||HitChan[13]))
                NeighborHit[19] = true; // Panel L1 right
            if ((HitChan[31] &&
                        (HitChan[2]||HitChan[22]||HitChan[4]) &&
                        (HitChan[3]||HitChan[23]||HitChan[5])) ||
                    (run>833 && (HitChan[2]||HitChan[22]||HitChan[4]) &&
                     (HitChan[3]||HitChan[23]||HitChan[5])))
                NeighborHit[26] = true; // Panel L2 right
            if (HitChan[26] &&
                    (HitChan[2]||HitChan[22]||HitChan[4]) &&
                    (HitChan[3]||HitChan[23]||HitChan[5]))
                NeighborHit[31] = true; // Pannel L2 left
    
            // Slabs
            if ( (HitChan[24] && HitChan[8] && !HitChan[0] && !HitChan[1] && !HitChan[10]) ||
                    (HitChan[25] && HitChan[9] && !HitChan[0] && !HitChan[1] && !HitChan[10]) ||
                    (HitChan[10] && HitChan[0] && HitChan[24] && !HitChan[8]) ||
                    (HitChan[10] && HitChan[1] && HitChan[25] && !HitChan[9]) ) {
                NeighborHit[18] = true; // Slab1
                NeighborHit[20] = true; // Slab0
            }
            if     ( (HitChan[6] && HitChan[16] && HitChan[30] && !HitChan[12] ) ||
                   (HitChan[7] && HitChan[17] && HitChan[30] && !HitChan[13]) ) {
                NeighborHit[20] = true; // Slab0
                NeighborHit[28] = true; // Slab2
            }
            if ( (HitChan[22] && HitChan[4] && !HitChan[2] && !HitChan[14]) ||
                    (HitChan[23] && HitChan[5] && !HitChan[3] && !HitChan[14]) ||
                    (HitChan[2] && HitChan[22] && HitChan[14]) ||
                    (HitChan[3] && HitChan[23] && HitChan[14]) ) {
                NeighborHit[28] = true; // Slab2
                NeighborHit[21] = true; // Slab3
            }
        } // Tighter selection for CosmicTag category
    
        else { // Looser selection for categories other than CosmicTag
            // Here we require ANY TWO hits in line with the probe channel
            // Used to obtain an efficient sample, and in particular one that tests trigger validity
            if ((HitChan[24] && HitChan[8]) || (HitChan[24] && HitChan[10]) || (HitChan[8] && HitChan[10]))
                NeighborHit[0] = true;
            if ((HitChan[25] && HitChan[9]) || (HitChan[25] && HitChan[10]) || (HitChan[9] && HitChan[10]))
                NeighborHit[1] = true;
            if ((HitChan[22] && HitChan[4]) || (HitChan[22] && HitChan[14]) || (HitChan[4] && HitChan[14]))
                NeighborHit[2] = true;
            if ((HitChan[23] && HitChan[5]) || (HitChan[23] && HitChan[14]) || (HitChan[5] && HitChan[14]))
                NeighborHit[3] = true;
            if ((HitChan[2] && HitChan[22]) || (HitChan[22] && HitChan[14]) || (HitChan[2] && HitChan[14]))
                NeighborHit[4] = true;
            if ((HitChan[3] && HitChan[23]) || (HitChan[23] && HitChan[14]) || (HitChan[3] && HitChan[14]))
                NeighborHit[5] = true;
            if ((HitChan[16] && HitChan[12]) ||
                    (HitChan[16] && HitChan[30]) ||
                    (HitChan[12] && HitChan[30]))
                NeighborHit[6] = true;
            if ((HitChan[17] && HitChan[13]) ||
                    (HitChan[17] && HitChan[30]) ||
                    (HitChan[13] && HitChan[30]))
                NeighborHit[7] = true;
            if ((HitChan[0] && HitChan[24]) ||
                    (HitChan[10] && HitChan[24]) ||
                    (HitChan[10] && HitChan[0]))
                NeighborHit[8] = true;
            if ((HitChan[1] && HitChan[25]) ||
                    (HitChan[10] && HitChan[25]) ||
                    (HitChan[10] && HitChan[1]))
                NeighborHit[9] = true;
            if ((HitChan[6] && HitChan[16]) ||
                    (HitChan[30] && HitChan[16]) ||
                    (HitChan[30] && HitChan[6]))
                NeighborHit[12] = true;
            if ((HitChan[7] && HitChan[17]) ||
                    (HitChan[30] && HitChan[17]) ||
                    (HitChan[30] && HitChan[7]))
                NeighborHit[13] = true;
            if ((HitChan[6] && HitChan[12]) ||
                    (HitChan[30] && HitChan[12]) ||
                    (HitChan[30] && HitChan[6]))
                NeighborHit[16] = true;
            if ((HitChan[7] && HitChan[13]) ||
                    (HitChan[30] && HitChan[13]) ||
                    (HitChan[30] && HitChan[7]))
                NeighborHit[17] = true;
            if ((HitChan[2] && HitChan[4]) || (HitChan[14] && HitChan[4]) || (HitChan[14] && HitChan[2]))
                NeighborHit[22] = true;
            if ((HitChan[3] && HitChan[5]) || (HitChan[14] && HitChan[5]) || (HitChan[14] && HitChan[3]))
                NeighborHit[23] = true;
            if ((HitChan[0] && HitChan[8]) || (HitChan[10] && HitChan[8]) || (HitChan[10] && HitChan[0]))
                NeighborHit[24] = true;
            if ((HitChan[1] && HitChan[9]) || (HitChan[10] && HitChan[9]) || (HitChan[10] && HitChan[1]))
                NeighborHit[25] = true;
    
            // Veto panels
            if ((HitChan[0]&&HitChan[24]) || (HitChan[0]&&HitChan[8])  ||
                    (HitChan[24]&&HitChan[8]) || (HitChan[1]&&HitChan[25]) ||
                    (HitChan[1]&&HitChan[9]) || (HitChan[25]&&HitChan[9]))
                NeighborHit[10] = true; // Panel L0 top
            if ((HitChan[6]&&HitChan[16]) || (HitChan[6]&&HitChan[12])  ||
                    (HitChan[16]&&HitChan[12]) || (HitChan[7]&&HitChan[17]) ||
                    (HitChan[7]&&HitChan[13]) || (HitChan[17]&&HitChan[13])) {
                NeighborHit[30] = true; // Panel L1 top
            }
                NeighborHit[30] = true; // Panel L1 top
            }
            if ((HitChan[2]&&HitChan[22]) || (HitChan[2]&&HitChan[4])  ||
                    (HitChan[22]&&HitChan[4]) || (HitChan[3]&&HitChan[23]) ||
                    (HitChan[3]&&HitChan[5]) || (HitChan[23]&&HitChan[5]))
                NeighborHit[14] = true; // Panel L2 top
    
            // Side veto panels
            if ((HitChan[0]||HitChan[24]||HitChan[8]) && (HitChan[1]||HitChan[25]||HitChan[9])) {
                NeighborHit[27] = true; // Panel L0 left
                NeighborHit[29] = true; // Panel L0 right
            }
            if ((HitChan[6]||HitChan[16]||HitChan[12]) && (HitChan[7]||HitChan[17]||HitChan[13])) {
                NeighborHit[19] = true; // Panel L1 right
                NeighborHit[11] = true; // Panel L1 left
            }
            if ((HitChan[2]||HitChan[22]||HitChan[4]) && (HitChan[3]||HitChan[23]||HitChan[5])) {
                NeighborHit[31] = true; // Panel L2 left
                NeighborHit[26] = true; // Panel L2 right
            }
    
            // Slabs
            if ( (HitChan[24] && HitChan[8]) || (HitChan[25] && HitChan[9]) ||
                    (HitChan[0] && HitChan[24]) || (HitChan[1] && HitChan[25]) ) {
                NeighborHit[18] = true; // Slab 0
                NeighborHit[20] = true; // Slab 1
            }
            if ( (HitChan[16] && HitChan[12]) || (HitChan[17] && HitChan[13]) ||
                    (HitChan[6] && HitChan[16]) || (HitChan[7] && HitChan[17]) ) {
                NeighborHit[20] = true; // Slab 1
                NeighborHit[28] = true; // Slab 2
            }
            if ( (HitChan[22] && HitChan[4]) || (HitChan[23] && HitChan[5]) ||
                    (HitChan[2] && HitChan[22]) || (HitChan[3] && HitChan[23]) ) {
                NeighborHit[28] = true; // Slab 2
                NeighborHit[21] = true; // Slab 3
            }
    } // Looser selec
}

int GetEventCategoryCode(TString EventCategoryName)
{
    if (EventCategoryName == "All") return 0;
    if (EventCategoryName == "SPE") return 1;
    if ((EventCategoryName == "Small") || (EventCategoryName == "SmallTag")) return 2;
    if ((EventCategoryName == "Cosmic") || (EventCategoryName == "CosmicTag")) return 3;
    if ((EventCategoryName == "Thru") || (EventCategoryName == "ThruTag")) return 4;
    return 0;
}

