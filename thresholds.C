#ifndef thresholds_h
#define thresholds_h

#include "thresholds.h"

void set_thresholds(float *vthresh, float *dthresh, float *athresh, int RunNum)
{
    // Set the default thresholds
    static const unsigned int NCOLS = 5;
    for (int c=0; c<32; c++) {
        *(vthresh+c*5+0) = 0.; // All, i.e., no cuts beyond pulse finding
        *(vthresh+c*NCOLS+1) = 10.; // SPE, upper cut [mV]
        *(vthresh+c*NCOLS+2) = 20.; // Small signals, lower cut [mV]
        *(vthresh+c*NCOLS+3) = 300.; // Cosmics, lower cut [mV]
        *(vthresh+c*NCOLS+4) = 10.; // Any pulse
        *(dthresh+c*NCOLS+0) = 0.; // All, i.e., no cuts beyond pulse finding
        *(dthresh+c*NCOLS+1) = 15.; // SPE, upper cut [ns)
        *(dthresh+c*NCOLS+2) = 5.; // Small signals, lower cut [ns)
        *(dthresh+c*NCOLS+3) = 10.; // Cosmics, lower cut [ns)
        *(dthresh+c*NCOLS+4) = 10.; // Through going particles, lower cut [ns)
        *(athresh+c*NCOLS+0) = 0.; // All, i.e., no cuts beyond pulse finding
        *(athresh+c*NCOLS+1) = 0.02; // SPE, upper cut [nVs)
        *(athresh+c*NCOLS+2) = 0.1; // Small signals, lower cut [nVs)
        *(athresh+c*NCOLS+3) = 1.; // Cosmics, lower cut [nVs)
        *(athresh+c*NCOLS+4) = 0.01; // Through going particles, lower cut [nVs)
    }

    // Special settings
    if (RunNum<31) {
        for (int c=0; c<32; c++) {
            *(vthresh+c*NCOLS+3) = 60.; // Cosmics, lower cut [mV]
            *(vthresh+c*NCOLS+4) = 1000.; // Through going particles, lower cut [mV]
            *(athresh+c*NCOLS+3) = 5.; // Cosmics, lower cut [nVs]
            *(athresh+c*NCOLS+4) = 20.; // Through going particles, lower cut [nVs]
        }
        *(vthresh+8*NCOLS+3) = 10.; // Cosmics, lower cut [mV]
        *(vthresh+8*NCOLS+4) = 100.; // Through going particles, lower cut [mV]
        *(athresh+8*NCOLS+3) = 0.4; // Cosmics, lower cut [nVs]
        *(athresh+8*NCOLS+4) = 2.; // Through going particles, lower cut [nVs]
        *(vthresh+9*NCOLS+3) = 10.; // Cosmics, lower cut [mV]
        *(vthresh+9*NCOLS+4) = 100.; // Through going particles, lower cut [mV]
        *(athresh+9*NCOLS+3) = 1.; // Cosmics, lower cut [nVs]
        *(athresh+9*NCOLS+4) = 2.; // Through going particles, lower cut [nVs]
        *(vthresh+10*NCOLS+3) = 10.; // Cosmics, lower cut [mV]
        *(vthresh+10*NCOLS+4) = 100.; // Through going particles, lower cut [mV]
        *(athresh+10*NCOLS+3) = 0.4; // Cosmics, lower cut [nVs]
        *(athresh+10*NCOLS+4) = 2.; // Through going particles, lower cut [nVs]
    }

    // Hardcode run dependent cosmic thresholds. These should eventually be read from a file.
    if (RunNum == 24) {
        *(athresh+1*NCOLS+3) = 5.;
        *(athresh+2*NCOLS+3) = 1.5;
        *(athresh+3*NCOLS+3) = 1.;
        *(athresh+4*NCOLS+3) = 2.;
        *(athresh+5*NCOLS+3) = 2.5;
        *(athresh+6*NCOLS+3) = 2.;
        *(athresh+7*NCOLS+3) = 2.;
        *(athresh+8*NCOLS+3) = 0.02;
        *(athresh+9*NCOLS+3) = 0.1;
        *(athresh+10*NCOLS+3) = 0.02;
        *(athresh+11*NCOLS+3) = 1.0;
        *(athresh+12*NCOLS+3) = 3.;
        *(athresh+14*NCOLS+3) = 2.;
        *(athresh+15*NCOLS+3) = 2.;
        *(vthresh+1*NCOLS+3) = 100.;
        *(vthresh+2*NCOLS+3) = 40.;
        *(vthresh+3*NCOLS+3) = 25.;
        *(vthresh+4*NCOLS+3) = 35.;
        *(vthresh+5*NCOLS+3) = 45.;
        *(vthresh+6*NCOLS+3) = 20.;
        *(vthresh+7*NCOLS+3) = 50.;
        *(vthresh+8*NCOLS+3) = 5.;
        *(vthresh+9*NCOLS+3) = 6.;
        *(vthresh+10*NCOLS+3) = 6.;
        *(vthresh+11*NCOLS+3) = 25.;
        *(vthresh+12*NCOLS+3) = 35.;
        *(vthresh+14*NCOLS+3) = 35.;
        *(vthresh+15*NCOLS+3) = 35.;
        *(dthresh+1*NCOLS+3) = 70.;
        *(dthresh+2*NCOLS+3) = 30.;
        *(dthresh+3*NCOLS+3) = 40.;
        *(dthresh+4*NCOLS+3) = 70.;
        *(dthresh+5*NCOLS+3) = 80.;
        *(dthresh+6*NCOLS+3) = 60.;
        *(dthresh+7*NCOLS+3) = 50.;
        *(dthresh+8*NCOLS+3) = 10.;
        *(dthresh+9*NCOLS+3) = 10.;
        *(dthresh+10*NCOLS+3) = 10.;
        *(dthresh+11*NCOLS+3) = 30.;
        *(dthresh+12*NCOLS+3) = 70.;
        *(dthresh+14*NCOLS+3) = 60.;
        *(dthresh+15*NCOLS+3) = 60.;
    }
    if (RunNum == 25) {
        *(athresh+1*NCOLS+3) = 11.;
        *(athresh+2*NCOLS+3) = 2.;
        *(athresh+3*NCOLS+3) = 2.;
        *(athresh+4*NCOLS+3) = 5.;
        *(athresh+5*NCOLS+3) = 7.;
        *(athresh+6*NCOLS+3) = 4.;
        *(athresh+7*NCOLS+3) = 4.;
        *(athresh+8*NCOLS+3) = 0.02;
        *(athresh+9*NCOLS+3) = 0.5;
        *(athresh+10*NCOLS+3) = 0.05;
        *(athresh+11*NCOLS+3) = 3.;
        *(athresh+12*NCOLS+3) = 3.;
        *(athresh+14*NCOLS+3) = 4.;
        *(athresh+15*NCOLS+3) = 4.;
        *(vthresh+1*NCOLS+3) = 200.;
        *(vthresh+2*NCOLS+3) = 80.;
        *(vthresh+3*NCOLS+3) = 50.;
        *(vthresh+4*NCOLS+3) = 50.;
        *(vthresh+5*NCOLS+3) = 50.;
        *(vthresh+6*NCOLS+3) = 50.;
        *(vthresh+7*NCOLS+3) = 60.;
        *(vthresh+8*NCOLS+3) = 3.;
        *(vthresh+9*NCOLS+3) = 18.;
        *(vthresh+10*NCOLS+3) = 7.;
        *(vthresh+11*NCOLS+3) = 60.;
        *(vthresh+12*NCOLS+3) = 50.;
        *(vthresh+14*NCOLS+3) = 40.;
        *(vthresh+15*NCOLS+3) = 50.;
        *(dthresh+1*NCOLS+3) = 70.;
        *(dthresh+2*NCOLS+3) = 30.;
        *(dthresh+3*NCOLS+3) = 40.;
        *(dthresh+4*NCOLS+3) = 70.;
        *(dthresh+5*NCOLS+3) = 80.;
        *(dthresh+6*NCOLS+3) = 60.;
        *(dthresh+7*NCOLS+3) = 50.;
        *(dthresh+8*NCOLS+3) = 10.;
        *(dthresh+9*NCOLS+3) = 10.;
        *(dthresh+10*NCOLS+3) = 10.;
        *(dthresh+11*NCOLS+3) = 30.;
        *(dthresh+12*NCOLS+3) = 70.;
        *(dthresh+14*NCOLS+3) = 60.;
        *(dthresh+15*NCOLS+3) = 60.;
    }
    if (RunNum == 28) {
        *(athresh+1*NCOLS+3) = 11.;
        *(athresh+2*NCOLS+3) = 2.;
        *(athresh+3*NCOLS+3) = 2.;
        *(athresh+4*NCOLS+3) = 5.;
        *(athresh+5*NCOLS+3) = 7.;
        *(athresh+6*NCOLS+3) = 4.;
        *(athresh+7*NCOLS+3) = 4.;
        *(athresh+8*NCOLS+3) = 0.02;
        *(athresh+9*NCOLS+3) = 0.5;
        *(athresh+10*NCOLS+3) = 0.05;
        *(athresh+11*NCOLS+3) = 3.;
        *(athresh+12*NCOLS+3) = 3.;
        *(athresh+14*NCOLS+3) = 4.;
        *(athresh+15*NCOLS+3) = 4.;
        *(vthresh+1*NCOLS+3) = 200.;
        *(vthresh+2*NCOLS+3) = 80.;
        *(vthresh+3*NCOLS+3) = 50.;
        *(vthresh+4*NCOLS+3) = 50.;
        *(vthresh+5*NCOLS+3) = 50.;
        *(vthresh+6*NCOLS+3) = 50.;
        *(vthresh+7*NCOLS+3) = 60.;
        *(vthresh+8*NCOLS+3) = 3.;
        *(vthresh+9*NCOLS+3) = 18.;
        *(vthresh+10*NCOLS+3) = 7.;
        *(vthresh+11*NCOLS+3) = 60.;
        *(vthresh+12*NCOLS+3) = 50.;
        *(vthresh+14*NCOLS+3) = 40.;
        *(vthresh+15*NCOLS+3) = 50.;
        *(dthresh+1*NCOLS+3) = 70.;
        *(dthresh+2*NCOLS+3) = 30.;
        *(dthresh+3*NCOLS+3) = 40.;
        *(dthresh+4*NCOLS+3) = 70.;
        *(dthresh+5*NCOLS+3) = 80.;
        *(dthresh+6*NCOLS+3) = 60.;
        *(dthresh+7*NCOLS+3) = 50.;
        *(dthresh+8*NCOLS+3) = 10.;
        *(dthresh+9*NCOLS+3) = 10.;
        *(dthresh+10*NCOLS+3) = 10.;
        *(dthresh+11*NCOLS+3) = 30.;
        *(dthresh+12*NCOLS+3) = 70.;
        *(dthresh+14*NCOLS+3) = 60.;
        *(dthresh+15*NCOLS+3) = 60.;
    }
    if ((RunNum == 32)||(RunNum == 33)) {
        *(athresh+1*NCOLS+3) = 40.;
        *(athresh+2*NCOLS+3) = 20.;
        *(athresh+3*NCOLS+3) = 10.;
        *(athresh+4*NCOLS+3) = 12.;
        *(athresh+5*NCOLS+3) = 18.;
        *(athresh+6*NCOLS+3) = 12.;
        *(athresh+7*NCOLS+3) = 18.;
        *(athresh+8*NCOLS+3) = 0.7;
        *(athresh+9*NCOLS+3) = 3.;
        *(athresh+10*NCOLS+3) = 1.8;
        *(athresh+11*NCOLS+3) = 10.;
        *(athresh+12*NCOLS+3) = 18.;
        *(athresh+14*NCOLS+3) = 11.;
        *(athresh+15*NCOLS+3) = 12.;
        *(vthresh+1*NCOLS+3) = 350.;
        *(vthresh+2*NCOLS+3) = 200.;
        *(vthresh+3*NCOLS+3) = 350.;
        *(vthresh+4*NCOLS+3) = 200.;
        *(vthresh+5*NCOLS+3) = 250.;
        *(vthresh+6*NCOLS+3) = 220.;
        *(vthresh+7*NCOLS+3) = 400.;
        *(vthresh+8*NCOLS+3) = 20.;
        *(vthresh+9*NCOLS+3) = 80.;
        *(vthresh+10*NCOLS+3) = 100.;
        *(vthresh+11*NCOLS+3) = 250.;
        *(vthresh+12*NCOLS+3) = 250.;
        *(vthresh+14*NCOLS+3) = 180.;
        *(vthresh+15*NCOLS+3) = 180.;
        *(dthresh+1*NCOLS+3) = 70.;
        *(dthresh+2*NCOLS+3) = 30.;
        *(dthresh+3*NCOLS+3) = 40.;
        *(dthresh+4*NCOLS+3) = 70.;
        *(dthresh+5*NCOLS+3) = 80.;
        *(dthresh+6*NCOLS+3) = 60.;
        *(dthresh+7*NCOLS+3) = 50.;
        *(dthresh+8*NCOLS+3) = 10.;
        *(dthresh+9*NCOLS+3) = 10.;
        *(dthresh+10*NCOLS+3) = 10.;
        *(dthresh+11*NCOLS+3) = 30.;
        *(dthresh+12*NCOLS+3) = 70.;
        *(dthresh+14*NCOLS+3) = 60.;
        *(dthresh+15*NCOLS+3) = 60.;
    }
    if (RunNum == 48) {
        *(athresh+1*NCOLS+3) = 8.;
        *(athresh+2*NCOLS+3) = 5.;
        *(athresh+3*NCOLS+3) = 1.5;
        *(athresh+4*NCOLS+3) = 8.;
        *(athresh+5*NCOLS+3) = 10.;
        *(athresh+6*NCOLS+3) = 6.;
        *(athresh+7*NCOLS+3) = 4.;
        *(athresh+8*NCOLS+3) = 0.2;
        *(athresh+9*NCOLS+3) = 1.5;
        *(athresh+10*NCOLS+3) = 1.5;
        *(athresh+11*NCOLS+3) = 5.;
        *(athresh+12*NCOLS+3) = 9.;
        *(athresh+14*NCOLS+3) = 8.;
        *(athresh+15*NCOLS+3) = 6.;
        *(vthresh+1*NCOLS+3) = 100.;
        *(vthresh+2*NCOLS+3) = 100.;
        *(vthresh+3*NCOLS+3) = 50.;
        *(vthresh+4*NCOLS+3) = 80.;
        *(vthresh+5*NCOLS+3) = 80.;
        *(vthresh+6*NCOLS+3) = 80.;
        *(vthresh+7*NCOLS+3) = 80.;
        *(vthresh+8*NCOLS+3) = 8.;
        *(vthresh+9*NCOLS+3) = 35.;
        *(vthresh+10*NCOLS+3) = 80.;
        *(vthresh+11*NCOLS+3) = 80.;
        *(vthresh+12*NCOLS+3) = 100.;
        *(vthresh+14*NCOLS+3) = 80.;
        *(vthresh+15*NCOLS+3) = 80.;
        *(dthresh+1*NCOLS+3) = 70.;
        *(dthresh+2*NCOLS+3) = 30.;
        *(dthresh+3*NCOLS+3) = 40.;
        *(dthresh+4*NCOLS+3) = 70.;
        *(dthresh+5*NCOLS+3) = 80.;
        *(dthresh+6*NCOLS+3) = 60.;
        *(dthresh+7*NCOLS+3) = 50.;
        *(dthresh+8*NCOLS+3) = 10.;
        *(dthresh+9*NCOLS+3) = 10.;
        *(dthresh+10*NCOLS+3) = 10.;
        *(dthresh+11*NCOLS+3) = 30.;
        *(dthresh+12*NCOLS+3) = 70.;
        *(dthresh+14*NCOLS+3) = 60.;
        *(dthresh+15*NCOLS+3) = 60.;
    }
    if (RunNum == 50) {
        *(athresh+1*NCOLS+3) = 10.;
        *(athresh+2*NCOLS+3) = 8.;
        *(athresh+3*NCOLS+3) = 3.;
        *(athresh+4*NCOLS+3) = 10.;
        *(athresh+5*NCOLS+3) = 15.;
        *(athresh+6*NCOLS+3) = 8.;
        *(athresh+7*NCOLS+3) = 6.;
        *(athresh+8*NCOLS+3) = 0.5;
        *(athresh+9*NCOLS+3) = 2.5;
        *(athresh+10*NCOLS+3) = 0.8;
        *(athresh+11*NCOLS+3) = 9.;
        *(athresh+12*NCOLS+3) = 15.;
        *(athresh+14*NCOLS+3) = 9.;
        *(athresh+15*NCOLS+3) = 10.;
        *(vthresh+1*NCOLS+3) = 250.;
        *(vthresh+2*NCOLS+3) = 200.;
        *(vthresh+3*NCOLS+3) = 70.;
        *(vthresh+4*NCOLS+3) = 150.;
        *(vthresh+5*NCOLS+3) = 200.;
        *(vthresh+6*NCOLS+3) = 120.;
        *(vthresh+7*NCOLS+3) = 150.;
        *(vthresh+8*NCOLS+3) = 20.;
        *(vthresh+9*NCOLS+3) = 60.;
        *(vthresh+10*NCOLS+3) = 30.;
        *(vthresh+11*NCOLS+3) = 200.;
        *(vthresh+12*NCOLS+3) = 200.;
        *(vthresh+14*NCOLS+3) = 130.;
        *(vthresh+15*NCOLS+3) = 150.;
        *(dthresh+1*NCOLS+3) = 70.;
        *(dthresh+2*NCOLS+3) = 30.;
        *(dthresh+3*NCOLS+3) = 40.;
        *(dthresh+4*NCOLS+3) = 70.;
        *(dthresh+5*NCOLS+3) = 80.;
        *(dthresh+6*NCOLS+3) = 60.;
        *(dthresh+7*NCOLS+3) = 50.;
        *(dthresh+8*NCOLS+3) = 10.;
        *(dthresh+9*NCOLS+3) = 10.;
        *(dthresh+10*NCOLS+3) = 10.;
        *(dthresh+11*NCOLS+3) = 30.;
        *(dthresh+12*NCOLS+3) = 70.;
        *(dthresh+14*NCOLS+3) = 60.;
        *(dthresh+15*NCOLS+3) = 60.;
    }

    if (RunNum == 61) {
        *(athresh+1*NCOLS+3) = 60.;
        *(athresh+2*NCOLS+3) = 60.;
        *(athresh+3*NCOLS+3) = 60.;
        *(athresh+4*NCOLS+3) = 10.;
        *(athresh+5*NCOLS+3) = 10.;
        *(athresh+6*NCOLS+3) = 10.;
        *(athresh+7*NCOLS+3) = 10.;
        *(athresh+8*NCOLS+3) = 20.;
        *(athresh+9*NCOLS+3) = 50.;
        *(athresh+10*NCOLS+3) = 20.;
        *(athresh+11*NCOLS+3) = 70.;
        *(athresh+12*NCOLS+3) = 10.;
        *(athresh+14*NCOLS+3) = 10.;
        *(athresh+15*NCOLS+3) = 10.;
        *(vthresh+1*NCOLS+3) = 600.;
        *(vthresh+2*NCOLS+3) = 600.;
        *(vthresh+3*NCOLS+3) = 600.;
        *(vthresh+4*NCOLS+3) = 100.;
        *(vthresh+5*NCOLS+3) = 100.;
        *(vthresh+6*NCOLS+3) = 100.;
        *(vthresh+7*NCOLS+3) = 600.;
        *(vthresh+8*NCOLS+3) = 600.;
        *(vthresh+9*NCOLS+3) = 250.;
        *(vthresh+10*NCOLS+3) = 600.;
        *(vthresh+11*NCOLS+3) = 250.;
        *(vthresh+12*NCOLS+3) = 100.;
        *(vthresh+14*NCOLS+3) = 100.;
        *(vthresh+15*NCOLS+3) = 100.;
        *(dthresh+1*NCOLS+3) = 70.;
        *(dthresh+2*NCOLS+3) = 30.;
        *(dthresh+3*NCOLS+3) = 40.;
        *(dthresh+4*NCOLS+3) = 70.;
        *(dthresh+5*NCOLS+3) = 80.;
        *(dthresh+6*NCOLS+3) = 60.;
        *(dthresh+7*NCOLS+3) = 50.;
        *(dthresh+8*NCOLS+3) = 10.;
        *(dthresh+9*NCOLS+3) = 10.;
        *(dthresh+10*NCOLS+3) = 10.;
        *(dthresh+11*NCOLS+3) = 30.;
        *(dthresh+12*NCOLS+3) = 70.;
        *(dthresh+14*NCOLS+3) = 60.;
        *(dthresh+15*NCOLS+3) = 60.;
    }

    if (RunNum == 97) {
        *(athresh+1*NCOLS+3) = 2.;
        *(athresh+2*NCOLS+3) = 0.5;
        *(athresh+3*NCOLS+3) = 0.5;
        *(athresh+4*NCOLS+3) = 1.;
        *(athresh+5*NCOLS+3) = 1.;
        *(athresh+6*NCOLS+3) = 1.;
        *(athresh+7*NCOLS+3) = 1.;
        *(athresh+8*NCOLS+3) = 0.01;
        *(athresh+9*NCOLS+3) = 0.05;
        *(athresh+10*NCOLS+3) = 0.01;
        *(athresh+11*NCOLS+3) = 0.5;
        *(athresh+12*NCOLS+3) = 1.;
        *(athresh+14*NCOLS+3) = 1.;
        *(athresh+15*NCOLS+3) = 1.;
        *(vthresh+1*NCOLS+3) = 40.;
        *(vthresh+2*NCOLS+3) = 20.;
        *(vthresh+3*NCOLS+3) = 10.;
        *(vthresh+4*NCOLS+3) = 10.;
        *(vthresh+5*NCOLS+3) = 10.;
        *(vthresh+6*NCOLS+3) = 10.;
        *(vthresh+7*NCOLS+3) = 20.;
        *(vthresh+8*NCOLS+3) = 2.;
        *(vthresh+9*NCOLS+3) = 2.;
        *(vthresh+10*NCOLS+3) = 2.;
        *(vthresh+11*NCOLS+3) = 10.;
        *(vthresh+12*NCOLS+3) = 15.;
        *(vthresh+14*NCOLS+3) = 15.;
        *(vthresh+15*NCOLS+3) = 15.;
        *(dthresh+1*NCOLS+3) = 10.;
        *(dthresh+2*NCOLS+3) = 10.;
        *(dthresh+3*NCOLS+3) = 10.;
        *(dthresh+4*NCOLS+3) = 10.;
        *(dthresh+5*NCOLS+3) = 10.;
        *(dthresh+6*NCOLS+3) = 10.;
        *(dthresh+7*NCOLS+3) = 10.;
        *(dthresh+8*NCOLS+3) = 10.;
        *(dthresh+9*NCOLS+3) = 10.;
        *(dthresh+10*NCOLS+3) = 10.;
        *(dthresh+11*NCOLS+3) = 10.;
        *(dthresh+12*NCOLS+3) = 10.;
        *(dthresh+14*NCOLS+3) = 10.;
        *(dthresh+15*NCOLS+3) = 10.;
    }
    if (RunNum == 242 || RunNum == 243) {
        *(athresh+0*NCOLS+3) = 50.;
        *(athresh+1*NCOLS+3) = 50.;
        *(athresh+2*NCOLS+3) = 50.;
        *(athresh+3*NCOLS+3) = 50.;
        *(athresh+4*NCOLS+3) = 50.;
        *(athresh+5*NCOLS+3) = 50.;
        *(athresh+6*NCOLS+3) = 50.;
        *(athresh+7*NCOLS+3) = 50.;
        *(athresh+8*NCOLS+3) = 50.;
        *(athresh+9*NCOLS+3) = 50.;
        *(athresh+10*NCOLS+3) = 50.;
        *(athresh+11*NCOLS+3) = 50.;
        *(athresh+12*NCOLS+3) = 50.;
        *(athresh+14*NCOLS+3) = 50.;
        *(athresh+15*NCOLS+3) = 50.;
        *(vthresh+0*NCOLS+3) = 500.;
        *(vthresh+1*NCOLS+3) = 500.;
        *(vthresh+2*NCOLS+3) = 500.;
        *(vthresh+3*NCOLS+3) = 500.;
        *(vthresh+4*NCOLS+3) = 500.;
        *(vthresh+5*NCOLS+3) = 500.;
        *(vthresh+6*NCOLS+3) = 500.;
        *(vthresh+7*NCOLS+3) = 500.;
        *(vthresh+8*NCOLS+3) = 500.;
        *(vthresh+9*NCOLS+3) = 500.;
        *(vthresh+10*NCOLS+3) = 500.;
        *(vthresh+11*NCOLS+3) = 500.;
        *(vthresh+12*NCOLS+3) = 500.;
        *(vthresh+14*NCOLS+3) = 500.;
        *(vthresh+15*NCOLS+3) = 500.;
        *(dthresh+0*NCOLS+3) = 70.;
        *(dthresh+1*NCOLS+3) = 70.;
        *(dthresh+2*NCOLS+3) = 30.;
        *(dthresh+3*NCOLS+3) = 40.;
        *(dthresh+4*NCOLS+3) = 70.;
        *(dthresh+5*NCOLS+3) = 80.;
        *(dthresh+6*NCOLS+3) = 60.;
        *(dthresh+7*NCOLS+3) = 50.;
        *(dthresh+8*NCOLS+3) = 10.;
        *(dthresh+9*NCOLS+3) = 10.;
        *(dthresh+10*NCOLS+3) = 10.;
        *(dthresh+11*NCOLS+3) = 30.;
        *(dthresh+12*NCOLS+3) = 70.;
        *(dthresh+14*NCOLS+3) = 60.;
        *(dthresh+15*NCOLS+3) = 60.;
    }
    if (RunNum >= 247 ) {
        *(athresh+0*NCOLS+3) = 2;
        *(athresh+1*NCOLS+3) = 2;
        *(athresh+2*NCOLS+3) = 0.1;
        *(athresh+3*NCOLS+3) = 0.1;
        *(athresh+4*NCOLS+3) = 0.1;
        *(athresh+5*NCOLS+3) = 0.1;
        *(athresh+6*NCOLS+3) = 2;
        *(athresh+7*NCOLS+3) = 2;
        *(athresh+8*NCOLS+3) = 2;
        *(athresh+9*NCOLS+3) = 2;
        *(athresh+10*NCOLS+3) = 2;
        *(athresh+11*NCOLS+3) = 2;
        *(athresh+12*NCOLS+3) = 2;
        *(athresh+13*NCOLS+3) = 0.1;
        *(athresh+14*NCOLS+3) = 2;
        *(athresh+15*NCOLS+3) = 2;
        *(vthresh+0*NCOLS+3) = 30.;
        *(vthresh+1*NCOLS+3) = 30.;
        *(vthresh+2*NCOLS+3) = 7.;
        *(vthresh+3*NCOLS+3) = 3.;
        *(vthresh+4*NCOLS+3) = 3.;
        *(vthresh+5*NCOLS+3) = 3.;
        *(vthresh+6*NCOLS+3) = 30.;
        *(vthresh+7*NCOLS+3) = 30.;
        *(vthresh+8*NCOLS+3) = 30.;
        *(vthresh+9*NCOLS+3) = 30.;
        *(vthresh+10*NCOLS+3) = 30.;
        *(vthresh+11*NCOLS+3) = 30.;
        *(vthresh+12*NCOLS+3) = 30.;
        *(vthresh+13*NCOLS+3) = 3.;
        *(vthresh+14*NCOLS+3) = 30.;
        *(vthresh+15*NCOLS+3) = 30.;
        *(dthresh+0*NCOLS+3) = 60.;
        *(dthresh+1*NCOLS+3) = 60.;
        *(dthresh+2*NCOLS+3) = 20.;
        *(dthresh+3*NCOLS+3) = 20.;
        *(dthresh+4*NCOLS+3) = 20.;
        *(dthresh+5*NCOLS+3) = 20.;
        *(dthresh+6*NCOLS+3) = 60.;
        *(dthresh+7*NCOLS+3) = 60.;
        *(dthresh+8*NCOLS+3) = 20.;
        *(dthresh+9*NCOLS+3) = 20.;
        *(dthresh+10*NCOLS+3) = 10.;
        *(dthresh+11*NCOLS+3) = 60.;
        *(dthresh+12*NCOLS+3) = 60.;
        *(dthresh+13*NCOLS+3) = 20.;
        *(dthresh+14*NCOLS+3) = 60.;
        *(dthresh+15*NCOLS+3) = 60.;
    }
    if (RunNum >= 253 ) {
        // Needs to be updated.
        *(athresh+0*NCOLS+3) = 7;
        *(athresh+1*NCOLS+3) = 10;
        *(athresh+2*NCOLS+3) = 1.2;
        *(athresh+3*NCOLS+3) = 0.5;
        *(athresh+4*NCOLS+3) = 0.2;
        *(athresh+5*NCOLS+3) = 1.1;
        *(athresh+6*NCOLS+3) = 10;
        *(athresh+7*NCOLS+3) = 12;
        *(athresh+8*NCOLS+3) = 10;
        *(athresh+9*NCOLS+3) = 2;
        *(athresh+10*NCOLS+3) = 5;
        *(athresh+11*NCOLS+3) = 6;
        *(athresh+12*NCOLS+3) = 12;
        *(athresh+13*NCOLS+3) = 0.7;
        *(athresh+14*NCOLS+3) = 10;
        *(athresh+15*NCOLS+3) = 10;
        *(vthresh+0*NCOLS+3) = 60.;
        *(vthresh+1*NCOLS+3) = 80.;
        *(vthresh+2*NCOLS+3) = 30.;
        *(vthresh+3*NCOLS+3) = 10.;
        *(vthresh+4*NCOLS+3) = 6.;
        *(vthresh+5*NCOLS+3) = 20.;
        *(vthresh+6*NCOLS+3) = 100.;
        *(vthresh+7*NCOLS+3) = 150.;
        *(vthresh+8*NCOLS+3) = 120.;
        *(vthresh+9*NCOLS+3) = 30.;
        *(vthresh+10*NCOLS+3) = 150.;
        *(vthresh+11*NCOLS+3) = 70.;
        *(vthresh+12*NCOLS+3) = 150.;
        *(vthresh+13*NCOLS+3) = 15.;
        *(vthresh+14*NCOLS+3) = 150.;
        *(vthresh+15*NCOLS+3) = 120.;
        // Duration thresholds not yet optimized
        *(dthresh+0*NCOLS+3) = 60.;
        *(dthresh+1*NCOLS+3) = 60.;
        *(dthresh+2*NCOLS+3) = 20.;
        *(dthresh+3*NCOLS+3) = 20.;
        *(dthresh+4*NCOLS+3) = 20.;
        *(dthresh+5*NCOLS+3) = 20.;
        *(dthresh+6*NCOLS+3) = 60.;
        *(dthresh+7*NCOLS+3) = 60.;
        *(dthresh+8*NCOLS+3) = 20.;
        *(dthresh+9*NCOLS+3) = 20.;
        *(dthresh+10*NCOLS+3) = 10.;
        *(dthresh+11*NCOLS+3) = 60.;
        *(dthresh+12*NCOLS+3) = 60.;
        *(dthresh+13*NCOLS+3) = 20.;
        *(dthresh+14*NCOLS+3) = 60.;
        *(dthresh+15*NCOLS+3) = 60.;
    }
    if (RunNum >= 255 ) {
        *(athresh+0*NCOLS+3) = 10;
        *(athresh+1*NCOLS+3) = 10;
        *(athresh+2*NCOLS+3) = 2;
        *(athresh+3*NCOLS+3) = 2;
        *(athresh+4*NCOLS+3) = 0.5;
        *(athresh+5*NCOLS+3) = 2;
        *(athresh+6*NCOLS+3) = 10;
        *(athresh+7*NCOLS+3) = 15;
        *(athresh+8*NCOLS+3) = 10;
        *(athresh+9*NCOLS+3) = 2;
        *(athresh+10*NCOLS+3) = 10;
        *(athresh+11*NCOLS+3) = 10;
        *(athresh+12*NCOLS+3) = 15;
        *(athresh+13*NCOLS+3) = 2;
        *(athresh+14*NCOLS+3) = 15;
        *(athresh+15*NCOLS+3) = 15;
        *(vthresh+0*NCOLS+3) = 100.;
        *(vthresh+1*NCOLS+3) = 100.;
        *(vthresh+2*NCOLS+3) = 60.;
        *(vthresh+3*NCOLS+3) = 30.;
        *(vthresh+4*NCOLS+3) = 18.;
        *(vthresh+5*NCOLS+3) = 50.;
        *(vthresh+6*NCOLS+3) = 100.;
        *(vthresh+7*NCOLS+3) = 200.;
        *(vthresh+8*NCOLS+3) = 200.;
        *(vthresh+9*NCOLS+3) = 100.;
        *(vthresh+10*NCOLS+3) = 30.;
        *(vthresh+11*NCOLS+3) = 30.;
        *(vthresh+12*NCOLS+3) = 200.;
        *(vthresh+13*NCOLS+3) = 40.;
        *(vthresh+14*NCOLS+3) = 200.;
        *(vthresh+15*NCOLS+3) = 150.;
        // Duration thresholds not updated.
        *(dthresh+0*NCOLS+3) = 60.;
        *(dthresh+1*NCOLS+3) = 60.;
        *(dthresh+2*NCOLS+3) = 20.;
        *(dthresh+3*NCOLS+3) = 20.;
        *(dthresh+4*NCOLS+3) = 20.;
        *(dthresh+5*NCOLS+3) = 20.;
        *(dthresh+6*NCOLS+3) = 60.;
        *(dthresh+7*NCOLS+3) = 60.;
        *(dthresh+8*NCOLS+3) = 20.;
        *(dthresh+9*NCOLS+3) = 20.;
        *(dthresh+10*NCOLS+3) = 10.;
        *(dthresh+11*NCOLS+3) = 60.;
        *(dthresh+12*NCOLS+3) = 60.;
        *(dthresh+13*NCOLS+3) = 20.;
        *(dthresh+14*NCOLS+3) = 60.;
        *(dthresh+15*NCOLS+3) = 60.;
    }

    if (RunNum >= 286 ) {
        *(athresh+0*NCOLS+3) = 1.5;
        *(athresh+1*NCOLS+3) = 2;
        *(athresh+2*NCOLS+3) = 20;
        *(athresh+3*NCOLS+3) = 14;
        *(athresh+4*NCOLS+3) = 4;
        *(athresh+5*NCOLS+3) = 20;
        *(athresh+6*NCOLS+3) = 2;
        *(athresh+7*NCOLS+3) = 2.5;
        *(athresh+8*NCOLS+3) = 2;
        *(athresh+9*NCOLS+3) = 2.5;
        *(athresh+10*NCOLS+3) = 0.5;
        *(athresh+11*NCOLS+3) = 2;
        *(athresh+12*NCOLS+3) = 2.5;
        *(athresh+13*NCOLS+3) = 14;
        *(athresh+14*NCOLS+3) = 2;
        *(athresh+15*NCOLS+3) = 2;
        *(vthresh+0*NCOLS+3) = 20.;
        *(vthresh+1*NCOLS+3) = 25.;
        *(vthresh+2*NCOLS+3) = 600.;
        *(vthresh+3*NCOLS+3) = 250.;
        *(vthresh+4*NCOLS+3) = 120.;
        *(vthresh+5*NCOLS+3) = 400.;
        *(vthresh+6*NCOLS+3) = 30.;
        *(vthresh+7*NCOLS+3) = 35.;
        *(vthresh+8*NCOLS+3) = 30.;
        *(vthresh+9*NCOLS+3) = 35.;
        *(vthresh+10*NCOLS+3) = 20.;
        *(vthresh+11*NCOLS+3) = 25.;
        *(vthresh+12*NCOLS+3) = 35.;
        *(vthresh+13*NCOLS+3) = 300.;
        *(vthresh+14*NCOLS+3) = 30.;
        *(vthresh+15*NCOLS+3) = 30.;
        // Duration thresholds not updated.
        *(dthresh+0*NCOLS+3) = 60.;
        *(dthresh+1*NCOLS+3) = 60.;
        *(dthresh+2*NCOLS+3) = 20.;
        *(dthresh+3*NCOLS+3) = 20.;
        *(dthresh+4*NCOLS+3) = 20.;
        *(dthresh+5*NCOLS+3) = 20.;
        *(dthresh+6*NCOLS+3) = 60.;
        *(dthresh+7*NCOLS+3) = 60.;
        *(dthresh+8*NCOLS+3) = 20.;
        *(dthresh+9*NCOLS+3) = 20.;
        *(dthresh+10*NCOLS+3) = 10.;
        *(dthresh+11*NCOLS+3) = 60.;
        *(dthresh+12*NCOLS+3) = 60.;
        *(dthresh+13*NCOLS+3) = 20.;
        *(dthresh+14*NCOLS+3) = 60.;
        *(dthresh+15*NCOLS+3) = 60.;
    }


    if (RunNum >= 288 ) { // First run after rechanneling for second digitizer 
        *(athresh+0*NCOLS+3) = 0.1;
        *(athresh+1*NCOLS+3) = 0.1;
        *(athresh+2*NCOLS+3) = 0.1;
        *(athresh+3*NCOLS+3) = 0.1;
        *(athresh+4*NCOLS+3) = 0.1;
        *(athresh+5*NCOLS+3) = 0.1;
        *(athresh+6*NCOLS+3) = 0.1;
        *(athresh+7*NCOLS+3) = 0.1;
        *(athresh+8*NCOLS+3) = 0.1;
        *(athresh+9*NCOLS+3) = 0.1;
        *(athresh+10*NCOLS+3) = 0.1;
        *(athresh+11*NCOLS+3) = 0.1;
        *(athresh+12*NCOLS+3) = 0.1;
        *(athresh+13*NCOLS+3) = 0.1;
        *(athresh+14*NCOLS+3) = 0.1;
        *(athresh+15*NCOLS+3) = 0.1;
        *(athresh+16*NCOLS+3) = 0.1;
        *(athresh+17*NCOLS+3) = 0.1;
        *(athresh+18*NCOLS+3) = 0.1;
        *(athresh+19*NCOLS+3) = 0.1;
        *(athresh+20*NCOLS+3) = 0.1;
        *(athresh+21*NCOLS+3) = 0.1;
        *(athresh+22*NCOLS+3) = 0.1;
        *(athresh+23*NCOLS+3) = 0.1;
        *(athresh+24*NCOLS+3) = 0.1;
        *(athresh+25*NCOLS+3) = 0.1;
        *(athresh+26*NCOLS+3) = 0.1;
        *(athresh+27*NCOLS+3) = 0.1;
        *(athresh+28*NCOLS+3) = 0.1;
        *(athresh+29*NCOLS+3) = 0.1;
        *(athresh+30*NCOLS+3) = 0.1;
        *(athresh+31*NCOLS+3) = 0.1;
        *(vthresh+0*NCOLS+3) = 25.;
        *(vthresh+1*NCOLS+3) = 25.;
        *(vthresh+2*NCOLS+3) = 30.;
        *(vthresh+3*NCOLS+3) = 25.;
        *(vthresh+4*NCOLS+3) = 30.;
        *(vthresh+5*NCOLS+3) = 15.;
        *(vthresh+6*NCOLS+3) = 30.;
        *(vthresh+7*NCOLS+3) = 30.;
        *(vthresh+8*NCOLS+3) = 100.;
        *(vthresh+9*NCOLS+3) = 200.;
        *(vthresh+10*NCOLS+3) = 6.;
        *(vthresh+11*NCOLS+3) = 6.;
        *(vthresh+12*NCOLS+3) = 25.;
        *(vthresh+13*NCOLS+3) = 25.;
        *(vthresh+14*NCOLS+3) = 5.;
        *(vthresh+15*NCOLS+3) = 30.;
        *(vthresh+16*NCOLS+3) = 30.;
        *(vthresh+17*NCOLS+3) = 300.;
        *(vthresh+18*NCOLS+3) = 6.;
        *(vthresh+19*NCOLS+3) = 5.;
        *(vthresh+20*NCOLS+3) = 6.;
        *(vthresh+21*NCOLS+3) = 7.;
        *(vthresh+22*NCOLS+3) = 20.;
        *(vthresh+23*NCOLS+3) = 25.;
        *(vthresh+24*NCOLS+3) = 600.;
        *(vthresh+25*NCOLS+3) = 200.;
        *(vthresh+26*NCOLS+3) = 6.;
        *(vthresh+27*NCOLS+3) = 6.;
        *(vthresh+28*NCOLS+3) = 5.;
        *(vthresh+29*NCOLS+3) = 5.;
        *(vthresh+30*NCOLS+3) = 5.;
        *(vthresh+31*NCOLS+3) = 5.;
        // Duration thresholds not updated.
        *(dthresh+0*NCOLS+3) = 10.;
        *(dthresh+1*NCOLS+3) = 10.;
        *(dthresh+2*NCOLS+3) = 10.;
        *(dthresh+3*NCOLS+3) = 10.;
        *(dthresh+4*NCOLS+3) = 10.;
        *(dthresh+5*NCOLS+3) = 10.;
        *(dthresh+6*NCOLS+3) = 10.;
        *(dthresh+7*NCOLS+3) = 10.;
        *(dthresh+8*NCOLS+3) = 10.;
        *(dthresh+9*NCOLS+3) = 10.;
        *(dthresh+10*NCOLS+3) = 10.;
        *(dthresh+11*NCOLS+3) = 10.;
        *(dthresh+12*NCOLS+3) = 10.;
        *(dthresh+13*NCOLS+3) = 10.;
        *(dthresh+14*NCOLS+3) = 10.;
        *(dthresh+15*NCOLS+3) = 10.;
        *(dthresh+16*NCOLS+3) = 10.;
        *(dthresh+17*NCOLS+3) = 10.;
        *(dthresh+18*NCOLS+3) = 10.;
        *(dthresh+19*NCOLS+3) = 10.;
        *(dthresh+20*NCOLS+3) = 10.;
        *(dthresh+21*NCOLS+3) = 10.;
        *(dthresh+22*NCOLS+3) = 10.;
        *(dthresh+23*NCOLS+3) = 10.;
        *(dthresh+24*NCOLS+3) = 10.;
        *(dthresh+25*NCOLS+3) = 10.;
        *(dthresh+26*NCOLS+3) = 10.;
        *(dthresh+27*NCOLS+3) = 10.;
        *(dthresh+28*NCOLS+3) = 10.;
        *(dthresh+29*NCOLS+3) = 10.;
        *(dthresh+30*NCOLS+3) = 10.;
        *(dthresh+31*NCOLS+3) = 10.;
    }

    if (RunNum >= 374 ) { // 1600 on ET and 1450 on all else
        *(athresh+0*NCOLS+3) = 20;
        *(athresh+1*NCOLS+3) = 20;
        *(athresh+2*NCOLS+3) = 20;
        *(athresh+3*NCOLS+3) = 20;
        *(athresh+4*NCOLS+3) = 0.1;
        *(athresh+5*NCOLS+3) = 0.1;
        *(athresh+6*NCOLS+3) = 20;
        *(athresh+7*NCOLS+3) = 20;
        *(athresh+8*NCOLS+3) = 0.1;
        *(athresh+9*NCOLS+3) = 0.1;
        *(athresh+10*NCOLS+3) = 0.1;
        *(athresh+11*NCOLS+3) = 0.1;
        *(athresh+12*NCOLS+3) = 0.1;
        *(athresh+13*NCOLS+3) = 0.1;
        *(athresh+14*NCOLS+3) = 0.1;
        *(athresh+15*NCOLS+3) = 0.1;
        *(athresh+16*NCOLS+3) = 0.1;
        *(athresh+17*NCOLS+3) = 0.1;
        *(athresh+18*NCOLS+3) = 0.1;
        *(athresh+19*NCOLS+3) = 0.1;
        *(athresh+20*NCOLS+3) = 0.1;
        *(athresh+21*NCOLS+3) = 0.1;
        *(athresh+22*NCOLS+3) = 0.1;
        *(athresh+23*NCOLS+3) = 0.1;
        *(athresh+24*NCOLS+3) = 0.1;
        *(athresh+25*NCOLS+3) = 0.1;
        *(athresh+26*NCOLS+3) = 0.1;
        *(athresh+27*NCOLS+3) = 0.1;
        *(athresh+28*NCOLS+3) = 0.1;
        *(athresh+29*NCOLS+3) = 0.1;
        *(athresh+30*NCOLS+3) = 0.1;
        *(athresh+31*NCOLS+3) = 0.1;
        *(vthresh+0*NCOLS+3) = 300.;
        *(vthresh+1*NCOLS+3) = 300.;
        *(vthresh+2*NCOLS+3) = 350.;
        *(vthresh+3*NCOLS+3) = 350.;
        *(vthresh+4*NCOLS+3) = 30.;
        *(vthresh+5*NCOLS+3) = 15.;
        *(vthresh+6*NCOLS+3) = 400.;
        *(vthresh+7*NCOLS+3) = 400.;
        *(vthresh+8*NCOLS+3) = 100.;
        *(vthresh+9*NCOLS+3) = 100.;
        *(vthresh+10*NCOLS+3) = 30.;
        *(vthresh+11*NCOLS+3) = 30.;
        *(vthresh+12*NCOLS+3) = 25.;
        *(vthresh+13*NCOLS+3) = 25.;
        *(vthresh+14*NCOLS+3) = 30.;
        *(vthresh+15*NCOLS+3) = 30.;
        *(vthresh+16*NCOLS+3) = 30.;
        *(vthresh+17*NCOLS+3) = 200.;
        *(vthresh+18*NCOLS+3) = 600.;
        *(vthresh+19*NCOLS+3) = 30.;
        *(vthresh+20*NCOLS+3) = 500.;
        *(vthresh+21*NCOLS+3) = 500.;
        *(vthresh+22*NCOLS+3) = 20.;
        *(vthresh+23*NCOLS+3) = 25.;
        *(vthresh+24*NCOLS+3) = 200.;
        *(vthresh+25*NCOLS+3) = 200.;
        *(vthresh+26*NCOLS+3) = 30.;
        *(vthresh+27*NCOLS+3) = 30.;
        *(vthresh+28*NCOLS+3) = 500.;
        *(vthresh+29*NCOLS+3) = 30.;
        *(vthresh+30*NCOLS+3) = 30.;
        *(vthresh+31*NCOLS+3) = 30.;
        // Duration thresholds not updated.
        *(dthresh+0*NCOLS+3) = 400.; // 878
        *(dthresh+1*NCOLS+3) = 400.; // 878
        *(dthresh+2*NCOLS+3) = 400.; // 878
        *(dthresh+3*NCOLS+3) = 400.; // 878
        *(dthresh+4*NCOLS+3) = 400.; // 878
        *(dthresh+5*NCOLS+3) = 40.; // 7725
        *(dthresh+6*NCOLS+3) = 400.; // 878
        *(dthresh+7*NCOLS+3) = 400.; // 878
        *(dthresh+8*NCOLS+3) = 50.; // ET
        *(dthresh+9*NCOLS+3) = 50.; // ET
        *(dthresh+10*NCOLS+3) = 10.; // 878 - L0 top panel
        *(dthresh+11*NCOLS+3) = 10.; // 878 - L1 top panel
        *(dthresh+12*NCOLS+3) = 400.; // 878
        *(dthresh+13*NCOLS+3) = 400.; // 878
        *(dthresh+14*NCOLS+3) = 10.; // 878 - L2 top panel
        *(dthresh+15*NCOLS+3) = 10.; // LHC clock
        *(dthresh+16*NCOLS+3) = 400.; // 878
        *(dthresh+17*NCOLS+3) = 50.; // ET
        *(dthresh+18*NCOLS+3) = 400.; // 878 - L0 slab
        *(dthresh+19*NCOLS+3) = 10.; // 878 - L1 right panel
        *(dthresh+20*NCOLS+3) = 400.; // 878 - L1 slab
        *(dthresh+21*NCOLS+3) = 400.; // 878 - Back slab
        *(dthresh+22*NCOLS+3) = 40.; // 7725
        *(dthresh+23*NCOLS+3) = 400.; // 878
        *(dthresh+24*NCOLS+3) = 50.; // ET
        *(dthresh+25*NCOLS+3) = 50.; // ET
        *(dthresh+26*NCOLS+3) = 10.; // 878 - L2 right panel
        *(dthresh+27*NCOLS+3) = 10.; // 878 - L0 left panel
        *(dthresh+28*NCOLS+3) = 400.; // 878 - L2 slab
        *(dthresh+29*NCOLS+3) = 10.; // 878 - L0 right panel
        *(dthresh+30*NCOLS+3) = 10.; // 878 - L1 left panel
        *(dthresh+31*NCOLS+3) = 10.; // 878 - L2 left panel
    }

    if (RunNum >= 424 ) { // 1600 on ET and 1450 on all else
        *(athresh+0*NCOLS+3) = 3;
        *(athresh+1*NCOLS+3) = 3;
        *(athresh+2*NCOLS+3) = 5;
        *(athresh+3*NCOLS+3) = 5;
        *(athresh+4*NCOLS+3) = 5;
        *(athresh+5*NCOLS+3) = 2;
        *(athresh+6*NCOLS+3) = 4;
        *(athresh+7*NCOLS+3) = 6;
        *(athresh+8*NCOLS+3) = 0.6;
        *(athresh+9*NCOLS+3) = 3;
        *(athresh+10*NCOLS+3) = 2;
        *(athresh+11*NCOLS+3) = 2;
        *(athresh+12*NCOLS+3) = 5;
        *(athresh+13*NCOLS+3) = 5;
        *(athresh+14*NCOLS+3) = 0.1;
        *(athresh+15*NCOLS+3) = 0.1;
        *(athresh+16*NCOLS+3) = 5;
        *(athresh+17*NCOLS+3) = 2;
        *(athresh+18*NCOLS+3) = 60;
        *(athresh+19*NCOLS+3) = 0.1;
        *(athresh+20*NCOLS+3) = 0.5;
        *(athresh+21*NCOLS+3) = 0.1;
        *(athresh+22*NCOLS+3) = 1.5;
        *(athresh+23*NCOLS+3) = 3;
        *(athresh+24*NCOLS+3) = 1.5;
        *(athresh+25*NCOLS+3) = 2;
        *(athresh+26*NCOLS+3) = 0.1;
        *(athresh+27*NCOLS+3) = 1;
        *(athresh+28*NCOLS+3) = 0.2;
        *(athresh+29*NCOLS+3) = 1;
        *(athresh+30*NCOLS+3) = 2;
        *(athresh+31*NCOLS+3) = 1;
        *(vthresh+0*NCOLS+3) = 50.;
        *(vthresh+1*NCOLS+3) = 60.;
        *(vthresh+2*NCOLS+3) = 70.;
        *(vthresh+3*NCOLS+3) = 70.;
        *(vthresh+4*NCOLS+3) = 70.;
        *(vthresh+5*NCOLS+3) = 50.;
        *(vthresh+6*NCOLS+3) = 60.;
        *(vthresh+7*NCOLS+3) = 80.;
        *(vthresh+8*NCOLS+3) = 15.;
        *(vthresh+9*NCOLS+3) = 50.;
        *(vthresh+10*NCOLS+3) = 40.;
        *(vthresh+11*NCOLS+3) = 30.;
        *(vthresh+12*NCOLS+3) = 60.;
        *(vthresh+13*NCOLS+3) = 60.;
        *(vthresh+14*NCOLS+3) = 10.;
        *(vthresh+15*NCOLS+3) = 30.;
        *(vthresh+16*NCOLS+3) = 80.;
        *(vthresh+17*NCOLS+3) = 50.;
        *(vthresh+18*NCOLS+3) = 600.;
        *(vthresh+19*NCOLS+3) = 10.;
        *(vthresh+20*NCOLS+3) = 15.;
        *(vthresh+21*NCOLS+3) = 10.;
        *(vthresh+22*NCOLS+3) = 50.;
        *(vthresh+23*NCOLS+3) = 50.;
        *(vthresh+24*NCOLS+3) = 100.;
        *(vthresh+25*NCOLS+3) = 30.;
        *(vthresh+26*NCOLS+3) = 10.;
        *(vthresh+27*NCOLS+3) = 20.;
        *(vthresh+28*NCOLS+3) = 10.;
        *(vthresh+29*NCOLS+3) = 20.;
        *(vthresh+30*NCOLS+3) = 40.;
        *(vthresh+31*NCOLS+3) = 30.;
        // Duration thresholds not updated.
        *(dthresh+0*NCOLS+3) = 40.; // 878
        *(dthresh+1*NCOLS+3) = 60.; // 878
        *(dthresh+2*NCOLS+3) = 60.; // 878
        *(dthresh+3*NCOLS+3) = 60.; // 878
        *(dthresh+4*NCOLS+3) = 60.; // 878
        *(dthresh+5*NCOLS+3) = 40.; // 7725
        *(dthresh+6*NCOLS+3) = 60.; // 878
        *(dthresh+7*NCOLS+3) = 60.; // 878
        *(dthresh+8*NCOLS+3) = 40.; // ET
        *(dthresh+9*NCOLS+3) = 40.; // ET
        *(dthresh+10*NCOLS+3) = 60.; // 878 - L0 top panel
        *(dthresh+11*NCOLS+3) = 10.; // 878 - L1 top panel
        *(dthresh+12*NCOLS+3) = 60.; // 878
        *(dthresh+13*NCOLS+3) = 60.; // 878
        *(dthresh+14*NCOLS+3) = 20.; // 878 - L2 top panel
        *(dthresh+15*NCOLS+3) = 10.; // LHC clock
        *(dthresh+16*NCOLS+3) = 60.; // 878
        *(dthresh+17*NCOLS+3) = 40.; // ET
        *(dthresh+18*NCOLS+3) = 400.; // 878 - L0 slab
        *(dthresh+19*NCOLS+3) = 10.; // 878 - L1 right panel
        *(dthresh+20*NCOLS+3) = 60.; // 878 - L1 slab
        *(dthresh+21*NCOLS+3) = 60.; // 878 - Back slab
        *(dthresh+22*NCOLS+3) = 20.; // 7725
        *(dthresh+23*NCOLS+3) = 40.; // 878
        *(dthresh+24*NCOLS+3) = 40.; // ET
        *(dthresh+25*NCOLS+3) = 40.; // ET
        *(dthresh+26*NCOLS+3) = 10.; // 878 - L2 right panel
        *(dthresh+27*NCOLS+3) = 10.; // 878 - L0 left panel
        *(dthresh+28*NCOLS+3) = 20.; // 878 - L2 slab
        *(dthresh+29*NCOLS+3) = 10.; // 878 - L0 right panel
        *(dthresh+30*NCOLS+3) = 50.; // 878 - L1 left panel
        *(dthresh+31*NCOLS+3) = 10.; // 878 - L2 left panel
    }

    if (RunNum >= 430 ) { // ET=1050, 878=750, 7725=900
        *(athresh+0*NCOLS+3) = 1;
        *(athresh+1*NCOLS+3) = 1;
        *(athresh+2*NCOLS+3) = 2;
        *(athresh+3*NCOLS+3) = 2;
        *(athresh+4*NCOLS+3) = 2;
        *(athresh+5*NCOLS+3) = 5;
        *(athresh+6*NCOLS+3) = 1.5;
        *(athresh+7*NCOLS+3) = 2;
        *(athresh+8*NCOLS+3) = 1;
        *(athresh+9*NCOLS+3) = 5;
        *(athresh+10*NCOLS+3) = 2;
        *(athresh+11*NCOLS+3) = 2;
        *(athresh+12*NCOLS+3) = 2;
        *(athresh+13*NCOLS+3) = 2;
        *(athresh+14*NCOLS+3) = 0.1;
        *(athresh+15*NCOLS+3) = 999; // LHC clock
        *(athresh+16*NCOLS+3) = 2;
        *(athresh+17*NCOLS+3) = 2;
        *(athresh+18*NCOLS+3) = 2;
        *(athresh+19*NCOLS+3) = 0.1;
        *(athresh+20*NCOLS+3) = 0.1;
        *(athresh+21*NCOLS+3) = 0.1;
        *(athresh+22*NCOLS+3) = 2;
        *(athresh+23*NCOLS+3) = 2;
        *(athresh+24*NCOLS+3) = 5;
        *(athresh+25*NCOLS+3) = 3;
        *(athresh+26*NCOLS+3) = 0.1;
        *(athresh+27*NCOLS+3) = 1;
        *(athresh+28*NCOLS+3) = 0.1;
        *(athresh+29*NCOLS+3) = 1;
        *(athresh+30*NCOLS+3) = 2;
        *(athresh+31*NCOLS+3) = 2;
        *(vthresh+0*NCOLS+3) = 20.;
        *(vthresh+1*NCOLS+3) = 30.;
        *(vthresh+2*NCOLS+3) = 30.;
        *(vthresh+3*NCOLS+3) = 30.;
        *(vthresh+4*NCOLS+3) = 30.;
        *(vthresh+5*NCOLS+3) = 30.;
        *(vthresh+6*NCOLS+3) = 30.;
        *(vthresh+7*NCOLS+3) = 30.;
        *(vthresh+8*NCOLS+3) = 10.;
        *(vthresh+9*NCOLS+3) = 40.;
        *(vthresh+10*NCOLS+3) = 40.;
        *(vthresh+11*NCOLS+3) = 30.;
        *(vthresh+12*NCOLS+3) = 40.;
        *(vthresh+13*NCOLS+3) = 30.;
        *(vthresh+14*NCOLS+3) = 20.;
        *(vthresh+15*NCOLS+3) = 999.; // LHC clock
        *(vthresh+16*NCOLS+3) = 20.;
        *(vthresh+17*NCOLS+3) = 30.;
        *(vthresh+18*NCOLS+3) = 400.;
        *(vthresh+19*NCOLS+3) = 10.;
        *(vthresh+20*NCOLS+3) = 10.;
        *(vthresh+21*NCOLS+3) = 10.;
        *(vthresh+22*NCOLS+3) = 1000.;
        *(vthresh+23*NCOLS+3) = 20.;
        *(vthresh+24*NCOLS+3) = 50.;
        *(vthresh+25*NCOLS+3) = 30.;
        *(vthresh+26*NCOLS+3) = 10.;
        *(vthresh+27*NCOLS+3) = 20.;
        *(vthresh+28*NCOLS+3) = 10.;
        *(vthresh+29*NCOLS+3) = 20.;
        *(vthresh+30*NCOLS+3) = 40.;
        *(vthresh+31*NCOLS+3) = 30.;
        // Duration thresholds not updated.
        *(dthresh+0*NCOLS+3) = 40.; // 878
        *(dthresh+1*NCOLS+3) = 60.; // 878
        *(dthresh+2*NCOLS+3) = 60.; // 878
        *(dthresh+3*NCOLS+3) = 60.; // 878
        *(dthresh+4*NCOLS+3) = 60.; // 878
        *(dthresh+5*NCOLS+3) = 40.; // 7725
        *(dthresh+6*NCOLS+3) = 60.; // 878
        *(dthresh+7*NCOLS+3) = 60.; // 878
        *(dthresh+8*NCOLS+3) = 40.; // ET
        *(dthresh+9*NCOLS+3) = 40.; // ET
        *(dthresh+10*NCOLS+3) = 60.; // 878 - L0 top panel
        *(dthresh+11*NCOLS+3) = 10.; // 878 - L1 top panel
        *(dthresh+12*NCOLS+3) = 60.; // 878
        *(dthresh+13*NCOLS+3) = 60.; // 878
        *(dthresh+14*NCOLS+3) = 20.; // 878 - L2 top panel
        *(dthresh+15*NCOLS+3) = 10.; // LHC clock
        *(dthresh+16*NCOLS+3) = 60.; // 878
        *(dthresh+17*NCOLS+3) = 40.; // ET
        *(dthresh+18*NCOLS+3) = 40.; // 878 - L0 slab
        *(dthresh+19*NCOLS+3) = 10.; // 878 - L1 right panel
        *(dthresh+20*NCOLS+3) = 60.; // 878 - L1 slab
        *(dthresh+21*NCOLS+3) = 60.; // 878 - Back slab
        *(dthresh+22*NCOLS+3) = 20.; // 7725
        *(dthresh+23*NCOLS+3) = 40.; // 878
        *(dthresh+24*NCOLS+3) = 40.; // ET
        *(dthresh+25*NCOLS+3) = 40.; // ET
        *(dthresh+26*NCOLS+3) = 10.; // 878 - L2 right panel
        *(dthresh+27*NCOLS+3) = 10.; // 878 - L0 left panel
        *(dthresh+28*NCOLS+3) = 20.; // 878 - L2 slab
        *(dthresh+29*NCOLS+3) = 10.; // 878 - L0 right panel
        *(dthresh+30*NCOLS+3) = 50.; // 878 - L1 left panel
        *(dthresh+31*NCOLS+3) = 10.; // 878 - L2 left panel
    }

    if (RunNum >= 485 ) { // ET=1050, 878=750, 7725=900
        *(athresh+0*NCOLS+3) = 2;
        *(athresh+1*NCOLS+3) = 3;
        *(athresh+2*NCOLS+3) = 4;
        *(athresh+3*NCOLS+3) = 4;
        *(athresh+4*NCOLS+3) = 4;
        *(athresh+5*NCOLS+3) = 3;
        *(athresh+6*NCOLS+3) = 3;
        *(athresh+7*NCOLS+3) = 3;
        *(athresh+8*NCOLS+3) = 0.5;
        *(athresh+9*NCOLS+3) = 3;
        *(athresh+10*NCOLS+3) = 2;
        *(athresh+11*NCOLS+3) = 2;
        *(athresh+12*NCOLS+3) = 4;
        *(athresh+13*NCOLS+3) = 4;
        *(athresh+14*NCOLS+3) = 2;
        *(athresh+15*NCOLS+3) = 999; // LHC clock
        *(athresh+16*NCOLS+3) = 4;
        *(athresh+17*NCOLS+3) = 2;
        *(athresh+18*NCOLS+3) = 80;
        *(athresh+19*NCOLS+3) = 2;
        *(athresh+20*NCOLS+3) = 40;
        *(athresh+21*NCOLS+3) = 40;
        *(athresh+22*NCOLS+3) = 20;
        *(athresh+23*NCOLS+3) = 60;
        *(athresh+24*NCOLS+3) = 3;
        *(athresh+25*NCOLS+3) = 1;
        *(athresh+26*NCOLS+3) = 2;
        *(athresh+27*NCOLS+3) = 2;
        *(athresh+28*NCOLS+3) = 20;
        *(athresh+29*NCOLS+3) = 2;
        *(athresh+30*NCOLS+3) = 2;
        *(athresh+31*NCOLS+3) = 2;
        *(vthresh+0*NCOLS+3) = 30.;
        *(vthresh+1*NCOLS+3) = 40.;
        *(vthresh+2*NCOLS+3) = 50.;
        *(vthresh+3*NCOLS+3) = 50.;
        *(vthresh+4*NCOLS+3) = 30.;
        *(vthresh+5*NCOLS+3) = 50.;
        *(vthresh+6*NCOLS+3) = 50.;
        *(vthresh+7*NCOLS+3) = 50.;
        *(vthresh+8*NCOLS+3) = 15.;
        *(vthresh+9*NCOLS+3) = 50.;
        *(vthresh+10*NCOLS+3) = 40.;
        *(vthresh+11*NCOLS+3) = 20.;
        *(vthresh+12*NCOLS+3) = 50.;
        *(vthresh+13*NCOLS+3) = 50.;
        *(vthresh+14*NCOLS+3) = 30.;
        *(vthresh+15*NCOLS+3) = 999.; // LHC clock
        *(vthresh+16*NCOLS+3) = 50.;
        *(vthresh+17*NCOLS+3) = 50.;
        *(vthresh+18*NCOLS+3) = 600.;
        *(vthresh+19*NCOLS+3) = 50.;
        *(vthresh+20*NCOLS+3) = 400.;
        *(vthresh+21*NCOLS+3) = 600.;
        *(vthresh+22*NCOLS+3) = 1000.;
        *(vthresh+23*NCOLS+3) = 400.;
        *(vthresh+24*NCOLS+3) = 100.;
        *(vthresh+25*NCOLS+3) = 40.;
        *(vthresh+26*NCOLS+3) = 30.;
        *(vthresh+27*NCOLS+3) = 20.;
        *(vthresh+28*NCOLS+3) = 300.;
        *(vthresh+29*NCOLS+3) = 20.;
        *(vthresh+30*NCOLS+3) = 40.;
        *(vthresh+31*NCOLS+3) = 30.;
        // Duration thresholds not updated.
        *(dthresh+0*NCOLS+3) = 40.; // 878
        *(dthresh+1*NCOLS+3) = 60.; // 878
        *(dthresh+2*NCOLS+3) = 60.; // 878
        *(dthresh+3*NCOLS+3) = 60.; // 878
        *(dthresh+4*NCOLS+3) = 60.; // 878
        *(dthresh+5*NCOLS+3) = 40.; // 7725
        *(dthresh+6*NCOLS+3) = 60.; // 878
        *(dthresh+7*NCOLS+3) = 60.; // 878
        *(dthresh+8*NCOLS+3) = 40.; // ET
        *(dthresh+9*NCOLS+3) = 40.; // ET
        *(dthresh+10*NCOLS+3) = 60.; // 878 - L0 top panel
        *(dthresh+11*NCOLS+3) = 10.; // 878 - L1 top panel
        *(dthresh+12*NCOLS+3) = 60.; // 878
        *(dthresh+13*NCOLS+3) = 60.; // 878
        *(dthresh+14*NCOLS+3) = 20.; // 878 - L2 top panel
        *(dthresh+15*NCOLS+3) = 10.; // LHC clock
        *(dthresh+16*NCOLS+3) = 60.; // 878
        *(dthresh+17*NCOLS+3) = 40.; // ET
        *(dthresh+18*NCOLS+3) = 40.; // 878 - L0 slab
        *(dthresh+19*NCOLS+3) = 10.; // 878 - L1 right panel
        *(dthresh+20*NCOLS+3) = 60.; // 878 - L1 slab
        *(dthresh+21*NCOLS+3) = 60.; // 878 - Back slab
        *(dthresh+22*NCOLS+3) = 20.; // 7725
        *(dthresh+23*NCOLS+3) = 40.; // 878
        *(dthresh+24*NCOLS+3) = 40.; // ET
        *(dthresh+25*NCOLS+3) = 40.; // ET
        *(dthresh+26*NCOLS+3) = 10.; // 878 - L2 right panel
        *(dthresh+27*NCOLS+3) = 10.; // 878 - L0 left panel
        *(dthresh+28*NCOLS+3) = 20.; // 878 - L2 slab
        *(dthresh+29*NCOLS+3) = 10.; // 878 - L0 right panel
        *(dthresh+30*NCOLS+3) = 50.; // 878 - L1 left panel
        *(dthresh+31*NCOLS+3) = 10.; // 878 - L2 left panel
    }


    if (RunNum >= 491 ) { // ET=1100, 878=825, 7725=875
        *(athresh+0*NCOLS+3) = 4;
        *(athresh+1*NCOLS+3) = 5;
        *(athresh+2*NCOLS+3) = 5;
        *(athresh+3*NCOLS+3) = 5;
        *(athresh+4*NCOLS+3) = 4;
        *(athresh+5*NCOLS+3) = 3;
        *(athresh+6*NCOLS+3) = 5;
        *(athresh+7*NCOLS+3) = 5;
        *(athresh+8*NCOLS+3) = 1.5;
        *(athresh+9*NCOLS+3) = 9;
        *(athresh+10*NCOLS+3) = 2;
        *(athresh+11*NCOLS+3) = 2;
        *(athresh+12*NCOLS+3) = 5;
        *(athresh+13*NCOLS+3) = 5;
        *(athresh+14*NCOLS+3) = 2;
        *(athresh+15*NCOLS+3) = 999; // LHC clock
        *(athresh+16*NCOLS+3) = 5;
        *(athresh+17*NCOLS+3) = 5;
        *(athresh+18*NCOLS+3) = 40;
        *(athresh+19*NCOLS+3) = 2;
        *(athresh+20*NCOLS+3) = 30;
        *(athresh+21*NCOLS+3) = 30;
        *(athresh+22*NCOLS+3) = 40;
        *(athresh+23*NCOLS+3) = 60;
        *(athresh+24*NCOLS+3) = 8;
        *(athresh+25*NCOLS+3) = 5;
        *(athresh+26*NCOLS+3) = 2;
        *(athresh+27*NCOLS+3) = 1.5;
        *(athresh+28*NCOLS+3) = 15;
        *(athresh+29*NCOLS+3) = 1.5;
        *(athresh+30*NCOLS+3) = 2;
        *(athresh+31*NCOLS+3) = 2;
        *(vthresh+0*NCOLS+3) = 50.;
        *(vthresh+1*NCOLS+3) = 50.;
        *(vthresh+2*NCOLS+3) = 90.;
        *(vthresh+3*NCOLS+3) = 60.;
        *(vthresh+4*NCOLS+3) = 60.;
        *(vthresh+5*NCOLS+3) = 50.;
        *(vthresh+6*NCOLS+3) = 70.;
        *(vthresh+7*NCOLS+3) = 80.;
        *(vthresh+8*NCOLS+3) = 40.;
        *(vthresh+9*NCOLS+3) = 100.;
        *(vthresh+10*NCOLS+3) = 40.;
        *(vthresh+11*NCOLS+3) = 30.;
        *(vthresh+12*NCOLS+3) = 60.;
        *(vthresh+13*NCOLS+3) = 60.;
        *(vthresh+14*NCOLS+3) = 30.;
        *(vthresh+15*NCOLS+3) = 999.; // LHC clock
        *(vthresh+16*NCOLS+3) = 60.;
        *(vthresh+17*NCOLS+3) = 60.;
        *(vthresh+18*NCOLS+3) = 600.;
        *(vthresh+19*NCOLS+3) = 60.;
        *(vthresh+20*NCOLS+3) = 400.;
        *(vthresh+21*NCOLS+3) = 400.;
        *(vthresh+22*NCOLS+3) = 1200.;
        *(vthresh+23*NCOLS+3) = 500.;
        *(vthresh+24*NCOLS+3) = 200.;
        *(vthresh+25*NCOLS+3) = 100.;
        *(vthresh+26*NCOLS+3) = 30.;
        *(vthresh+27*NCOLS+3) = 20.;
        *(vthresh+28*NCOLS+3) = 300.;
        *(vthresh+29*NCOLS+3) = 20.;
        *(vthresh+30*NCOLS+3) = 40.;
        *(vthresh+31*NCOLS+3) = 30.;
        // Duration thresholds not updated.
        *(dthresh+0*NCOLS+3) = 40.; // 878
        *(dthresh+1*NCOLS+3) = 40.; // 878
        *(dthresh+2*NCOLS+3) = 40.; // 878
        *(dthresh+3*NCOLS+3) = 40.; // 878
        *(dthresh+4*NCOLS+3) = 4.; // 878  Affected by noise?
        *(dthresh+5*NCOLS+3) = 40.; // 7725
        *(dthresh+6*NCOLS+3) = 40.; // 878
        *(dthresh+7*NCOLS+3) = 40.; // 878
        *(dthresh+8*NCOLS+3) = 40.; // ET
        *(dthresh+9*NCOLS+3) = 40.; // ET
        *(dthresh+10*NCOLS+3) = 40.; // 878 - L0 top panel
        *(dthresh+11*NCOLS+3) = 10.; // 878 - L1 top panel
        *(dthresh+12*NCOLS+3) = 40.; // 878
        *(dthresh+13*NCOLS+3) = 40.; // 878
        *(dthresh+14*NCOLS+3) = 20.; // 878 - L2 top panel
        *(dthresh+15*NCOLS+3) = 10.; // LHC clock
        *(dthresh+16*NCOLS+3) = 40.; // 878
        *(dthresh+17*NCOLS+3) = 40.; // ET
        *(dthresh+18*NCOLS+3) = 40.; // 878 - L0 slab
        *(dthresh+19*NCOLS+3) = 10.; // 878 - L1 right panel
        *(dthresh+20*NCOLS+3) = 40.; // 878 - L1 slab
        *(dthresh+21*NCOLS+3) = 40.; // 878 - Back slab
        *(dthresh+22*NCOLS+3) = 40.; // 7725
        *(dthresh+23*NCOLS+3) = 400.; // 878
        *(dthresh+24*NCOLS+3) = 40.; // ET
        *(dthresh+25*NCOLS+3) = 40.; // ET
        *(dthresh+26*NCOLS+3) = 10.; // 878 - L2 right panel
        *(dthresh+27*NCOLS+3) = 10.; // 878 - L0 left panel
        *(dthresh+28*NCOLS+3) = 40.; // 878 - L2 slab
        *(dthresh+29*NCOLS+3) = 10.; // 878 - L0 right panel
        *(dthresh+30*NCOLS+3) = 40.; // 878 - L1 left panel
        *(dthresh+31*NCOLS+3) = 10.; // 878 - L2 left panel
    }


    if (RunNum >= 497 ) { // ET=1100, 878=825, 7725=875, B ramping (ramped) to 3.8T
        *(athresh+0*NCOLS+3) = 2;
        *(athresh+1*NCOLS+3) = 2;
        *(athresh+2*NCOLS+3) = 2;
        *(athresh+3*NCOLS+3) = 2;
        *(athresh+4*NCOLS+3) = 2;
        *(athresh+5*NCOLS+3) = 3;
        *(athresh+6*NCOLS+3) = 2;
        *(athresh+7*NCOLS+3) = 2;
        *(athresh+8*NCOLS+3) = 0.5;
        *(athresh+9*NCOLS+3) = 4;
        *(athresh+10*NCOLS+3) = 0.5;
        *(athresh+11*NCOLS+3) = 0.5;
        *(athresh+12*NCOLS+3) = 2;
        *(athresh+13*NCOLS+3) = 2;
        *(athresh+14*NCOLS+3) = 0.5;
        *(athresh+15*NCOLS+3) = 999; // LHC clock
        *(athresh+16*NCOLS+3) = 2;
        *(athresh+17*NCOLS+3) = 2;
        *(athresh+18*NCOLS+3) = 10;
        *(athresh+19*NCOLS+3) = 2;
        *(athresh+20*NCOLS+3) = 10;
        *(athresh+21*NCOLS+3) = 10;
        *(athresh+22*NCOLS+3) = 20;
        *(athresh+23*NCOLS+3) = 40;
        *(athresh+24*NCOLS+3) = 2;
        *(athresh+25*NCOLS+3) = 2;
        *(athresh+26*NCOLS+3) = 1;
        *(athresh+27*NCOLS+3) = 0.5;
        *(athresh+28*NCOLS+3) = 5;
        *(athresh+29*NCOLS+3) = 0.5;
        *(athresh+30*NCOLS+3) = 1;
        *(athresh+31*NCOLS+3) = 1;
        *(vthresh+0*NCOLS+3) = 30.;
        *(vthresh+1*NCOLS+3) = 30.;
        *(vthresh+2*NCOLS+3) = 30.;
        *(vthresh+3*NCOLS+3) = 30.;
        *(vthresh+4*NCOLS+3) = 20.;
        *(vthresh+5*NCOLS+3) = 40.;
        *(vthresh+6*NCOLS+3) = 40.;
        *(vthresh+7*NCOLS+3) = 40.;
        *(vthresh+8*NCOLS+3) = 10.;
        *(vthresh+9*NCOLS+3) = 90.;
        *(vthresh+10*NCOLS+3) = 10.;
        *(vthresh+11*NCOLS+3) = 20.;
        *(vthresh+12*NCOLS+3) = 40.;
        *(vthresh+13*NCOLS+3) = 40.;
        *(vthresh+14*NCOLS+3) = 10.;
        *(vthresh+15*NCOLS+3) = 999.; // LHC clock
        *(vthresh+16*NCOLS+3) = 40.;
        *(vthresh+17*NCOLS+3) = 40.;
        *(vthresh+18*NCOLS+3) = 300.;
        *(vthresh+19*NCOLS+3) = 40.;
        *(vthresh+20*NCOLS+3) = 300.;
        *(vthresh+21*NCOLS+3) = 300.;
        *(vthresh+22*NCOLS+3) = 1200.;
        *(vthresh+23*NCOLS+3) = 400.;
        *(vthresh+24*NCOLS+3) = 100.;
        *(vthresh+25*NCOLS+3) = 50.;
        *(vthresh+26*NCOLS+3) = 20.;
        *(vthresh+27*NCOLS+3) = 5.;
        *(vthresh+28*NCOLS+3) = 100.;
        *(vthresh+29*NCOLS+3) = 10.;
        *(vthresh+30*NCOLS+3) = 20.;
        *(vthresh+31*NCOLS+3) = 5.;
        // Duration thresholds not updated.
        *(dthresh+0*NCOLS+3) = 40.; // 878
        *(dthresh+1*NCOLS+3) = 40.; // 878
        *(dthresh+2*NCOLS+3) = 40.; // 878
        *(dthresh+3*NCOLS+3) = 40.; // 878
        *(dthresh+4*NCOLS+3) = 1.; // 878  Affected by noise?
        *(dthresh+5*NCOLS+3) = 40.; // 7725
        *(dthresh+6*NCOLS+3) = 40.; // 878
        *(dthresh+7*NCOLS+3) = 40.; // 878
        *(dthresh+8*NCOLS+3) = 40.; // ET
        *(dthresh+9*NCOLS+3) = 40.; // ET
        *(dthresh+10*NCOLS+3) = 40.; // 878 - L0 top panel
        *(dthresh+11*NCOLS+3) = 10.; // 878 - L1 top panel
        *(dthresh+12*NCOLS+3) = 40.; // 878
        *(dthresh+13*NCOLS+3) = 40.; // 878
        *(dthresh+14*NCOLS+3) = 20.; // 878 - L2 top panel
        *(dthresh+15*NCOLS+3) = 10.; // LHC clock
        *(dthresh+16*NCOLS+3) = 40.; // 878
        *(dthresh+17*NCOLS+3) = 40.; // ET
        *(dthresh+18*NCOLS+3) = 40.; // 878 - L0 slab
        *(dthresh+19*NCOLS+3) = 10.; // 878 - L1 right panel
        *(dthresh+20*NCOLS+3) = 40.; // 878 - L1 slab
        *(dthresh+21*NCOLS+3) = 40.; // 878 - Back slab
        *(dthresh+22*NCOLS+3) = 40.; // 7725
        *(dthresh+23*NCOLS+3) = 400.; // 878
        *(dthresh+24*NCOLS+3) = 40.; // ET
        *(dthresh+25*NCOLS+3) = 40.; // ET
        *(dthresh+26*NCOLS+3) = 10.; // 878 - L2 right panel
        *(dthresh+27*NCOLS+3) = 10.; // 878 - L0 left panel
        *(dthresh+28*NCOLS+3) = 40.; // 878 - L2 slab
        *(dthresh+29*NCOLS+3) = 10.; // 878 - L0 right panel
        *(dthresh+30*NCOLS+3) = 40.; // 878 - L1 left panel
        *(dthresh+31*NCOLS+3) = 10.; // 878 - L2 left panel
    }

    if (RunNum >= 500 ) { // ET=1100, 878=825, 7725=875, B ramping (ramped) to 3.8T
        *(athresh+0*NCOLS+3) = 2;
        *(athresh+1*NCOLS+3) = 2;
        *(athresh+2*NCOLS+3) = 2;
        *(athresh+3*NCOLS+3) = 2;
        *(athresh+4*NCOLS+3) = 2;
        *(athresh+5*NCOLS+3) = 3;
        *(athresh+6*NCOLS+3) = 2;
        *(athresh+7*NCOLS+3) = 2;
        *(athresh+8*NCOLS+3) = 0.5;
        *(athresh+9*NCOLS+3) = 4;
        *(athresh+10*NCOLS+3) = 0.5;
        *(athresh+11*NCOLS+3) = 0.5;
        *(athresh+12*NCOLS+3) = 2;
        *(athresh+13*NCOLS+3) = 2;
        *(athresh+14*NCOLS+3) = 0.5;
        *(athresh+15*NCOLS+3) = 999; // LHC clock
        *(athresh+16*NCOLS+3) = 2;
        *(athresh+17*NCOLS+3) = 2;
        *(athresh+18*NCOLS+3) = 10;
        *(athresh+19*NCOLS+3) = 2;
        *(athresh+20*NCOLS+3) = 10;
        *(athresh+21*NCOLS+3) = 10;
        *(athresh+22*NCOLS+3) = 20;
        *(athresh+23*NCOLS+3) = 40;
        *(athresh+24*NCOLS+3) = 2;
        *(athresh+25*NCOLS+3) = 2;
        *(athresh+26*NCOLS+3) = 1;
        *(athresh+27*NCOLS+3) = 0.5;
        *(athresh+28*NCOLS+3) = 5;
        *(athresh+29*NCOLS+3) = 0.5;
        *(athresh+30*NCOLS+3) = 1;
        *(athresh+31*NCOLS+3) = 1;
        *(vthresh+0*NCOLS+3) = 400.;
        *(vthresh+1*NCOLS+3) = 400.;
        *(vthresh+2*NCOLS+3) = 400.;
        *(vthresh+3*NCOLS+3) = 400.;
        *(vthresh+4*NCOLS+3) = 400.;
        *(vthresh+5*NCOLS+3) = 400.;
        *(vthresh+6*NCOLS+3) = 400.;
        *(vthresh+7*NCOLS+3) = 400.;
        *(vthresh+8*NCOLS+3) = 400.;
        *(vthresh+9*NCOLS+3) = 400.;
        *(vthresh+10*NCOLS+3) = 10.;
        *(vthresh+11*NCOLS+3) = 20.;
        *(vthresh+12*NCOLS+3) = 400.;
        *(vthresh+13*NCOLS+3) = 400.;
        *(vthresh+14*NCOLS+3) = 10.;
        *(vthresh+15*NCOLS+3) = 999.; // LHC clock
        *(vthresh+16*NCOLS+3) = 400.;
        *(vthresh+17*NCOLS+3) = 400.;
        *(vthresh+18*NCOLS+3) = 300.;
        *(vthresh+19*NCOLS+3) = 40.;
        *(vthresh+20*NCOLS+3) = 300.;
        *(vthresh+21*NCOLS+3) = 300.;
        *(vthresh+22*NCOLS+3) = 1200.;
        *(vthresh+23*NCOLS+3) = 400.;
        *(vthresh+24*NCOLS+3) = 400.;
        *(vthresh+25*NCOLS+3) = 400.;
        *(vthresh+26*NCOLS+3) = 20.;
        *(vthresh+27*NCOLS+3) = 5.;
        *(vthresh+28*NCOLS+3) = 100.;
        *(vthresh+29*NCOLS+3) = 10.;
        *(vthresh+30*NCOLS+3) = 20.;
        *(vthresh+31*NCOLS+3) = 5.;
        // Duration thresholds not updated.
        *(dthresh+0*NCOLS+3) = 40.; // 878
        *(dthresh+1*NCOLS+3) = 40.; // 878
        *(dthresh+2*NCOLS+3) = 40.; // 878
        *(dthresh+3*NCOLS+3) = 40.; // 878
        *(dthresh+4*NCOLS+3) = 1.; // 878  Affected by noise?
        *(dthresh+5*NCOLS+3) = 40.; // 7725
        *(dthresh+6*NCOLS+3) = 40.; // 878
        *(dthresh+7*NCOLS+3) = 40.; // 878
        *(dthresh+8*NCOLS+3) = 40.; // ET
        *(dthresh+9*NCOLS+3) = 40.; // ET
        *(dthresh+10*NCOLS+3) = 40.; // 878 - L0 top panel
        *(dthresh+11*NCOLS+3) = 10.; // 878 - L1 top panel
        *(dthresh+12*NCOLS+3) = 40.; // 878
        *(dthresh+13*NCOLS+3) = 40.; // 878
        *(dthresh+14*NCOLS+3) = 20.; // 878 - L2 top panel
        *(dthresh+15*NCOLS+3) = 10.; // LHC clock
        *(dthresh+16*NCOLS+3) = 40.; // 878
        *(dthresh+17*NCOLS+3) = 40.; // ET
        *(dthresh+18*NCOLS+3) = 40.; // 878 - L0 slab
        *(dthresh+19*NCOLS+3) = 10.; // 878 - L1 right panel
        *(dthresh+20*NCOLS+3) = 40.; // 878 - L1 slab
        *(dthresh+21*NCOLS+3) = 40.; // 878 - Back slab
        *(dthresh+22*NCOLS+3) = 40.; // 7725
        *(dthresh+23*NCOLS+3) = 400.; // 878
        *(dthresh+24*NCOLS+3) = 40.; // ET
        *(dthresh+25*NCOLS+3) = 40.; // ET
        *(dthresh+26*NCOLS+3) = 10.; // 878 - L2 right panel
        *(dthresh+27*NCOLS+3) = 10.; // 878 - L0 left panel
        *(dthresh+28*NCOLS+3) = 40.; // 878 - L2 slab
        *(dthresh+29*NCOLS+3) = 10.; // 878 - L0 right panel
        *(dthresh+30*NCOLS+3) = 40.; // 878 - L1 left panel
        *(dthresh+31*NCOLS+3) = 10.; // 878 - L2 left panel
    }

    if (RunNum >= 572 ) { // ET=1100, 878=825, 7725=875, B ramping (ramped) to 3.8T. CONFIRMED VALID
        *(athresh+0*NCOLS+3) = 2.0;
        *(athresh+1*NCOLS+3) = 2.0;
        *(athresh+2*NCOLS+3) = 2.0;
        *(athresh+3*NCOLS+3) = 2.0;
        *(athresh+4*NCOLS+3) = 2.0;
        *(athresh+5*NCOLS+3) = 3.0;
        *(athresh+6*NCOLS+3) = 2.0;
        *(athresh+7*NCOLS+3) = 2.0;
        *(athresh+8*NCOLS+3) = 0.5;
        *(athresh+9*NCOLS+3) = 4.0;
        *(athresh+10*NCOLS+3) = 0.5;
        *(athresh+11*NCOLS+3) = 1.0;
        *(athresh+12*NCOLS+3) = 2.0;
        *(athresh+13*NCOLS+3) = 2.0;
        *(athresh+14*NCOLS+3) = 0.5;
        *(athresh+15*NCOLS+3) = 999; // LHC clock
        *(athresh+16*NCOLS+3) = 4.0;
        *(athresh+17*NCOLS+3) = 4.0;
        *(athresh+18*NCOLS+3) = 20.;
        *(athresh+19*NCOLS+3) = 2.0;
        *(athresh+20*NCOLS+3) = 20.;
        *(athresh+21*NCOLS+3) = 20.;
        *(athresh+22*NCOLS+3) = 2.0;
        *(athresh+23*NCOLS+3) = 40.;
        *(athresh+24*NCOLS+3) = 4.0;
        *(athresh+25*NCOLS+3) = 4.0;
        *(athresh+26*NCOLS+3) = 2.0;
        *(athresh+27*NCOLS+3) = 0.5;
        *(athresh+28*NCOLS+3) = 8.0;
        *(athresh+29*NCOLS+3) = 0.4;
        *(athresh+30*NCOLS+3) = 1.0;
        *(athresh+31*NCOLS+3) = 1.5;
        *(vthresh+0*NCOLS+3) = 40.;
        *(vthresh+1*NCOLS+3) = 70.;
        *(vthresh+2*NCOLS+3) = 80.;
        *(vthresh+3*NCOLS+3) = 60.;
        *(vthresh+4*NCOLS+3) = 70.;
        *(vthresh+5*NCOLS+3) = 70.;
        *(vthresh+6*NCOLS+3) = 70.;
        *(vthresh+7*NCOLS+3) = 100.;
        *(vthresh+8*NCOLS+3) = 15.;
        *(vthresh+9*NCOLS+3) = 150.;
        *(vthresh+10*NCOLS+3) = 20.;
        *(vthresh+11*NCOLS+3) = 25.;
        *(vthresh+12*NCOLS+3) = 70.;
        *(vthresh+13*NCOLS+3) = 70.;
        *(vthresh+14*NCOLS+3) = 10.;
        *(vthresh+15*NCOLS+3) = 999.; // LHC clock
        *(vthresh+16*NCOLS+3) = 80.;
        *(vthresh+17*NCOLS+3) = 100.;
        *(vthresh+18*NCOLS+3) = 300.;
        *(vthresh+19*NCOLS+3) = 50.;
        *(vthresh+20*NCOLS+3) = 300.;
        *(vthresh+21*NCOLS+3) = 350.;
        *(vthresh+22*NCOLS+3) = 100.;
        *(vthresh+23*NCOLS+3) = 400.;
        *(vthresh+24*NCOLS+3) = 150.;
        *(vthresh+25*NCOLS+3) = 90.;
        *(vthresh+26*NCOLS+3) = 30.;
        *(vthresh+27*NCOLS+3) = 8.;
        *(vthresh+28*NCOLS+3) = 100.;
        *(vthresh+29*NCOLS+3) = 8.;
        *(vthresh+30*NCOLS+3) = 30.;
        *(vthresh+31*NCOLS+3) = 30.;
        // Duration thresholds not updated.
        *(dthresh+0*NCOLS+3) = 40.; // 878
        *(dthresh+1*NCOLS+3) = 40.; // 878
        *(dthresh+2*NCOLS+3) = 40.; // 878
        *(dthresh+3*NCOLS+3) = 40.; // 878
        *(dthresh+4*NCOLS+3) = 1.; // 878  Affected by noise?
        *(dthresh+5*NCOLS+3) = 40.; // 7725
        *(dthresh+6*NCOLS+3) = 20.; // 878
        *(dthresh+7*NCOLS+3) = 40.; // 878
        *(dthresh+8*NCOLS+3) = 40.; // ET
        *(dthresh+9*NCOLS+3) = 40.; // ET
        *(dthresh+10*NCOLS+3) = 40.; // 878 - L0 top panel
        *(dthresh+11*NCOLS+3) = 10.; // 878 - L1 top panel
        *(dthresh+12*NCOLS+3) = 40.; // 878
        *(dthresh+13*NCOLS+3) = 40.; // 878
        *(dthresh+14*NCOLS+3) = 20.; // 878 - L2 top panel
        *(dthresh+15*NCOLS+3) = 10.; // LHC clock
        *(dthresh+16*NCOLS+3) = 40.; // 878
        *(dthresh+17*NCOLS+3) = 40.; // ET
        *(dthresh+18*NCOLS+3) = 40.; // 878 - L0 slab
        *(dthresh+19*NCOLS+3) = 10.; // 878 - L1 right panel
        *(dthresh+20*NCOLS+3) = 40.; // 878 - L1 slab
        *(dthresh+21*NCOLS+3) = 40.; // 878 - Back slab
        *(dthresh+22*NCOLS+3) = 40.; // 7725
        *(dthresh+23*NCOLS+3) = 400.; // 878
        *(dthresh+24*NCOLS+3) = 40.; // ET
        *(dthresh+25*NCOLS+3) = 40.; // ET
        *(dthresh+26*NCOLS+3) = 10.; // 878 - L2 right panel
        *(dthresh+27*NCOLS+3) = 10.; // 878 - L0 left panel
        *(dthresh+28*NCOLS+3) = 40.; // 878 - L2 slab
        *(dthresh+29*NCOLS+3) = 10.; // 878 - L0 right panel
        *(dthresh+30*NCOLS+3) = 40.; // 878 - L1 left panel
        *(dthresh+31*NCOLS+3) = 10.; // 878 - L2 left panel
    }

    if (RunNum >= 582 ) { // ET=1000, 878=775, 7725=850, B=3.8T.
        *(vthresh+0*NCOLS+3) = 30.; *(athresh+0*NCOLS+3) = 2.0; *(dthresh+0*NCOLS+3) = 40.; // 878bar
        *(vthresh+1*NCOLS+3) = 50.; *(athresh+1*NCOLS+3) = 3.5; *(dthresh+1*NCOLS+3) = 40.; // 878bar
        *(vthresh+2*NCOLS+3) = 50.; *(athresh+2*NCOLS+3) = 4.0; *(dthresh+2*NCOLS+3) = 40.; // 878bar
        *(vthresh+3*NCOLS+3) = 50.; *(athresh+3*NCOLS+3) = 4.0; *(dthresh+3*NCOLS+3) = 40.; // 878bar
        *(vthresh+4*NCOLS+3) = 40.; *(athresh+4*NCOLS+3) = 4.0; *(dthresh+4*NCOLS+3) = 40.; // 878bar
        *(vthresh+5*NCOLS+3) = 50.; *(athresh+5*NCOLS+3) = 2.5; *(dthresh+5*NCOLS+3) = 40.; // 7725
        *(vthresh+6*NCOLS+3) = 40.; *(athresh+6*NCOLS+3) = 3.0; *(dthresh+6*NCOLS+3) = 20.; // 878bar
        *(vthresh+7*NCOLS+3) = 60.; *(athresh+7*NCOLS+3) = 5.0; *(dthresh+7*NCOLS+3) = 40.; // 878bar
        *(vthresh+8*NCOLS+3) = 5.; *(athresh+8*NCOLS+3) = 0.2; *(dthresh+8*NCOLS+3) = 40.; // ET
        *(vthresh+9*NCOLS+3) = 60.; *(athresh+9*NCOLS+3) = 3.0; *(dthresh+9*NCOLS+3) = 40.; // ET
        *(vthresh+10*NCOLS+3) = 10.; *(athresh+10*NCOLS+3) = 0.6; *(dthresh+10*NCOLS+3) = 40.; // 878 - L0 top panel
        *(vthresh+11*NCOLS+3) = 25.; *(athresh+11*NCOLS+3) = 1.5; *(dthresh+11*NCOLS+3) = 10.; // 878 - L1 left panel
        *(vthresh+12*NCOLS+3) = 50.; *(athresh+12*NCOLS+3) = 4.0; *(dthresh+12*NCOLS+3) = 40.; // 878bar
        *(vthresh+13*NCOLS+3) = 50.; *(athresh+13*NCOLS+3) = 4.0; *(dthresh+13*NCOLS+3) = 40.; // 878bar
        *(vthresh+14*NCOLS+3) = 10.; *(athresh+14*NCOLS+3) = 0.4; *(dthresh+14*NCOLS+3) = 20.; // 878 - L2 top panel
        *(vthresh+15*NCOLS+3) = 999.; *(athresh+15*NCOLS+3) = 999; *(dthresh+15*NCOLS+3) = 10.; // LHC clock
        *(vthresh+16*NCOLS+3) = 50.; *(athresh+16*NCOLS+3) = 4.0; *(dthresh+16*NCOLS+3) = 40.; // 878bar
        *(vthresh+17*NCOLS+3) = 40.; *(athresh+17*NCOLS+3) = 2.0;  *(dthresh+17*NCOLS+3) = 40.; // ET
        *(vthresh+18*NCOLS+3) = 200.; *(athresh+18*NCOLS+3) = 20.; *(dthresh+18*NCOLS+3) = 80.; // 878 - L0 slab
        *(vthresh+19*NCOLS+3) = 40.; *(athresh+19*NCOLS+3) = 3.0; *(dthresh+19*NCOLS+3) = 10.; // 878 - L1 right panel
        *(vthresh+20*NCOLS+3) = 200.; *(athresh+20*NCOLS+3) = 18.; *(dthresh+20*NCOLS+3) = 80.; // 878 - L1 slab
        *(vthresh+21*NCOLS+3) = 320.; *(athresh+21*NCOLS+3) = 25.; *(dthresh+21*NCOLS+3) = 80.; // 878 - Back slab
        *(vthresh+22*NCOLS+3) = 70.; *(athresh+22*NCOLS+3) = 2.3; *(dthresh+22*NCOLS+3) = 40.; // 7725
        *(vthresh+23*NCOLS+3) = 500.; *(athresh+23*NCOLS+3) = 65.; *(dthresh+23*NCOLS+3) = 400.; // 878bar
        *(vthresh+24*NCOLS+3) = 50.; *(athresh+24*NCOLS+3) = 2.0; *(dthresh+24*NCOLS+3) = 40.; // ET
        *(vthresh+25*NCOLS+3) = 35.; *(athresh+25*NCOLS+3) = 1.6; *(dthresh+25*NCOLS+3) = 40.; // ET
        *(vthresh+26*NCOLS+3) = 30.; *(athresh+26*NCOLS+3) = 1.0; *(dthresh+26*NCOLS+3) = 10.; // 878 - L2 right panel
        *(vthresh+27*NCOLS+3) = 8.; *(athresh+27*NCOLS+3) = 0.4; *(dthresh+27*NCOLS+3) = 10.; // 878 - L0 left panel
        *(vthresh+28*NCOLS+3) = 100.; *(athresh+28*NCOLS+3) = 7.0; *(dthresh+28*NCOLS+3) = 80.; // 878 - L2 slab
        *(vthresh+29*NCOLS+3) = 6.; *(athresh+29*NCOLS+3) = 0.4; *(dthresh+29*NCOLS+3) = 10.; // 878 - L0 right panel
        *(vthresh+30*NCOLS+3) = 30.; *(athresh+30*NCOLS+3) = 1.0; *(dthresh+30*NCOLS+3) = 40.; // 878 - L1 top panel
        *(vthresh+31*NCOLS+3) = 25.; *(athresh+31*NCOLS+3) = 1.5; *(dthresh+31*NCOLS+3) = 10.; // 878 - L2 left panel
    }

    if (RunNum >= 616 ) { // ET=1050, 878=750, 7725=900, B=3.8T.
        *(vthresh+0*NCOLS+3) = 25.; *(athresh+0*NCOLS+3) = 1.8; *(dthresh+0*NCOLS+3) = 40.; // 878bar
        *(vthresh+1*NCOLS+3) = 40.; *(athresh+1*NCOLS+3) = 3.0; *(dthresh+1*NCOLS+3) = 40.; // 878bar
        *(vthresh+2*NCOLS+3) = 45.; *(athresh+2*NCOLS+3) = 3.5; *(dthresh+2*NCOLS+3) = 40.; // 878bar
        *(vthresh+3*NCOLS+3) = 40.; *(athresh+3*NCOLS+3) = 3.5; *(dthresh+3*NCOLS+3) = 40.; // 878bar
        *(vthresh+4*NCOLS+3) = 40.; *(athresh+4*NCOLS+3) = 3.5; *(dthresh+4*NCOLS+3) = 40.; // 878bar
        *(vthresh+5*NCOLS+3) = 90.; *(athresh+5*NCOLS+3) = 3.5; *(dthresh+5*NCOLS+3) = 40.; // 7725
        *(vthresh+6*NCOLS+3) = 30.; *(athresh+6*NCOLS+3) = 2.5; *(dthresh+6*NCOLS+3) = 20.; // 878bar
        *(vthresh+7*NCOLS+3) = 55.; *(athresh+7*NCOLS+3) = 4.0; *(dthresh+7*NCOLS+3) = 40.; // 878bar
        *(vthresh+8*NCOLS+3) = 12.; *(athresh+8*NCOLS+3) = 0.3; *(dthresh+8*NCOLS+3) = 40.; // ET
        *(vthresh+9*NCOLS+3) = 80.; *(athresh+9*NCOLS+3) = 5.0; *(dthresh+9*NCOLS+3) = 40.; // ET
        *(vthresh+10*NCOLS+3) = 10.; *(athresh+10*NCOLS+3) = 0.6; *(dthresh+10*NCOLS+3) = 40.; // 878 - L0 top panel
        *(vthresh+11*NCOLS+3) = 25.; *(athresh+11*NCOLS+3) = 1.5; *(dthresh+11*NCOLS+3) = 10.; // 878 - L1 left panel
        *(vthresh+12*NCOLS+3) = 40.; *(athresh+12*NCOLS+3) = 3.5; *(dthresh+12*NCOLS+3) = 40.; // 878bar
        *(vthresh+13*NCOLS+3) = 45.; *(athresh+13*NCOLS+3) = 3.5; *(dthresh+13*NCOLS+3) = 40.; // 878bar
        *(vthresh+14*NCOLS+3) = 10.; *(athresh+14*NCOLS+3) = 0.4; *(dthresh+14*NCOLS+3) = 20.; // 878 - L2 top panel
        *(vthresh+15*NCOLS+3) = 999.; *(athresh+15*NCOLS+3) = 999; *(dthresh+15*NCOLS+3) = 10.; // LHC clock
        *(vthresh+16*NCOLS+3) = 40.; *(athresh+16*NCOLS+3) = 3.5; *(dthresh+16*NCOLS+3) = 40.; // 878bar
        *(vthresh+17*NCOLS+3) = 60.; *(athresh+17*NCOLS+3) = 3.5;  *(dthresh+17*NCOLS+3) = 40.; // ET
        *(vthresh+18*NCOLS+3) = 200.; *(athresh+18*NCOLS+3) = 20.; *(dthresh+18*NCOLS+3) = 80.; // 878 - L0 slab
        *(vthresh+19*NCOLS+3) = 40.; *(athresh+19*NCOLS+3) = 3.0; *(dthresh+19*NCOLS+3) = 10.; // 878 - L1 right panel
        *(vthresh+20*NCOLS+3) = 200.; *(athresh+20*NCOLS+3) = 18.; *(dthresh+20*NCOLS+3) = 80.; // 878 - L1 slab
        *(vthresh+21*NCOLS+3) = 320.; *(athresh+21*NCOLS+3) = 25.; *(dthresh+21*NCOLS+3) = 80.; // 878 - Back slab
        *(vthresh+22*NCOLS+3) = 140.; *(athresh+22*NCOLS+3) = 4.0; *(dthresh+22*NCOLS+3) = 40.; // 7725
        *(vthresh+23*NCOLS+3) = 500.; *(athresh+23*NCOLS+3) = 70.; *(dthresh+23*NCOLS+3) = 400.; // 878bar
        *(vthresh+24*NCOLS+3) = 80.; *(athresh+24*NCOLS+3) = 3.0; *(dthresh+24*NCOLS+3) = 40.; // ET
        *(vthresh+25*NCOLS+3) = 50.; *(athresh+25*NCOLS+3) = 2.7; *(dthresh+25*NCOLS+3) = 40.; // ET
        *(vthresh+26*NCOLS+3) = 30.; *(athresh+26*NCOLS+3) = 1.0; *(dthresh+26*NCOLS+3) = 10.; // 878 - L2 right panel
        *(vthresh+27*NCOLS+3) = 8.; *(athresh+27*NCOLS+3) = 0.4; *(dthresh+27*NCOLS+3) = 10.; // 878 - L0 left panel
        *(vthresh+28*NCOLS+3) = 100.; *(athresh+28*NCOLS+3) = 7.0; *(dthresh+28*NCOLS+3) = 80.; // 878 - L2 slab
        *(vthresh+29*NCOLS+3) = 6.; *(athresh+29*NCOLS+3) = 0.4; *(dthresh+29*NCOLS+3) = 10.; // 878 - L0 right panel
        *(vthresh+30*NCOLS+3) = 30.; *(athresh+30*NCOLS+3) = 1.0; *(dthresh+30*NCOLS+3) = 40.; // 878 - L1 top panel
        *(vthresh+31*NCOLS+3) = 25.; *(athresh+31*NCOLS+3) = 1.5; *(dthresh+31*NCOLS+3) = 10.; // 878 - L2 left panel
    }

    if (RunNum >= 651) { // ET=1150, 878=800, 7725=800, B=3.8T.
        *(vthresh+0*NCOLS+3) = 40.; *(athresh+0*NCOLS+3) = 1.8; *(dthresh+0*NCOLS+3) = 40.; // 878bar
        *(vthresh+1*NCOLS+3) = 60.; *(athresh+1*NCOLS+3) = 3.0; *(dthresh+1*NCOLS+3) = 40.; // 878bar
        *(vthresh+2*NCOLS+3) = 45.; *(athresh+2*NCOLS+3) = 3.5; *(dthresh+2*NCOLS+3) = 40.; // 878bar
        *(vthresh+3*NCOLS+3) = 40.; *(athresh+3*NCOLS+3) = 3.5; *(dthresh+3*NCOLS+3) = 40.; // 878bar
        *(vthresh+4*NCOLS+3) = 40.; *(athresh+4*NCOLS+3) = 3.5; *(dthresh+4*NCOLS+3) = 40.; // 878bar
        *(vthresh+5*NCOLS+3) = 40.; *(athresh+5*NCOLS+3) = 1.; *(dthresh+5*NCOLS+3) = 40.; // 7725
        *(vthresh+6*NCOLS+3) = 30.; *(athresh+6*NCOLS+3) = 2.5; *(dthresh+6*NCOLS+3) = 20.; // 878bar
        *(vthresh+7*NCOLS+3) = 55.; *(athresh+7*NCOLS+3) = 4.0; *(dthresh+7*NCOLS+3) = 40.; // 878bar
        *(vthresh+8*NCOLS+3) = 8.; *(athresh+8*NCOLS+3) = 0.3; *(dthresh+8*NCOLS+3) = 40.; // ET
        *(vthresh+9*NCOLS+3) = 80.; *(athresh+9*NCOLS+3) = 5.0; *(dthresh+9*NCOLS+3) = 40.; // ET
        *(vthresh+10*NCOLS+3) = 10.; *(athresh+10*NCOLS+3) = 0.6; *(dthresh+10*NCOLS+3) = 40.; // 878 - L0 top panel
        *(vthresh+11*NCOLS+3) = 25.; *(athresh+11*NCOLS+3) = 1.5; *(dthresh+11*NCOLS+3) = 10.; // 878 - L1 left panel
        *(vthresh+12*NCOLS+3) = 40.; *(athresh+12*NCOLS+3) = 3.5; *(dthresh+12*NCOLS+3) = 40.; // 878bar
        *(vthresh+13*NCOLS+3) = 45.; *(athresh+13*NCOLS+3) = 3.5; *(dthresh+13*NCOLS+3) = 40.; // 878bar
        *(vthresh+14*NCOLS+3) = 10.; *(athresh+14*NCOLS+3) = 0.4; *(dthresh+14*NCOLS+3) = 20.; // 878 - L2 top panel
        *(vthresh+15*NCOLS+3) = 999.; *(athresh+15*NCOLS+3) = 999; *(dthresh+15*NCOLS+3) = 10.; // LHC clock
        *(vthresh+16*NCOLS+3) = 40.; *(athresh+16*NCOLS+3) = 3.5; *(dthresh+16*NCOLS+3) = 40.; // 878bar
        *(vthresh+17*NCOLS+3) = 60.; *(athresh+17*NCOLS+3) = 3.5;  *(dthresh+17*NCOLS+3) = 40.; // ET
        *(vthresh+18*NCOLS+3) = 200.; *(athresh+18*NCOLS+3) = 20.; *(dthresh+18*NCOLS+3) = 80.; // 878 - L0 slab
        *(vthresh+19*NCOLS+3) = 40.; *(athresh+19*NCOLS+3) = 3.0; *(dthresh+19*NCOLS+3) = 10.; // 878 - L1 right panel
        *(vthresh+20*NCOLS+3) = 200.; *(athresh+20*NCOLS+3) = 18.; *(dthresh+20*NCOLS+3) = 80.; // 878 - L1 slab
        *(vthresh+21*NCOLS+3) = 320.; *(athresh+21*NCOLS+3) = 25.; *(dthresh+21*NCOLS+3) = 80.; // 878 - Back slab
        *(vthresh+22*NCOLS+3) = 40.; *(athresh+22*NCOLS+3) = 1.0; *(dthresh+22*NCOLS+3) = 40.; // 7725
        *(vthresh+23*NCOLS+3) = 500.; *(athresh+23*NCOLS+3) = 70.; *(dthresh+23*NCOLS+3) = 400.; // 878bar
        *(vthresh+24*NCOLS+3) = 80.; *(athresh+24*NCOLS+3) = 3.0; *(dthresh+24*NCOLS+3) = 40.; // ET
        *(vthresh+25*NCOLS+3) = 50.; *(athresh+25*NCOLS+3) = 2.5; *(dthresh+25*NCOLS+3) = 40.; // ET
        *(vthresh+26*NCOLS+3) = 30.; *(athresh+26*NCOLS+3) = 1.0; *(dthresh+26*NCOLS+3) = 10.; // 878 - L2 right panel
        *(vthresh+27*NCOLS+3) = 8.; *(athresh+27*NCOLS+3) = 0.4; *(dthresh+27*NCOLS+3) = 10.; // 878 - L0 left panel
        *(vthresh+28*NCOLS+3) = 100.; *(athresh+28*NCOLS+3) = 7.0; *(dthresh+28*NCOLS+3) = 80.; // 878 - L2 slab
        *(vthresh+29*NCOLS+3) = 6.; *(athresh+29*NCOLS+3) = 0.4; *(dthresh+29*NCOLS+3) = 10.; // 878 - L0 right panel
        *(vthresh+30*NCOLS+3) = 30.; *(athresh+30*NCOLS+3) = 1.0; *(dthresh+30*NCOLS+3) = 40.; // 878 - L1 top panel
        *(vthresh+31*NCOLS+3) = 25.; *(athresh+31*NCOLS+3) = 1.5; *(dthresh+31*NCOLS+3) = 10.; // 878 - L2 left panel
    }

    // Not confirmed
    if (RunNum >= 670 ) { // ET=1200, 878=700, 7725=950, B=3.8T.
        *(vthresh+0*NCOLS+3) = 8.; *(athresh+0*NCOLS+3) = 1.8; *(dthresh+0*NCOLS+3) = 40.; // 878bar
        *(vthresh+1*NCOLS+3) = 10.; *(athresh+1*NCOLS+3) = 3.0; *(dthresh+1*NCOLS+3) = 40.; // 878bar
        *(vthresh+2*NCOLS+3) = 10.; *(athresh+2*NCOLS+3) = 3.5; *(dthresh+2*NCOLS+3) = 40.; // 878bar
        *(vthresh+3*NCOLS+3) = 10.; *(athresh+3*NCOLS+3) = 3.5; *(dthresh+3*NCOLS+3) = 40.; // 878bar
        *(vthresh+4*NCOLS+3) = 10.; *(athresh+4*NCOLS+3) = 3.5; *(dthresh+4*NCOLS+3) = 40.; // 878bar
        *(vthresh+5*NCOLS+3) = 100.; *(athresh+5*NCOLS+3) = 3.5; *(dthresh+5*NCOLS+3) = 40.; // 7725
        *(vthresh+6*NCOLS+3) = 10.; *(athresh+6*NCOLS+3) = 2.5; *(dthresh+6*NCOLS+3) = 20.; // 878bar
        *(vthresh+7*NCOLS+3) = 10.; *(athresh+7*NCOLS+3) = 4.0; *(dthresh+7*NCOLS+3) = 40.; // 878bar
        *(vthresh+8*NCOLS+3) = 15.; *(athresh+8*NCOLS+3) = 0.3; *(dthresh+8*NCOLS+3) = 40.; // ET
        *(vthresh+9*NCOLS+3) = 300.; *(athresh+9*NCOLS+3) = 5.0; *(dthresh+9*NCOLS+3) = 40.; // ET
        *(vthresh+10*NCOLS+3) = 10.; *(athresh+10*NCOLS+3) = 0.6; *(dthresh+10*NCOLS+3) = 40.; // 878 - L0 top panel
        *(vthresh+11*NCOLS+3) = 25.; *(athresh+11*NCOLS+3) = 1.5; *(dthresh+11*NCOLS+3) = 10.; // 878 - L1 left panel
        *(vthresh+12*NCOLS+3) = 10.; *(athresh+12*NCOLS+3) = 3.5; *(dthresh+12*NCOLS+3) = 40.; // 878bar
        *(vthresh+13*NCOLS+3) = 10.; *(athresh+13*NCOLS+3) = 3.5; *(dthresh+13*NCOLS+3) = 40.; // 878bar
        *(vthresh+14*NCOLS+3) = 10.; *(athresh+14*NCOLS+3) = 0.4; *(dthresh+14*NCOLS+3) = 20.; // 878 - L2 top panel
        *(vthresh+15*NCOLS+3) = 999.; *(athresh+15*NCOLS+3) = 999; *(dthresh+15*NCOLS+3) = 10.; // LHC clock
        *(vthresh+16*NCOLS+3) = 20.; *(athresh+16*NCOLS+3) = 3.5; *(dthresh+16*NCOLS+3) = 40.; // 878bar
        *(vthresh+17*NCOLS+3) = 120.; *(athresh+17*NCOLS+3) = 3.5;  *(dthresh+17*NCOLS+3) = 40.; // ET
        *(vthresh+18*NCOLS+3) = 200.; *(athresh+18*NCOLS+3) = 20.; *(dthresh+18*NCOLS+3) = 80.; // 878 - L0 slab
        *(vthresh+19*NCOLS+3) = 40.; *(athresh+19*NCOLS+3) = 3.0; *(dthresh+19*NCOLS+3) = 10.; // 878 - L1 right panel
        *(vthresh+20*NCOLS+3) = 200.; *(athresh+20*NCOLS+3) = 18.; *(dthresh+20*NCOLS+3) = 80.; // 878 - L1 slab
        *(vthresh+21*NCOLS+3) = 320.; *(athresh+21*NCOLS+3) = 25.; *(dthresh+21*NCOLS+3) = 80.; // 878 - Back slab
        *(vthresh+22*NCOLS+3) = 120.; *(athresh+22*NCOLS+3) = 4.0; *(dthresh+22*NCOLS+3) = 40.; // 7725
        *(vthresh+23*NCOLS+3) = 500.; *(athresh+23*NCOLS+3) = 70.; *(dthresh+23*NCOLS+3) = 400.; // 878bar
        *(vthresh+24*NCOLS+3) = 300.; *(athresh+24*NCOLS+3) = 3.0; *(dthresh+24*NCOLS+3) = 40.; // ET
        *(vthresh+25*NCOLS+3) = 150.; *(athresh+25*NCOLS+3) = 2.5; *(dthresh+25*NCOLS+3) = 40.; // ET
        *(vthresh+26*NCOLS+3) = 30.; *(athresh+26*NCOLS+3) = 1.0; *(dthresh+26*NCOLS+3) = 10.; // 878 - L2 right panel
        *(vthresh+27*NCOLS+3) = 8.; *(athresh+27*NCOLS+3) = 0.4; *(dthresh+27*NCOLS+3) = 10.; // 878 - L0 left panel
        *(vthresh+28*NCOLS+3) = 100.; *(athresh+28*NCOLS+3) = 7.0; *(dthresh+28*NCOLS+3) = 80.; // 878 - L2 slab
        *(vthresh+29*NCOLS+3) = 6.; *(athresh+29*NCOLS+3) = 0.4; *(dthresh+29*NCOLS+3) = 10.; // 878 - L0 right panel
        *(vthresh+30*NCOLS+3) = 30.; *(athresh+30*NCOLS+3) = 1.0; *(dthresh+30*NCOLS+3) = 40.; // 878 - L1 top panel
        *(vthresh+31*NCOLS+3) = 25.; *(athresh+31*NCOLS+3) = 1.5; *(dthresh+31*NCOLS+3) = 10.; // 878 - L2 left panel
    }

    if (RunNum >= 725) { // ET=1150, 878=800, 7725=800, B=3.8T.
        *(vthresh+0*NCOLS+3) = 40.; *(athresh+0*NCOLS+3) = 1.8; *(dthresh+0*NCOLS+3) = 40.; // 878bar
        *(vthresh+1*NCOLS+3) = 60.; *(athresh+1*NCOLS+3) = 3.0; *(dthresh+1*NCOLS+3) = 40.; // 878bar
        *(vthresh+2*NCOLS+3) = 45.; *(athresh+2*NCOLS+3) = 3.5; *(dthresh+2*NCOLS+3) = 40.; // 878bar
        *(vthresh+3*NCOLS+3) = 40.; *(athresh+3*NCOLS+3) = 3.5; *(dthresh+3*NCOLS+3) = 40.; // 878bar
        *(vthresh+4*NCOLS+3) = 40.; *(athresh+4*NCOLS+3) = 3.5; *(dthresh+4*NCOLS+3) = 40.; // 878bar
        *(vthresh+5*NCOLS+3) = 40.; *(athresh+5*NCOLS+3) = 1.; *(dthresh+5*NCOLS+3) = 40.; // 7725
        *(vthresh+6*NCOLS+3) = 30.; *(athresh+6*NCOLS+3) = 2.5; *(dthresh+6*NCOLS+3) = 20.; // 878bar
        *(vthresh+7*NCOLS+3) = 55.; *(athresh+7*NCOLS+3) = 4.0; *(dthresh+7*NCOLS+3) = 40.; // 878bar
        *(vthresh+8*NCOLS+3) = 8.; *(athresh+8*NCOLS+3) = 0.3; *(dthresh+8*NCOLS+3) = 40.; // ET
        *(vthresh+9*NCOLS+3) = 80.; *(athresh+9*NCOLS+3) = 5.0; *(dthresh+9*NCOLS+3) = 40.; // ET
        *(vthresh+10*NCOLS+3) = 10.; *(athresh+10*NCOLS+3) = 0.6; *(dthresh+10*NCOLS+3) = 40.; // 878 - L0 top panel
        *(vthresh+11*NCOLS+3) = 25.; *(athresh+11*NCOLS+3) = 1.5; *(dthresh+11*NCOLS+3) = 10.; // 878 - L1 left panel
        *(vthresh+12*NCOLS+3) = 40.; *(athresh+12*NCOLS+3) = 3.5; *(dthresh+12*NCOLS+3) = 40.; // 878bar
        *(vthresh+13*NCOLS+3) = 45.; *(athresh+13*NCOLS+3) = 3.5; *(dthresh+13*NCOLS+3) = 40.; // 878bar
        *(vthresh+14*NCOLS+3) = 10.; *(athresh+14*NCOLS+3) = 0.4; *(dthresh+14*NCOLS+3) = 20.; // 878 - L2 top panel
        *(vthresh+15*NCOLS+3) = 999.; *(athresh+15*NCOLS+3) = 999; *(dthresh+15*NCOLS+3) = 10.; // LHC clock
        *(vthresh+16*NCOLS+3) = 40.; *(athresh+16*NCOLS+3) = 3.5; *(dthresh+16*NCOLS+3) = 40.; // 878bar
        *(vthresh+17*NCOLS+3) = 60.; *(athresh+17*NCOLS+3) = 3.5;  *(dthresh+17*NCOLS+3) = 40.; // ET
        *(vthresh+18*NCOLS+3) = 200.; *(athresh+18*NCOLS+3) = 20.; *(dthresh+18*NCOLS+3) = 80.; // 878 - L0 slab
        *(vthresh+19*NCOLS+3) = 40.; *(athresh+19*NCOLS+3) = 3.0; *(dthresh+19*NCOLS+3) = 10.; // 878 - L1 right panel
        *(vthresh+20*NCOLS+3) = 200.; *(athresh+20*NCOLS+3) = 18.; *(dthresh+20*NCOLS+3) = 80.; // 878 - L1 slab
        *(vthresh+21*NCOLS+3) = 320.; *(athresh+21*NCOLS+3) = 25.; *(dthresh+21*NCOLS+3) = 80.; // 878 - Back slab
        *(vthresh+22*NCOLS+3) = 40.; *(athresh+22*NCOLS+3) = 1.0; *(dthresh+22*NCOLS+3) = 40.; // 7725
        *(vthresh+23*NCOLS+3) = 500.; *(athresh+23*NCOLS+3) = 70.; *(dthresh+23*NCOLS+3) = 400.; // 878bar
        *(vthresh+24*NCOLS+3) = 80.; *(athresh+24*NCOLS+3) = 3.0; *(dthresh+24*NCOLS+3) = 40.; // ET
        *(vthresh+25*NCOLS+3) = 50.; *(athresh+25*NCOLS+3) = 2.5; *(dthresh+25*NCOLS+3) = 40.; // ET
        *(vthresh+26*NCOLS+3) = 30.; *(athresh+26*NCOLS+3) = 1.0; *(dthresh+26*NCOLS+3) = 10.; // 878 - L2 right panel
        *(vthresh+27*NCOLS+3) = 8.; *(athresh+27*NCOLS+3) = 0.4; *(dthresh+27*NCOLS+3) = 10.; // 878 - L0 left panel
        *(vthresh+28*NCOLS+3) = 100.; *(athresh+28*NCOLS+3) = 7.0; *(dthresh+28*NCOLS+3) = 80.; // 878 - L2 slab
        *(vthresh+29*NCOLS+3) = 6.; *(athresh+29*NCOLS+3) = 0.4; *(dthresh+29*NCOLS+3) = 10.; // 878 - L0 right panel
        *(vthresh+30*NCOLS+3) = 30.; *(athresh+30*NCOLS+3) = 1.0; *(dthresh+30*NCOLS+3) = 40.; // 878 - L1 top panel
        *(vthresh+31*NCOLS+3) = 25.; *(athresh+31*NCOLS+3) = 1.5; *(dthresh+31*NCOLS+3) = 10.; // 878 - L2 left panel
    }

    if (RunNum >= 728) { // ET=1300, 878box1=1100V, L3TL_878=1100V, L3BR_7725=1120V, L3ML_7725=1030V, Bars&Slabs=1450V, B=3.8T.
        *(vthresh+0*NCOLS+3) = 270.; *(athresh+0*NCOLS+3) = 18.; *(dthresh+0*NCOLS+3) = 80.; // 878bar
        *(vthresh+1*NCOLS+3) = 250.; *(athresh+1*NCOLS+3) = 27.; *(dthresh+1*NCOLS+3) = 100.; // 878bar
        *(vthresh+2*NCOLS+3) = 320.; *(athresh+2*NCOLS+3) = 28.; *(dthresh+2*NCOLS+3) = 100.; // 878bar
        *(vthresh+3*NCOLS+3) = 350.; *(athresh+3*NCOLS+3) = 30.; *(dthresh+3*NCOLS+3) = 100.; // 878bar
        *(vthresh+4*NCOLS+3) = 260.; *(athresh+4*NCOLS+3) = 28.; *(dthresh+4*NCOLS+3) = 100.; // 878bar
        *(vthresh+5*NCOLS+3) = 700.; *(athresh+5*NCOLS+3) = 28.; *(dthresh+5*NCOLS+3) = 80.; // 7725
        *(vthresh+6*NCOLS+3) = 300.; *(athresh+6*NCOLS+3) = 22.; *(dthresh+6*NCOLS+3) = 100.; // 878bar
        *(vthresh+7*NCOLS+3) = 380.; *(athresh+7*NCOLS+3) = 35.; *(dthresh+7*NCOLS+3) = 100.; // 878bar
        *(vthresh+8*NCOLS+3) = 95.; *(athresh+8*NCOLS+3) = 4.; *(dthresh+8*NCOLS+3) = 50.; // ET
        *(vthresh+9*NCOLS+3) = 850.; *(athresh+9*NCOLS+3) = 40.; *(dthresh+9*NCOLS+3) = 100.; // ET
        *(vthresh+10*NCOLS+3) = 10.; *(athresh+10*NCOLS+3) = 0.6; *(dthresh+10*NCOLS+3) = 40.; // 878 - L0 top panel
        *(vthresh+11*NCOLS+3) = 25.; *(athresh+11*NCOLS+3) = 1.5; *(dthresh+11*NCOLS+3) = 40.; // 878 - L1 left panel
        *(vthresh+12*NCOLS+3) = 320.; *(athresh+12*NCOLS+3) = 26.; *(dthresh+12*NCOLS+3) = 100.; // 878bar
        *(vthresh+13*NCOLS+3) = 300.; *(athresh+13*NCOLS+3) = 30.; *(dthresh+13*NCOLS+3) = 100.; // 878bar
        *(vthresh+14*NCOLS+3) = 10.; *(athresh+14*NCOLS+3) = 0.3; *(dthresh+14*NCOLS+3) = 40.; // 878 - L2 top panel
        *(vthresh+15*NCOLS+3) = 999.; *(athresh+15*NCOLS+3) = 999; *(dthresh+15*NCOLS+3) = 10.; // LHC clock
        *(vthresh+16*NCOLS+3) = 420.; *(athresh+16*NCOLS+3) = 30.; *(dthresh+16*NCOLS+3) = 100.; // 878bar
        *(vthresh+17*NCOLS+3) = 620.; *(athresh+17*NCOLS+3) = 30.;  *(dthresh+17*NCOLS+3) = 100.; // ET
        *(vthresh+18*NCOLS+3) = 250.; *(athresh+18*NCOLS+3) = 20.; *(dthresh+18*NCOLS+3) = 80.; // 878 - L0 slab
        *(vthresh+19*NCOLS+3) = 40.; *(athresh+19*NCOLS+3) = 3.0; *(dthresh+19*NCOLS+3) = 70.; // 878 - L1 right panel
        *(vthresh+20*NCOLS+3) = 250.; *(athresh+20*NCOLS+3) = 18.; *(dthresh+20*NCOLS+3) = 100.; // 878 - L1 slab
        *(vthresh+21*NCOLS+3) = 380.; *(athresh+21*NCOLS+3) = 25.; *(dthresh+21*NCOLS+3) = 100.; // 878 - Back slab
        *(vthresh+22*NCOLS+3) = 500.; *(athresh+22*NCOLS+3) = 14.; *(dthresh+22*NCOLS+3) = 40.; // 7725
        *(vthresh+23*NCOLS+3) = 580.; *(athresh+23*NCOLS+3) = 70.; *(dthresh+23*NCOLS+3) = 200.; // 878bar
        *(vthresh+24*NCOLS+3) = 780.; *(athresh+24*NCOLS+3) = 28.; *(dthresh+24*NCOLS+3) = 100.; // ET
        *(vthresh+25*NCOLS+3) = 500.; *(athresh+25*NCOLS+3) = 22.; *(dthresh+25*NCOLS+3) = 100.; // ET
        *(vthresh+26*NCOLS+3) = 30.; *(athresh+26*NCOLS+3) = 1.0; *(dthresh+26*NCOLS+3) = 60.; // 878 - L2 right panel
        *(vthresh+27*NCOLS+3) = 8.; *(athresh+27*NCOLS+3) = 0.4; *(dthresh+27*NCOLS+3) = 30.; // 878 - L0 left panel
        *(vthresh+28*NCOLS+3) = 90.; *(athresh+28*NCOLS+3) = 7.0; *(dthresh+28*NCOLS+3) = 80.; // 878 - L2 slab
        *(vthresh+29*NCOLS+3) = 6.; *(athresh+29*NCOLS+3) = 0.4; *(dthresh+29*NCOLS+3) = 20.; // 878 - L0 right panel
        *(vthresh+30*NCOLS+3) = 30.; *(athresh+30*NCOLS+3) = 1.0; *(dthresh+30*NCOLS+3) = 50.; // 878 - L1 top panel
        *(vthresh+31*NCOLS+3) = 25.; *(athresh+31*NCOLS+3) = 1.5; *(dthresh+31*NCOLS+3) = 60.; // 878 - L2 left panel
    }

    // Some changes in ET HV but no cosmic runs

    if (RunNum >= 802) { // ET=1150, 878box1=1200V, L3TL_878=1200V, L3BR_7725=1120V, L3ML_7725=1030V, Bars&Slabs=1450V, B=3.8T.
        *(vthresh+0*NCOLS+3) = 370.; *(athresh+0*NCOLS+3) = 20.; *(dthresh+0*NCOLS+3) = 80.; // 878bar
        *(vthresh+1*NCOLS+3) = 300.; *(athresh+1*NCOLS+3) = 30.; *(dthresh+1*NCOLS+3) = 100.; // 878bar
        *(vthresh+2*NCOLS+3) = 320.; *(athresh+2*NCOLS+3) = 30.; *(dthresh+2*NCOLS+3) = 100.; // 878bar
        *(vthresh+3*NCOLS+3) = 350.; *(athresh+3*NCOLS+3) = 30.; *(dthresh+3*NCOLS+3) = 100.; // 878bar
        *(vthresh+4*NCOLS+3) = 260.; *(athresh+4*NCOLS+3) = 28.; *(dthresh+4*NCOLS+3) = 100.; // 878bar
        *(vthresh+5*NCOLS+3) = 700.; *(athresh+5*NCOLS+3) = 28.; *(dthresh+5*NCOLS+3) = 80.; // 7725
        *(vthresh+6*NCOLS+3) = 300.; *(athresh+6*NCOLS+3) = 30.; *(dthresh+6*NCOLS+3) = 100.; // 878bar
        *(vthresh+7*NCOLS+3) = 380.; *(athresh+7*NCOLS+3) = 50.; *(dthresh+7*NCOLS+3) = 100.; // 878bar
        *(vthresh+8*NCOLS+3) = 15.; *(athresh+8*NCOLS+3) = 0.5; *(dthresh+8*NCOLS+3) = 40.; // ET
        *(vthresh+9*NCOLS+3) = 200.; *(athresh+9*NCOLS+3) = 4.; *(dthresh+9*NCOLS+3) = 80.; // ET
        *(vthresh+10*NCOLS+3) = 10.; *(athresh+10*NCOLS+3) = 0.6; *(dthresh+10*NCOLS+3) = 40.; // 878 - L0 top panel
        *(vthresh+11*NCOLS+3) = 25.; *(athresh+11*NCOLS+3) = 1.5; *(dthresh+11*NCOLS+3) = 40.; // 878 - L1 left panel
        *(vthresh+12*NCOLS+3) = 320.; *(athresh+12*NCOLS+3) = 26.; *(dthresh+12*NCOLS+3) = 100.; // 878bar
        *(vthresh+13*NCOLS+3) = 300.; *(athresh+13*NCOLS+3) = 30.; *(dthresh+13*NCOLS+3) = 100.; // 878bar
        *(vthresh+14*NCOLS+3) = 10.; *(athresh+14*NCOLS+3) = 0.3; *(dthresh+14*NCOLS+3) = 40.; // 878 - L2 top panel
        *(vthresh+15*NCOLS+3) = 999.; *(athresh+15*NCOLS+3) = 999; *(dthresh+15*NCOLS+3) = 10.; // LHC clock
        *(vthresh+16*NCOLS+3) = 420.; *(athresh+16*NCOLS+3) = 30.; *(dthresh+16*NCOLS+3) = 100.; // 878bar
        *(vthresh+17*NCOLS+3) = 150.; *(athresh+17*NCOLS+3) = 5.;  *(dthresh+17*NCOLS+3) = 50.; // ET
        *(vthresh+18*NCOLS+3) = 250.; *(athresh+18*NCOLS+3) = 20.; *(dthresh+18*NCOLS+3) = 80.; // 878 - L0 slab
        *(vthresh+19*NCOLS+3) = 40.; *(athresh+19*NCOLS+3) = 3.0; *(dthresh+19*NCOLS+3) = 50.; // 878 - L1 right panel
        *(vthresh+20*NCOLS+3) = 250.; *(athresh+20*NCOLS+3) = 18.; *(dthresh+20*NCOLS+3) = 100.; // 878 - L1 slab
        *(vthresh+21*NCOLS+3) = 380.; *(athresh+21*NCOLS+3) = 25.; *(dthresh+21*NCOLS+3) = 100.; // 878 - Back slab
        *(vthresh+22*NCOLS+3) = 500.; *(athresh+22*NCOLS+3) = 10.; *(dthresh+22*NCOLS+3) = 40.; // 7725
        *(vthresh+23*NCOLS+3) = 580.; *(athresh+23*NCOLS+3) = 50.; *(dthresh+23*NCOLS+3) = 200.; // 878bar
        *(vthresh+24*NCOLS+3) = 200.; *(athresh+24*NCOLS+3) = 5.; *(dthresh+24*NCOLS+3) = 60.; // ET
        *(vthresh+25*NCOLS+3) = 100.; *(athresh+25*NCOLS+3) = 5.; *(dthresh+25*NCOLS+3) = 60.; // ET
        *(vthresh+26*NCOLS+3) = 30.; *(athresh+26*NCOLS+3) = 1.0; *(dthresh+26*NCOLS+3) = 60.; // 878 - L2 right panel
        *(vthresh+27*NCOLS+3) = 8.; *(athresh+27*NCOLS+3) = 0.4; *(dthresh+27*NCOLS+3) = 30.; // 878 - L0 left panel
        *(vthresh+28*NCOLS+3) = 90.; *(athresh+28*NCOLS+3) = 7.0; *(dthresh+28*NCOLS+3) = 80.; // 878 - L2 slab
        *(vthresh+29*NCOLS+3) = 6.; *(athresh+29*NCOLS+3) = 0.4; *(dthresh+29*NCOLS+3) = 20.; // 878 - L0 right panel
        *(vthresh+30*NCOLS+3) = 30.; *(athresh+30*NCOLS+3) = 1.0; *(dthresh+30*NCOLS+3) = 50.; // 878 - L1 top panel
        *(vthresh+31*NCOLS+3) = 25.; *(athresh+31*NCOLS+3) = 1.5; *(dthresh+31*NCOLS+3) = 60.; // 878 - L2 left panel
    }

    if (RunNum >= 804) { // ET=1100, 878box1=1250V, L3TL_878=1250V, L3BR_7725=1120V, L3ML_7725=1030V, Bars&Slabs=1450V, B=3.8T.
        *(vthresh+0*NCOLS+3) = 370.; *(athresh+0*NCOLS+3) = 20.; *(dthresh+0*NCOLS+3) = 80.; // 878bar
        *(vthresh+1*NCOLS+3) = 350.; *(athresh+1*NCOLS+3) = 30.; *(dthresh+1*NCOLS+3) = 100.; // 878bar
        *(vthresh+2*NCOLS+3) = 400.; *(athresh+2*NCOLS+3) = 30.; *(dthresh+2*NCOLS+3) = 100.; // 878bar
        *(vthresh+3*NCOLS+3) = 400.; *(athresh+3*NCOLS+3) = 30.; *(dthresh+3*NCOLS+3) = 100.; // 878bar
        *(vthresh+4*NCOLS+3) = 360.; *(athresh+4*NCOLS+3) = 28.; *(dthresh+4*NCOLS+3) = 100.; // 878bar
        *(vthresh+5*NCOLS+3) = 700.; *(athresh+5*NCOLS+3) = 28.; *(dthresh+5*NCOLS+3) = 80.; // 7725
        *(vthresh+6*NCOLS+3) = 380.; *(athresh+6*NCOLS+3) = 30.; *(dthresh+6*NCOLS+3) = 100.; // 878bar
        *(vthresh+7*NCOLS+3) = 500.; *(athresh+7*NCOLS+3) = 50.; *(dthresh+7*NCOLS+3) = 100.; // 878bar
        *(vthresh+8*NCOLS+3) = 10.; *(athresh+8*NCOLS+3) = 0.8; *(dthresh+8*NCOLS+3) = 40.; // ET
        *(vthresh+9*NCOLS+3) = 140.; *(athresh+9*NCOLS+3) = 6.; *(dthresh+9*NCOLS+3) = 80.; // ET
        *(vthresh+10*NCOLS+3) = 10.; *(athresh+10*NCOLS+3) = 0.6; *(dthresh+10*NCOLS+3) = 40.; // 878 - L0 top panel
        *(vthresh+11*NCOLS+3) = 25.; *(athresh+11*NCOLS+3) = 1.5; *(dthresh+11*NCOLS+3) = 40.; // 878 - L1 left panel
        *(vthresh+12*NCOLS+3) = 320.; *(athresh+12*NCOLS+3) = 26.; *(dthresh+12*NCOLS+3) = 100.; // 878bar
        *(vthresh+13*NCOLS+3) = 300.; *(athresh+13*NCOLS+3) = 30.; *(dthresh+13*NCOLS+3) = 100.; // 878bar
        *(vthresh+14*NCOLS+3) = 10.; *(athresh+14*NCOLS+3) = 0.3; *(dthresh+14*NCOLS+3) = 40.; // 878 - L2 top panel
        *(vthresh+15*NCOLS+3) = 999.; *(athresh+15*NCOLS+3) = 999; *(dthresh+15*NCOLS+3) = 10.; // LHC clock
        *(vthresh+16*NCOLS+3) = 600.; *(athresh+16*NCOLS+3) = 30.; *(dthresh+16*NCOLS+3) = 100.; // 878bar
        *(vthresh+17*NCOLS+3) = 100.; *(athresh+17*NCOLS+3) = 2.;  *(dthresh+17*NCOLS+3) = 50.; // ET
        *(vthresh+18*NCOLS+3) = 250.; *(athresh+18*NCOLS+3) = 20.; *(dthresh+18*NCOLS+3) = 80.; // 878 - L0 slab
        *(vthresh+19*NCOLS+3) = 40.; *(athresh+19*NCOLS+3) = 3.0; *(dthresh+19*NCOLS+3) = 50.; // 878 - L1 right panel
        *(vthresh+20*NCOLS+3) = 250.; *(athresh+20*NCOLS+3) = 18.; *(dthresh+20*NCOLS+3) = 100.; // 878 - L1 slab
        *(vthresh+21*NCOLS+3) = 380.; *(athresh+21*NCOLS+3) = 25.; *(dthresh+21*NCOLS+3) = 100.; // 878 - Back slab
        *(vthresh+22*NCOLS+3) = 500.; *(athresh+22*NCOLS+3) = 10.; *(dthresh+22*NCOLS+3) = 40.; // 7725
        *(vthresh+23*NCOLS+3) = 580.; *(athresh+23*NCOLS+3) = 50.; *(dthresh+23*NCOLS+3) = 200.; // 878bar
        *(vthresh+24*NCOLS+3) = 90.; *(athresh+24*NCOLS+3) = 4.; *(dthresh+24*NCOLS+3) = 60.; // ET
        *(vthresh+25*NCOLS+3) = 80.; *(athresh+25*NCOLS+3) = 4.; *(dthresh+25*NCOLS+3) = 60.; // ET
        *(vthresh+26*NCOLS+3) = 30.; *(athresh+26*NCOLS+3) = 1.0; *(dthresh+26*NCOLS+3) = 60.; // 878 - L2 right panel
        *(vthresh+27*NCOLS+3) = 8.; *(athresh+27*NCOLS+3) = 0.4; *(dthresh+27*NCOLS+3) = 30.; // 878 - L0 left panel
        *(vthresh+28*NCOLS+3) = 90.; *(athresh+28*NCOLS+3) = 7.0; *(dthresh+28*NCOLS+3) = 80.; // 878 - L2 slab
        *(vthresh+29*NCOLS+3) = 6.; *(athresh+29*NCOLS+3) = 0.4; *(dthresh+29*NCOLS+3) = 20.; // 878 - L0 right panel
        *(vthresh+30*NCOLS+3) = 30.; *(athresh+30*NCOLS+3) = 1.0; *(dthresh+30*NCOLS+3) = 50.; // 878 - L1 top panel
        *(vthresh+31*NCOLS+3) = 25.; *(athresh+31*NCOLS+3) = 1.5; *(dthresh+31*NCOLS+3) = 60.; // 878 - L2 left panel
        *(vthresh+0*NCOLS+4) = 370.; *(athresh+0*NCOLS+4) = 20.; *(dthresh+0*NCOLS+4) = 80.; // 878bar
        *(vthresh+1*NCOLS+4) = 350.; *(athresh+1*NCOLS+4) = 30.; *(dthresh+1*NCOLS+4) = 100.; // 878bar
        *(vthresh+2*NCOLS+4) = 400.; *(athresh+2*NCOLS+4) = 30.; *(dthresh+2*NCOLS+4) = 100.; // 878bar
        *(vthresh+3*NCOLS+4) = 400.; *(athresh+3*NCOLS+4) = 30.; *(dthresh+3*NCOLS+4) = 100.; // 878bar
        *(vthresh+4*NCOLS+4) = 360.; *(athresh+4*NCOLS+4) = 28.; *(dthresh+4*NCOLS+4) = 100.; // 878bar
        *(vthresh+5*NCOLS+4) = 700.; *(athresh+5*NCOLS+4) = 28.; *(dthresh+5*NCOLS+4) = 80.; // 7725
        *(vthresh+6*NCOLS+4) = 380.; *(athresh+6*NCOLS+4) = 30.; *(dthresh+6*NCOLS+4) = 100.; // 878bar
        *(vthresh+7*NCOLS+4) = 500.; *(athresh+7*NCOLS+4) = 50.; *(dthresh+7*NCOLS+4) = 100.; // 878bar
        *(vthresh+8*NCOLS+4) = 10.; *(athresh+8*NCOLS+4) = 0.8; *(dthresh+8*NCOLS+4) = 40.; // ET
        *(vthresh+9*NCOLS+4) = 140.; *(athresh+9*NCOLS+4) = 6.; *(dthresh+9*NCOLS+4) = 80.; // ET
        *(vthresh+10*NCOLS+4) = 10.; *(athresh+10*NCOLS+4) = 0.6; *(dthresh+10*NCOLS+4) = 40.; // 878 - L0 top panel
        *(vthresh+11*NCOLS+4) = 25.; *(athresh+11*NCOLS+4) = 1.5; *(dthresh+11*NCOLS+4) = 40.; // 878 - L1 left panel
        *(vthresh+12*NCOLS+4) = 320.; *(athresh+12*NCOLS+4) = 26.; *(dthresh+12*NCOLS+4) = 100.; // 878bar
        *(vthresh+13*NCOLS+4) = 300.; *(athresh+13*NCOLS+4) = 30.; *(dthresh+13*NCOLS+4) = 100.; // 878bar
        *(vthresh+14*NCOLS+4) = 10.; *(athresh+14*NCOLS+4) = 0.3; *(dthresh+14*NCOLS+4) = 40.; // 878 - L2 top panel
        *(vthresh+15*NCOLS+4) = 999.; *(athresh+15*NCOLS+4) = 999; *(dthresh+15*NCOLS+4) = 10.; // LHC clock
        *(vthresh+16*NCOLS+4) = 600.; *(athresh+16*NCOLS+4) = 30.; *(dthresh+16*NCOLS+4) = 100.; // 878bar
        *(vthresh+17*NCOLS+4) = 100.; *(athresh+17*NCOLS+4) = 2.;  *(dthresh+17*NCOLS+4) = 50.; // ET
        *(vthresh+18*NCOLS+4) = 250.; *(athresh+18*NCOLS+4) = 20.; *(dthresh+18*NCOLS+4) = 80.; // 878 - L0 slab
        *(vthresh+19*NCOLS+4) = 40.; *(athresh+19*NCOLS+4) = 3.0; *(dthresh+19*NCOLS+4) = 50.; // 878 - L1 right panel
        *(vthresh+20*NCOLS+4) = 250.; *(athresh+20*NCOLS+4) = 18.; *(dthresh+20*NCOLS+4) = 100.; // 878 - L1 slab
        *(vthresh+21*NCOLS+4) = 380.; *(athresh+21*NCOLS+4) = 25.; *(dthresh+21*NCOLS+4) = 100.; // 878 - Back slab
        *(vthresh+22*NCOLS+4) = 500.; *(athresh+22*NCOLS+4) = 10.; *(dthresh+22*NCOLS+4) = 40.; // 7725
        *(vthresh+23*NCOLS+4) = 580.; *(athresh+23*NCOLS+4) = 50.; *(dthresh+23*NCOLS+4) = 200.; // 878bar
        *(vthresh+24*NCOLS+4) = 90.; *(athresh+24*NCOLS+4) = 4.; *(dthresh+24*NCOLS+4) = 60.; // ET
        *(vthresh+25*NCOLS+4) = 80.; *(athresh+25*NCOLS+4) = 4.; *(dthresh+25*NCOLS+4) = 60.; // ET
        *(vthresh+26*NCOLS+4) = 30.; *(athresh+26*NCOLS+4) = 1.0; *(dthresh+26*NCOLS+4) = 60.; // 878 - L2 right panel
        *(vthresh+27*NCOLS+4) = 8.; *(athresh+27*NCOLS+4) = 0.4; *(dthresh+27*NCOLS+4) = 30.; // 878 - L0 left panel
        *(vthresh+28*NCOLS+4) = 90.; *(athresh+28*NCOLS+4) = 7.0; *(dthresh+28*NCOLS+4) = 80.; // 878 - L2 slab
        *(vthresh+29*NCOLS+4) = 6.; *(athresh+29*NCOLS+4) = 0.4; *(dthresh+29*NCOLS+4) = 20.; // 878 - L0 right panel
        *(vthresh+30*NCOLS+4) = 30.; *(athresh+30*NCOLS+4) = 1.0; *(dthresh+30*NCOLS+4) = 50.; // 878 - L1 top panel
        *(vthresh+31*NCOLS+4) = 25.; *(athresh+31*NCOLS+4) = 1.5; *(dthresh+31*NCOLS+4) = 60.; // 878 - L2 left panel
    }

    if (RunNum >= 805) { // ET=1100, 878box1=1300V, L3TL_878=1300V, L3BR_7725=1120V, L3ML_7725=1030V, Bars&Slabs=1450V, B=3.8T.
        *(vthresh+0*NCOLS+3) = 450.; *(athresh+0*NCOLS+3) = 40.; *(dthresh+0*NCOLS+3) = 80.; // 878bar
        *(vthresh+1*NCOLS+3) = 380.; *(athresh+1*NCOLS+3) = 40.; *(dthresh+1*NCOLS+3) = 100.; // 878bar
        *(vthresh+2*NCOLS+3) = 500.; *(athresh+2*NCOLS+3) = 50.; *(dthresh+2*NCOLS+3) = 100.; // 878bar
        *(vthresh+3*NCOLS+3) = 520.; *(athresh+3*NCOLS+3) = 50.; *(dthresh+3*NCOLS+3) = 100.; // 878bar
        *(vthresh+4*NCOLS+3) = 400.; *(athresh+4*NCOLS+3) = 45.; *(dthresh+4*NCOLS+3) = 100.; // 878bar
        *(vthresh+5*NCOLS+3) = 700.; *(athresh+5*NCOLS+3) = 28.; *(dthresh+5*NCOLS+3) = 80.; // 7725
        *(vthresh+6*NCOLS+3) = 450.; *(athresh+6*NCOLS+3) = 45.; *(dthresh+6*NCOLS+3) = 100.; // 878bar
        *(vthresh+7*NCOLS+3) = 580.; *(athresh+7*NCOLS+3) = 65.; *(dthresh+7*NCOLS+3) = 100.; // 878bar
        *(vthresh+8*NCOLS+3) = 10.; *(athresh+8*NCOLS+3) = 0.8; *(dthresh+8*NCOLS+3) = 40.; // ET
        *(vthresh+9*NCOLS+3) = 140.; *(athresh+9*NCOLS+3) = 6.; *(dthresh+9*NCOLS+3) = 80.; // ET
        *(vthresh+10*NCOLS+3) = 10.; *(athresh+10*NCOLS+3) = 0.6; *(dthresh+10*NCOLS+3) = 40.; // 878 - L0 top panel
        *(vthresh+11*NCOLS+3) = 25.; *(athresh+11*NCOLS+3) = 1.5; *(dthresh+11*NCOLS+3) = 40.; // 878 - L1 left panel
        *(vthresh+12*NCOLS+3) = 550.; *(athresh+12*NCOLS+3) = 55.; *(dthresh+12*NCOLS+3) = 100.; // 878bar
        *(vthresh+13*NCOLS+3) = 480.; *(athresh+13*NCOLS+3) = 55.; *(dthresh+13*NCOLS+3) = 100.; // 878bar
        *(vthresh+14*NCOLS+3) = 10.; *(athresh+14*NCOLS+3) = 0.3; *(dthresh+14*NCOLS+3) = 40.; // 878 - L2 top panel
        *(vthresh+15*NCOLS+3) = 999.; *(athresh+15*NCOLS+3) = 999; *(dthresh+15*NCOLS+3) = 10.; // LHC clock
        *(vthresh+16*NCOLS+3) = 650.; *(athresh+16*NCOLS+3) = 60.; *(dthresh+16*NCOLS+3) = 100.; // 878bar
        *(vthresh+17*NCOLS+3) = 100.; *(athresh+17*NCOLS+3) = 2.;  *(dthresh+17*NCOLS+3) = 50.; // ET
        *(vthresh+18*NCOLS+3) = 250.; *(athresh+18*NCOLS+3) = 20.; *(dthresh+18*NCOLS+3) = 80.; // 878 - L0 slab
        *(vthresh+19*NCOLS+3) = 40.; *(athresh+19*NCOLS+3) = 3.0; *(dthresh+19*NCOLS+3) = 50.; // 878 - L1 right panel
        *(vthresh+20*NCOLS+3) = 250.; *(athresh+20*NCOLS+3) = 18.; *(dthresh+20*NCOLS+3) = 100.; // 878 - L1 slab
        *(vthresh+21*NCOLS+3) = 380.; *(athresh+21*NCOLS+3) = 25.; *(dthresh+21*NCOLS+3) = 100.; // 878 - Back slab
        *(vthresh+22*NCOLS+3) = 500.; *(athresh+22*NCOLS+3) = 10.; *(dthresh+22*NCOLS+3) = 40.; // 7725
        *(vthresh+23*NCOLS+3) = 580.; *(athresh+23*NCOLS+3) = 60.; *(dthresh+23*NCOLS+3) = 200.; // 878bar
        *(vthresh+24*NCOLS+3) = 90.; *(athresh+24*NCOLS+3) = 4.; *(dthresh+24*NCOLS+3) = 60.; // ET
        *(vthresh+25*NCOLS+3) = 80.; *(athresh+25*NCOLS+3) = 4.; *(dthresh+25*NCOLS+3) = 60.; // ET
        *(vthresh+26*NCOLS+3) = 30.; *(athresh+26*NCOLS+3) = 1.0; *(dthresh+26*NCOLS+3) = 60.; // 878 - L2 right panel
        *(vthresh+27*NCOLS+3) = 8.; *(athresh+27*NCOLS+3) = 0.4; *(dthresh+27*NCOLS+3) = 30.; // 878 - L0 left panel
        *(vthresh+28*NCOLS+3) = 90.; *(athresh+28*NCOLS+3) = 7.0; *(dthresh+28*NCOLS+3) = 80.; // 878 - L2 slab
        *(vthresh+29*NCOLS+3) = 6.; *(athresh+29*NCOLS+3) = 0.4; *(dthresh+29*NCOLS+3) = 20.; // 878 - L0 right panel
        *(vthresh+30*NCOLS+3) = 30.; *(athresh+30*NCOLS+3) = 1.0; *(dthresh+30*NCOLS+3) = 50.; // 878 - L1 top panel
        *(vthresh+31*NCOLS+3) = 25.; *(athresh+31*NCOLS+3) = 1.5; *(dthresh+31*NCOLS+3) = 60.; // 878 - L2 left panel
        *(vthresh+0*NCOLS+4) = 450.; *(athresh+0*NCOLS+4) = 40.; *(dthresh+0*NCOLS+4) = 80.; // 878bar
        *(vthresh+1*NCOLS+4) = 380.; *(athresh+1*NCOLS+4) = 40.; *(dthresh+1*NCOLS+4) = 100.; // 878bar
        *(vthresh+2*NCOLS+4) = 500.; *(athresh+2*NCOLS+4) = 50.; *(dthresh+2*NCOLS+4) = 100.; // 878bar
        *(vthresh+3*NCOLS+4) = 520.; *(athresh+3*NCOLS+4) = 50.; *(dthresh+3*NCOLS+4) = 100.; // 878bar
        *(vthresh+4*NCOLS+4) = 400.; *(athresh+4*NCOLS+4) = 28.; *(dthresh+4*NCOLS+4) = 100.; // 878bar
        *(vthresh+5*NCOLS+4) = 700.; *(athresh+5*NCOLS+4) = 28.; *(dthresh+5*NCOLS+4) = 80.; // 7725
        *(vthresh+6*NCOLS+4) = 450.; *(athresh+6*NCOLS+4) = 45.; *(dthresh+6*NCOLS+4) = 100.; // 878bar
        *(vthresh+7*NCOLS+4) = 580.; *(athresh+7*NCOLS+4) = 65.; *(dthresh+7*NCOLS+4) = 100.; // 878bar
        *(vthresh+8*NCOLS+4) = 10.; *(athresh+8*NCOLS+4) = 0.8; *(dthresh+8*NCOLS+4) = 40.; // ET
        *(vthresh+9*NCOLS+4) = 140.; *(athresh+9*NCOLS+4) = 6.; *(dthresh+9*NCOLS+4) = 80.; // ET
        *(vthresh+10*NCOLS+4) = 10.; *(athresh+10*NCOLS+4) = 0.6; *(dthresh+10*NCOLS+4) = 40.; // 878 - L0 top panel
        *(vthresh+11*NCOLS+4) = 25.; *(athresh+11*NCOLS+4) = 1.5; *(dthresh+11*NCOLS+4) = 40.; // 878 - L1 left panel
        *(vthresh+12*NCOLS+4) = 550.; *(athresh+12*NCOLS+4) = 55.; *(dthresh+12*NCOLS+4) = 100.; // 878bar
        *(vthresh+13*NCOLS+4) = 480.; *(athresh+13*NCOLS+4) = 55.; *(dthresh+13*NCOLS+4) = 100.; // 878bar
        *(vthresh+14*NCOLS+4) = 10.; *(athresh+14*NCOLS+4) = 0.3; *(dthresh+14*NCOLS+4) = 40.; // 878 - L2 top panel
        *(vthresh+15*NCOLS+4) = 999.; *(athresh+15*NCOLS+4) = 999; *(dthresh+15*NCOLS+4) = 10.; // LHC clock
        *(vthresh+16*NCOLS+4) = 650.; *(athresh+16*NCOLS+4) = 60.; *(dthresh+16*NCOLS+4) = 100.; // 878bar
        *(vthresh+17*NCOLS+4) = 100.; *(athresh+17*NCOLS+4) = 2.;  *(dthresh+17*NCOLS+4) = 50.; // ET
        *(vthresh+18*NCOLS+4) = 250.; *(athresh+18*NCOLS+4) = 20.; *(dthresh+18*NCOLS+4) = 80.; // 878 - L0 slab
        *(vthresh+19*NCOLS+4) = 40.; *(athresh+19*NCOLS+4) = 3.0; *(dthresh+19*NCOLS+4) = 50.; // 878 - L1 right panel
        *(vthresh+20*NCOLS+4) = 250.; *(athresh+20*NCOLS+4) = 18.; *(dthresh+20*NCOLS+4) = 100.; // 878 - L1 slab
        *(vthresh+21*NCOLS+4) = 380.; *(athresh+21*NCOLS+4) = 25.; *(dthresh+21*NCOLS+4) = 100.; // 878 - Back slab
        *(vthresh+22*NCOLS+4) = 500.; *(athresh+22*NCOLS+4) = 10.; *(dthresh+22*NCOLS+4) = 40.; // 7725
        *(vthresh+23*NCOLS+4) = 580.; *(athresh+23*NCOLS+4) = 60.; *(dthresh+23*NCOLS+4) = 200.; // 878bar
        *(vthresh+24*NCOLS+4) = 90.; *(athresh+24*NCOLS+4) = 4.; *(dthresh+24*NCOLS+4) = 60.; // ET
        *(vthresh+25*NCOLS+4) = 80.; *(athresh+25*NCOLS+4) = 4.; *(dthresh+25*NCOLS+4) = 60.; // ET
        *(vthresh+26*NCOLS+4) = 30.; *(athresh+26*NCOLS+4) = 1.0; *(dthresh+26*NCOLS+4) = 60.; // 878 - L2 right panel
        *(vthresh+27*NCOLS+4) = 8.; *(athresh+27*NCOLS+4) = 0.4; *(dthresh+27*NCOLS+4) = 30.; // 878 - L0 left panel
        *(vthresh+28*NCOLS+4) = 90.; *(athresh+28*NCOLS+4) = 7.0; *(dthresh+28*NCOLS+4) = 80.; // 878 - L2 slab
        *(vthresh+29*NCOLS+4) = 6.; *(athresh+29*NCOLS+4) = 0.4; *(dthresh+29*NCOLS+4) = 20.; // 878 - L0 right panel
        *(vthresh+30*NCOLS+4) = 30.; *(athresh+30*NCOLS+4) = 1.0; *(dthresh+30*NCOLS+4) = 50.; // 878 - L1 top panel
        *(vthresh+31*NCOLS+4) = 25.; *(athresh+31*NCOLS+4) = 1.5; *(dthresh+31*NCOLS+4) = 60.; // 878 - L2 left panel
    }

    if (RunNum >= 806) { // ET=1100, 878box1=1350V, L3TL_878=1350V, L3BR_7725=1120V, L3ML_7725=1030V, Bars&Slabs=1450V, B=3.8T.
        *(vthresh+0*NCOLS+3) = 470.; *(athresh+0*NCOLS+3) = 40.; *(dthresh+0*NCOLS+3) = 80.; // 878bar
        *(vthresh+1*NCOLS+3) = 400.; *(athresh+1*NCOLS+3) = 40.; *(dthresh+1*NCOLS+3) = 100.; // 878bar
        *(vthresh+2*NCOLS+3) = 550.; *(athresh+2*NCOLS+3) = 50.; *(dthresh+2*NCOLS+3) = 100.; // 878bar
        *(vthresh+3*NCOLS+3) = 580.; *(athresh+3*NCOLS+3) = 50.; *(dthresh+3*NCOLS+3) = 100.; // 878bar
        *(vthresh+4*NCOLS+3) = 450.; *(athresh+4*NCOLS+3) = 45.; *(dthresh+4*NCOLS+3) = 100.; // 878bar
        *(vthresh+5*NCOLS+3) = 700.; *(athresh+5*NCOLS+3) = 28.; *(dthresh+5*NCOLS+3) = 80.; // 7725
        *(vthresh+6*NCOLS+3) = 500.; *(athresh+6*NCOLS+3) = 45.; *(dthresh+6*NCOLS+3) = 100.; // 878bar
        *(vthresh+7*NCOLS+3) = 620.; *(athresh+7*NCOLS+3) = 65.; *(dthresh+7*NCOLS+3) = 100.; // 878bar
        *(vthresh+8*NCOLS+3) = 10.; *(athresh+8*NCOLS+3) = 0.8; *(dthresh+8*NCOLS+3) = 40.; // ET
        *(vthresh+9*NCOLS+3) = 140.; *(athresh+9*NCOLS+3) = 6.; *(dthresh+9*NCOLS+3) = 80.; // ET
        *(vthresh+10*NCOLS+3) = 10.; *(athresh+10*NCOLS+3) = 0.6; *(dthresh+10*NCOLS+3) = 40.; // 878 - L0 top panel
        *(vthresh+11*NCOLS+3) = 25.; *(athresh+11*NCOLS+3) = 1.5; *(dthresh+11*NCOLS+3) = 40.; // 878 - L1 left panel
        *(vthresh+12*NCOLS+3) = 600.; *(athresh+12*NCOLS+3) = 55.; *(dthresh+12*NCOLS+3) = 100.; // 878bar
        *(vthresh+13*NCOLS+3) = 550.; *(athresh+13*NCOLS+3) = 55.; *(dthresh+13*NCOLS+3) = 100.; // 878bar
        *(vthresh+14*NCOLS+3) = 10.; *(athresh+14*NCOLS+3) = 0.3; *(dthresh+14*NCOLS+3) = 40.; // 878 - L2 top panel
        *(vthresh+15*NCOLS+3) = 999.; *(athresh+15*NCOLS+3) = 999; *(dthresh+15*NCOLS+3) = 10.; // LHC clock
        *(vthresh+16*NCOLS+3) = 720.; *(athresh+16*NCOLS+3) = 60.; *(dthresh+16*NCOLS+3) = 100.; // 878bar
        *(vthresh+17*NCOLS+3) = 100.; *(athresh+17*NCOLS+3) = 2.;  *(dthresh+17*NCOLS+3) = 50.; // ET
        *(vthresh+18*NCOLS+3) = 250.; *(athresh+18*NCOLS+3) = 20.; *(dthresh+18*NCOLS+3) = 80.; // 878 - L0 slab
        *(vthresh+19*NCOLS+3) = 40.; *(athresh+19*NCOLS+3) = 3.0; *(dthresh+19*NCOLS+3) = 50.; // 878 - L1 right panel
        *(vthresh+20*NCOLS+3) = 250.; *(athresh+20*NCOLS+3) = 18.; *(dthresh+20*NCOLS+3) = 100.; // 878 - L1 slab
        *(vthresh+21*NCOLS+3) = 380.; *(athresh+21*NCOLS+3) = 25.; *(dthresh+21*NCOLS+3) = 100.; // 878 - Back slab
        *(vthresh+22*NCOLS+3) = 500.; *(athresh+22*NCOLS+3) = 10.; *(dthresh+22*NCOLS+3) = 40.; // 7725
        *(vthresh+23*NCOLS+3) = 580.; *(athresh+23*NCOLS+3) = 60.; *(dthresh+23*NCOLS+3) = 200.; // 878bar
        *(vthresh+24*NCOLS+3) = 90.; *(athresh+24*NCOLS+3) = 4.; *(dthresh+24*NCOLS+3) = 60.; // ET
        *(vthresh+25*NCOLS+3) = 80.; *(athresh+25*NCOLS+3) = 4.; *(dthresh+25*NCOLS+3) = 60.; // ET
        *(vthresh+26*NCOLS+3) = 30.; *(athresh+26*NCOLS+3) = 1.0; *(dthresh+26*NCOLS+3) = 60.; // 878 - L2 right panel
        *(vthresh+27*NCOLS+3) = 8.; *(athresh+27*NCOLS+3) = 0.4; *(dthresh+27*NCOLS+3) = 30.; // 878 - L0 left panel
        *(vthresh+28*NCOLS+3) = 90.; *(athresh+28*NCOLS+3) = 7.0; *(dthresh+28*NCOLS+3) = 80.; // 878 - L2 slab
        *(vthresh+29*NCOLS+3) = 6.; *(athresh+29*NCOLS+3) = 0.4; *(dthresh+29*NCOLS+3) = 20.; // 878 - L0 right panel
        *(vthresh+30*NCOLS+3) = 30.; *(athresh+30*NCOLS+3) = 1.0; *(dthresh+30*NCOLS+3) = 50.; // 878 - L1 top panel
        *(vthresh+31*NCOLS+3) = 25.; *(athresh+31*NCOLS+3) = 1.5; *(dthresh+31*NCOLS+3) = 60.; // 878 - L2 left panel
        *(vthresh+0*NCOLS+4) = 470.; *(athresh+0*NCOLS+4) = 40.; *(dthresh+0*NCOLS+4) = 80.; // 878bar
        *(vthresh+1*NCOLS+4) = 400.; *(athresh+1*NCOLS+4) = 40.; *(dthresh+1*NCOLS+4) = 100.; // 878bar
        *(vthresh+2*NCOLS+4) = 550.; *(athresh+2*NCOLS+4) = 50.; *(dthresh+2*NCOLS+4) = 100.; // 878bar
        *(vthresh+3*NCOLS+4) = 580.; *(athresh+3*NCOLS+4) = 50.; *(dthresh+3*NCOLS+4) = 100.; // 878bar
        *(vthresh+4*NCOLS+4) = 450.; *(athresh+4*NCOLS+4) = 28.; *(dthresh+4*NCOLS+4) = 100.; // 878bar
        *(vthresh+5*NCOLS+4) = 700.; *(athresh+5*NCOLS+4) = 28.; *(dthresh+5*NCOLS+4) = 80.; // 7725
        *(vthresh+6*NCOLS+4) = 500.; *(athresh+6*NCOLS+4) = 45.; *(dthresh+6*NCOLS+4) = 100.; // 878bar
        *(vthresh+7*NCOLS+4) = 620.; *(athresh+7*NCOLS+4) = 65.; *(dthresh+7*NCOLS+4) = 100.; // 878bar
        *(vthresh+8*NCOLS+4) = 10.; *(athresh+8*NCOLS+4) = 0.8; *(dthresh+8*NCOLS+4) = 40.; // ET
        *(vthresh+9*NCOLS+4) = 140.; *(athresh+9*NCOLS+4) = 6.; *(dthresh+9*NCOLS+4) = 80.; // ET
        *(vthresh+10*NCOLS+4) = 10.; *(athresh+10*NCOLS+4) = 0.6; *(dthresh+10*NCOLS+4) = 40.; // 878 - L0 top panel
        *(vthresh+11*NCOLS+4) = 25.; *(athresh+11*NCOLS+4) = 1.5; *(dthresh+11*NCOLS+4) = 40.; // 878 - L1 left panel
        *(vthresh+12*NCOLS+4) = 600.; *(athresh+12*NCOLS+4) = 55.; *(dthresh+12*NCOLS+4) = 100.; // 878bar
        *(vthresh+13*NCOLS+4) = 550.; *(athresh+13*NCOLS+4) = 55.; *(dthresh+13*NCOLS+4) = 100.; // 878bar
        *(vthresh+14*NCOLS+4) = 10.; *(athresh+14*NCOLS+4) = 0.3; *(dthresh+14*NCOLS+4) = 40.; // 878 - L2 top panel
        *(vthresh+15*NCOLS+4) = 999.; *(athresh+15*NCOLS+4) = 999; *(dthresh+15*NCOLS+4) = 10.; // LHC clock
        *(vthresh+16*NCOLS+4) = 720.; *(athresh+16*NCOLS+4) = 60.; *(dthresh+16*NCOLS+4) = 100.; // 878bar
        *(vthresh+17*NCOLS+4) = 100.; *(athresh+17*NCOLS+4) = 2.;  *(dthresh+17*NCOLS+4) = 50.; // ET
        *(vthresh+18*NCOLS+4) = 250.; *(athresh+18*NCOLS+4) = 20.; *(dthresh+18*NCOLS+4) = 80.; // 878 - L0 slab
        *(vthresh+19*NCOLS+4) = 40.; *(athresh+19*NCOLS+4) = 3.0; *(dthresh+19*NCOLS+4) = 50.; // 878 - L1 right panel
        *(vthresh+20*NCOLS+4) = 250.; *(athresh+20*NCOLS+4) = 18.; *(dthresh+20*NCOLS+4) = 100.; // 878 - L1 slab
        *(vthresh+21*NCOLS+4) = 380.; *(athresh+21*NCOLS+4) = 25.; *(dthresh+21*NCOLS+4) = 100.; // 878 - Back slab
        *(vthresh+22*NCOLS+4) = 500.; *(athresh+22*NCOLS+4) = 10.; *(dthresh+22*NCOLS+4) = 40.; // 7725
        *(vthresh+23*NCOLS+4) = 580.; *(athresh+23*NCOLS+4) = 60.; *(dthresh+23*NCOLS+4) = 200.; // 878bar
        *(vthresh+24*NCOLS+4) = 90.; *(athresh+24*NCOLS+4) = 4.; *(dthresh+24*NCOLS+4) = 60.; // ET
        *(vthresh+25*NCOLS+4) = 80.; *(athresh+25*NCOLS+4) = 4.; *(dthresh+25*NCOLS+4) = 60.; // ET
        *(vthresh+26*NCOLS+4) = 30.; *(athresh+26*NCOLS+4) = 1.0; *(dthresh+26*NCOLS+4) = 60.; // 878 - L2 right panel
        *(vthresh+27*NCOLS+4) = 8.; *(athresh+27*NCOLS+4) = 0.4; *(dthresh+27*NCOLS+4) = 30.; // 878 - L0 left panel
        *(vthresh+28*NCOLS+4) = 90.; *(athresh+28*NCOLS+4) = 7.0; *(dthresh+28*NCOLS+4) = 80.; // 878 - L2 slab
        *(vthresh+29*NCOLS+4) = 6.; *(athresh+29*NCOLS+4) = 0.4; *(dthresh+29*NCOLS+4) = 20.; // 878 - L0 right panel
        *(vthresh+30*NCOLS+4) = 30.; *(athresh+30*NCOLS+4) = 1.0; *(dthresh+30*NCOLS+4) = 50.; // 878 - L1 top panel
        *(vthresh+31*NCOLS+4) = 25.; *(athresh+31*NCOLS+4) = 1.5; *(dthresh+31*NCOLS+4) = 60.; // 878 - L2 left panel
    }

    if (RunNum >= 815) { // ET=1100, 878box1=1400V, L3TL_878=1400V, L3BR_7725=1120V, L3ML_7725=1030V, Bars&Slabs=1450V, B=3.8T.
        *(vthresh+0*NCOLS+3) = 520.; *(athresh+0*NCOLS+3) = 50.; *(dthresh+0*NCOLS+3) = 80.; // 878bar
        *(vthresh+1*NCOLS+3) = 450.; *(athresh+1*NCOLS+3) = 60.; *(dthresh+1*NCOLS+3) = 100.; // 878bar
        *(vthresh+2*NCOLS+3) = 600.; *(athresh+2*NCOLS+3) = 60.; *(dthresh+2*NCOLS+3) = 100.; // 878bar
        *(vthresh+3*NCOLS+3) = 620.; *(athresh+3*NCOLS+3) = 70.; *(dthresh+3*NCOLS+3) = 100.; // 878bar
        *(vthresh+4*NCOLS+3) = 500.; *(athresh+4*NCOLS+3) = 60.; *(dthresh+4*NCOLS+3) = 100.; // 878bar
        *(vthresh+5*NCOLS+3) = 700.; *(athresh+5*NCOLS+3) = 28.; *(dthresh+5*NCOLS+3) = 80.; // 7725
        *(vthresh+6*NCOLS+3) = 550.; *(athresh+6*NCOLS+3) = 60.; *(dthresh+6*NCOLS+3) = 100.; // 878bar
        *(vthresh+7*NCOLS+3) = 680.; *(athresh+7*NCOLS+3) = 80.; *(dthresh+7*NCOLS+3) = 100.; // 878bar
        *(vthresh+8*NCOLS+3) = 10.; *(athresh+8*NCOLS+3) = 0.8; *(dthresh+8*NCOLS+3) = 40.; // ET
        *(vthresh+9*NCOLS+3) = 140.; *(athresh+9*NCOLS+3) = 6.; *(dthresh+9*NCOLS+3) = 80.; // ET
        *(vthresh+10*NCOLS+3) = 10.; *(athresh+10*NCOLS+3) = 0.6; *(dthresh+10*NCOLS+3) = 40.; // 878 - L0 top panel
        *(vthresh+11*NCOLS+3) = 25.; *(athresh+11*NCOLS+3) = 1.5; *(dthresh+11*NCOLS+3) = 40.; // 878 - L1 left panel
        *(vthresh+12*NCOLS+3) = 650.; *(athresh+12*NCOLS+3) = 70.; *(dthresh+12*NCOLS+3) = 100.; // 878bar
        *(vthresh+13*NCOLS+3) = 580.; *(athresh+13*NCOLS+3) = 70.; *(dthresh+13*NCOLS+3) = 100.; // 878bar
        *(vthresh+14*NCOLS+3) = 10.; *(athresh+14*NCOLS+3) = 0.3; *(dthresh+14*NCOLS+3) = 40.; // 878 - L2 top panel
        *(vthresh+15*NCOLS+3) = 999.; *(athresh+15*NCOLS+3) = 999; *(dthresh+15*NCOLS+3) = 10.; // LHC clock
        *(vthresh+16*NCOLS+3) = 800.; *(athresh+16*NCOLS+3) = 80.; *(dthresh+16*NCOLS+3) = 100.; // 878bar
        *(vthresh+17*NCOLS+3) = 100.; *(athresh+17*NCOLS+3) = 2.;  *(dthresh+17*NCOLS+3) = 50.; // ET
        *(vthresh+18*NCOLS+3) = 250.; *(athresh+18*NCOLS+3) = 20.; *(dthresh+18*NCOLS+3) = 80.; // 878 - L0 slab
        *(vthresh+19*NCOLS+3) = 40.; *(athresh+19*NCOLS+3) = 3.0; *(dthresh+19*NCOLS+3) = 50.; // 878 - L1 right panel
        *(vthresh+20*NCOLS+3) = 250.; *(athresh+20*NCOLS+3) = 18.; *(dthresh+20*NCOLS+3) = 100.; // 878 - L1 slab
        *(vthresh+21*NCOLS+3) = 380.; *(athresh+21*NCOLS+3) = 25.; *(dthresh+21*NCOLS+3) = 100.; // 878 - Back slab
        *(vthresh+22*NCOLS+3) = 500.; *(athresh+22*NCOLS+3) = 10.; *(dthresh+22*NCOLS+3) = 40.; // 7725
        *(vthresh+23*NCOLS+3) = 580.; *(athresh+23*NCOLS+3) = 60.; *(dthresh+23*NCOLS+3) = 200.; // 878bar
        *(vthresh+24*NCOLS+3) = 90.; *(athresh+24*NCOLS+3) = 4.; *(dthresh+24*NCOLS+3) = 60.; // ET
        *(vthresh+25*NCOLS+3) = 80.; *(athresh+25*NCOLS+3) = 4.; *(dthresh+25*NCOLS+3) = 60.; // ET
        *(vthresh+26*NCOLS+3) = 30.; *(athresh+26*NCOLS+3) = 1.0; *(dthresh+26*NCOLS+3) = 60.; // 878 - L2 right panel
        *(vthresh+27*NCOLS+3) = 8.; *(athresh+27*NCOLS+3) = 0.4; *(dthresh+27*NCOLS+3) = 30.; // 878 - L0 left panel
        *(vthresh+28*NCOLS+3) = 90.; *(athresh+28*NCOLS+3) = 7.0; *(dthresh+28*NCOLS+3) = 80.; // 878 - L2 slab
        *(vthresh+29*NCOLS+3) = 6.; *(athresh+29*NCOLS+3) = 0.4; *(dthresh+29*NCOLS+3) = 20.; // 878 - L0 right panel
        *(vthresh+30*NCOLS+3) = 30.; *(athresh+30*NCOLS+3) = 1.0; *(dthresh+30*NCOLS+3) = 50.; // 878 - L1 top panel
        *(vthresh+31*NCOLS+3) = 25.; *(athresh+31*NCOLS+3) = 1.5; *(dthresh+31*NCOLS+3) = 60.; // 878 - L2 left panel
        *(vthresh+0*NCOLS+4) = 520.; *(athresh+0*NCOLS+4) = 50.; *(dthresh+0*NCOLS+4) = 80.; // 878bar
        *(vthresh+1*NCOLS+4) = 450.; *(athresh+1*NCOLS+4) = 60.; *(dthresh+1*NCOLS+4) = 100.; // 878bar
        *(vthresh+2*NCOLS+4) = 600.; *(athresh+2*NCOLS+4) = 60.; *(dthresh+2*NCOLS+4) = 100.; // 878bar
        *(vthresh+3*NCOLS+4) = 620.; *(athresh+3*NCOLS+4) = 70.; *(dthresh+3*NCOLS+4) = 100.; // 878bar
        *(vthresh+4*NCOLS+4) = 500.; *(athresh+4*NCOLS+4) = 60.; *(dthresh+4*NCOLS+4) = 100.; // 878bar
        *(vthresh+5*NCOLS+4) = 700.; *(athresh+5*NCOLS+4) = 28.; *(dthresh+5*NCOLS+4) = 80.; // 7725
        *(vthresh+6*NCOLS+4) = 550.; *(athresh+6*NCOLS+4) = 60.; *(dthresh+6*NCOLS+4) = 100.; // 878bar
        *(vthresh+7*NCOLS+4) = 680.; *(athresh+7*NCOLS+4) = 80.; *(dthresh+7*NCOLS+4) = 100.; // 878bar
        *(vthresh+8*NCOLS+4) = 10.; *(athresh+8*NCOLS+4) = 0.8; *(dthresh+8*NCOLS+4) = 40.; // ET
        *(vthresh+9*NCOLS+4) = 140.; *(athresh+9*NCOLS+4) = 6.; *(dthresh+9*NCOLS+4) = 80.; // ET
        *(vthresh+10*NCOLS+4) = 10.; *(athresh+10*NCOLS+4) = 0.6; *(dthresh+10*NCOLS+4) = 40.; // 878 - L0 top panel
        *(vthresh+11*NCOLS+4) = 25.; *(athresh+11*NCOLS+4) = 1.5; *(dthresh+11*NCOLS+4) = 40.; // 878 - L1 left panel
        *(vthresh+12*NCOLS+4) = 650.; *(athresh+12*NCOLS+4) = 70.; *(dthresh+12*NCOLS+4) = 100.; // 878bar
        *(vthresh+13*NCOLS+4) = 580.; *(athresh+13*NCOLS+4) = 70.; *(dthresh+13*NCOLS+4) = 100.; // 878bar
        *(vthresh+14*NCOLS+4) = 10.; *(athresh+14*NCOLS+4) = 0.3; *(dthresh+14*NCOLS+4) = 40.; // 878 - L2 top panel
        *(vthresh+15*NCOLS+4) = 999.; *(athresh+15*NCOLS+4) = 999; *(dthresh+15*NCOLS+4) = 10.; // LHC clock
        *(vthresh+16*NCOLS+4) = 800.; *(athresh+16*NCOLS+4) = 80.; *(dthresh+16*NCOLS+4) = 100.; // 878bar
        *(vthresh+17*NCOLS+4) = 100.; *(athresh+17*NCOLS+4) = 2.;  *(dthresh+17*NCOLS+4) = 50.; // ET
        *(vthresh+18*NCOLS+4) = 250.; *(athresh+18*NCOLS+4) = 20.; *(dthresh+18*NCOLS+4) = 80.; // 878 - L0 slab
        *(vthresh+19*NCOLS+4) = 40.; *(athresh+19*NCOLS+4) = 3.0; *(dthresh+19*NCOLS+4) = 50.; // 878 - L1 right panel
        *(vthresh+20*NCOLS+4) = 250.; *(athresh+20*NCOLS+4) = 18.; *(dthresh+20*NCOLS+4) = 100.; // 878 - L1 slab
        *(vthresh+21*NCOLS+4) = 380.; *(athresh+21*NCOLS+4) = 25.; *(dthresh+21*NCOLS+4) = 100.; // 878 - Back slab
        *(vthresh+22*NCOLS+4) = 500.; *(athresh+22*NCOLS+4) = 10.; *(dthresh+22*NCOLS+4) = 40.; // 7725
        *(vthresh+23*NCOLS+4) = 580.; *(athresh+23*NCOLS+4) = 60.; *(dthresh+23*NCOLS+4) = 200.; // 878bar
        *(vthresh+24*NCOLS+4) = 90.; *(athresh+24*NCOLS+4) = 4.; *(dthresh+24*NCOLS+4) = 60.; // ET
        *(vthresh+25*NCOLS+4) = 80.; *(athresh+25*NCOLS+4) = 4.; *(dthresh+25*NCOLS+4) = 60.; // ET
        *(vthresh+26*NCOLS+4) = 30.; *(athresh+26*NCOLS+4) = 1.0; *(dthresh+26*NCOLS+4) = 60.; // 878 - L2 right panel
        *(vthresh+27*NCOLS+4) = 8.; *(athresh+27*NCOLS+4) = 0.4; *(dthresh+27*NCOLS+4) = 30.; // 878 - L0 left panel
        *(vthresh+28*NCOLS+4) = 90.; *(athresh+28*NCOLS+4) = 7.0; *(dthresh+28*NCOLS+4) = 80.; // 878 - L2 slab
        *(vthresh+29*NCOLS+4) = 6.; *(athresh+29*NCOLS+4) = 0.4; *(dthresh+29*NCOLS+4) = 20.; // 878 - L0 right panel
        *(vthresh+30*NCOLS+4) = 30.; *(athresh+30*NCOLS+4) = 1.0; *(dthresh+30*NCOLS+4) = 50.; // 878 - L1 top panel
        *(vthresh+31*NCOLS+4) = 25.; *(athresh+31*NCOLS+4) = 1.5; *(dthresh+31*NCOLS+4) = 60.; // 878 - L2 left panel
    }

    if (RunNum >= 816) { // ET=1100, 878box1=1450V, L3TL_878=1450V, L3BR_7725=1120V, L3ML_7725=1030V, Bars&Slabs=1450V, B=3.8T.
        *(vthresh+0*NCOLS+3) = 600.; *(athresh+0*NCOLS+3) = 60.; *(dthresh+0*NCOLS+3) = 80.; // 878bar
        *(vthresh+1*NCOLS+3) = 500.; *(athresh+1*NCOLS+3) = 65.; *(dthresh+1*NCOLS+3) = 100.; // 878bar
        *(vthresh+2*NCOLS+3) = 680.; *(athresh+2*NCOLS+3) = 70.; *(dthresh+2*NCOLS+3) = 100.; // 878bar
        *(vthresh+3*NCOLS+3) = 700.; *(athresh+3*NCOLS+3) = 80.; *(dthresh+3*NCOLS+3) = 100.; // 878bar
        *(vthresh+4*NCOLS+3) = 550.; *(athresh+4*NCOLS+3) = 75.; *(dthresh+4*NCOLS+3) = 100.; // 878bar
        *(vthresh+5*NCOLS+3) = 700.; *(athresh+5*NCOLS+3) = 28.; *(dthresh+5*NCOLS+3) = 80.; // 7725
        *(vthresh+6*NCOLS+3) = 580.; *(athresh+6*NCOLS+3) = 65.; *(dthresh+6*NCOLS+3) = 100.; // 878bar
        *(vthresh+7*NCOLS+3) = 720.; *(athresh+7*NCOLS+3) = 90.; *(dthresh+7*NCOLS+3) = 100.; // 878bar
        *(vthresh+8*NCOLS+3) = 10.; *(athresh+8*NCOLS+3) = 0.8; *(dthresh+8*NCOLS+3) = 40.; // ET
        *(vthresh+9*NCOLS+3) = 140.; *(athresh+9*NCOLS+3) = 6.; *(dthresh+9*NCOLS+3) = 80.; // ET
        *(vthresh+10*NCOLS+3) = 10.; *(athresh+10*NCOLS+3) = 0.6; *(dthresh+10*NCOLS+3) = 40.; // 878 - L0 top panel
        *(vthresh+11*NCOLS+3) = 25.; *(athresh+11*NCOLS+3) = 1.5; *(dthresh+11*NCOLS+3) = 40.; // 878 - L1 left panel
        *(vthresh+12*NCOLS+3) = 700.; *(athresh+12*NCOLS+3) = 80.; *(dthresh+12*NCOLS+3) = 100.; // 878bar
        *(vthresh+13*NCOLS+3) = 650.; *(athresh+13*NCOLS+3) = 80.; *(dthresh+13*NCOLS+3) = 100.; // 878bar
        *(vthresh+14*NCOLS+3) = 10.; *(athresh+14*NCOLS+3) = 0.3; *(dthresh+14*NCOLS+3) = 40.; // 878 - L2 top panel
        *(vthresh+15*NCOLS+3) = 999.; *(athresh+15*NCOLS+3) = 999; *(dthresh+15*NCOLS+3) = 10.; // LHC clock
        *(vthresh+16*NCOLS+3) = 880.; *(athresh+16*NCOLS+3) = 90.; *(dthresh+16*NCOLS+3) = 100.; // 878bar
        *(vthresh+17*NCOLS+3) = 100.; *(athresh+17*NCOLS+3) = 2.;  *(dthresh+17*NCOLS+3) = 50.; // ET
        *(vthresh+18*NCOLS+3) = 250.; *(athresh+18*NCOLS+3) = 20.; *(dthresh+18*NCOLS+3) = 80.; // 878 - L0 slab
        *(vthresh+19*NCOLS+3) = 40.; *(athresh+19*NCOLS+3) = 3.0; *(dthresh+19*NCOLS+3) = 50.; // 878 - L1 right panel
        *(vthresh+20*NCOLS+3) = 250.; *(athresh+20*NCOLS+3) = 18.; *(dthresh+20*NCOLS+3) = 100.; // 878 - L1 slab
        *(vthresh+21*NCOLS+3) = 380.; *(athresh+21*NCOLS+3) = 25.; *(dthresh+21*NCOLS+3) = 100.; // 878 - Back slab
        *(vthresh+22*NCOLS+3) = 500.; *(athresh+22*NCOLS+3) = 10.; *(dthresh+22*NCOLS+3) = 40.; // 7725
        *(vthresh+23*NCOLS+3) = 580.; *(athresh+23*NCOLS+3) = 60.; *(dthresh+23*NCOLS+3) = 200.; // 878bar
        *(vthresh+24*NCOLS+3) = 90.; *(athresh+24*NCOLS+3) = 4.; *(dthresh+24*NCOLS+3) = 60.; // ET
        *(vthresh+25*NCOLS+3) = 80.; *(athresh+25*NCOLS+3) = 4.; *(dthresh+25*NCOLS+3) = 60.; // ET
        *(vthresh+26*NCOLS+3) = 30.; *(athresh+26*NCOLS+3) = 1.0; *(dthresh+26*NCOLS+3) = 60.; // 878 - L2 right panel
        *(vthresh+27*NCOLS+3) = 8.; *(athresh+27*NCOLS+3) = 0.4; *(dthresh+27*NCOLS+3) = 30.; // 878 - L0 left panel
        *(vthresh+28*NCOLS+3) = 90.; *(athresh+28*NCOLS+3) = 7.0; *(dthresh+28*NCOLS+3) = 80.; // 878 - L2 slab
        *(vthresh+29*NCOLS+3) = 6.; *(athresh+29*NCOLS+3) = 0.4; *(dthresh+29*NCOLS+3) = 20.; // 878 - L0 right panel
        *(vthresh+30*NCOLS+3) = 30.; *(athresh+30*NCOLS+3) = 1.0; *(dthresh+30*NCOLS+3) = 50.; // 878 - L1 top panel
        *(vthresh+31*NCOLS+3) = 25.; *(athresh+31*NCOLS+3) = 1.5; *(dthresh+31*NCOLS+3) = 60.; // 878 - L2 left panel
        *(vthresh+0*NCOLS+4) = 600.; *(athresh+0*NCOLS+4) = 60.; *(dthresh+0*NCOLS+4) = 80.; // 878bar
        *(vthresh+1*NCOLS+4) = 500.; *(athresh+1*NCOLS+4) = 65.; *(dthresh+1*NCOLS+4) = 100.; // 878bar
        *(vthresh+2*NCOLS+4) = 680.; *(athresh+2*NCOLS+4) = 70.; *(dthresh+2*NCOLS+4) = 100.; // 878bar
        *(vthresh+3*NCOLS+4) = 700.; *(athresh+3*NCOLS+4) = 80.; *(dthresh+3*NCOLS+4) = 100.; // 878bar
        *(vthresh+4*NCOLS+4) = 550.; *(athresh+4*NCOLS+4) = 75.; *(dthresh+4*NCOLS+4) = 100.; // 878bar
        *(vthresh+5*NCOLS+4) = 700.; *(athresh+5*NCOLS+4) = 28.; *(dthresh+5*NCOLS+4) = 80.; // 7725
        *(vthresh+6*NCOLS+4) = 580.; *(athresh+6*NCOLS+4) = 65.; *(dthresh+6*NCOLS+4) = 100.; // 878bar
        *(vthresh+7*NCOLS+4) = 720.; *(athresh+7*NCOLS+4) = 90.; *(dthresh+7*NCOLS+4) = 100.; // 878bar
        *(vthresh+8*NCOLS+4) = 10.; *(athresh+8*NCOLS+4) = 0.8; *(dthresh+8*NCOLS+4) = 40.; // ET
        *(vthresh+9*NCOLS+4) = 140.; *(athresh+9*NCOLS+4) = 6.; *(dthresh+9*NCOLS+4) = 80.; // ET
        *(vthresh+10*NCOLS+4) = 10.; *(athresh+10*NCOLS+4) = 0.6; *(dthresh+10*NCOLS+4) = 40.; // 878 - L0 top panel
        *(vthresh+11*NCOLS+4) = 25.; *(athresh+11*NCOLS+4) = 1.5; *(dthresh+11*NCOLS+4) = 40.; // 878 - L1 left panel
        *(vthresh+12*NCOLS+4) = 700.; *(athresh+12*NCOLS+4) = 80.; *(dthresh+12*NCOLS+4) = 100.; // 878bar
        *(vthresh+13*NCOLS+4) = 650.; *(athresh+13*NCOLS+4) = 80.; *(dthresh+13*NCOLS+4) = 100.; // 878bar
        *(vthresh+14*NCOLS+4) = 10.; *(athresh+14*NCOLS+4) = 0.3; *(dthresh+14*NCOLS+4) = 40.; // 878 - L2 top panel
        *(vthresh+15*NCOLS+4) = 999.; *(athresh+15*NCOLS+4) = 999; *(dthresh+15*NCOLS+4) = 10.; // LHC clock
        *(vthresh+16*NCOLS+4) = 880.; *(athresh+16*NCOLS+4) = 90.; *(dthresh+16*NCOLS+4) = 100.; // 878bar
        *(vthresh+17*NCOLS+4) = 100.; *(athresh+17*NCOLS+4) = 2.;  *(dthresh+17*NCOLS+4) = 50.; // ET
        *(vthresh+18*NCOLS+4) = 250.; *(athresh+18*NCOLS+4) = 20.; *(dthresh+18*NCOLS+4) = 80.; // 878 - L0 slab
        *(vthresh+19*NCOLS+4) = 40.; *(athresh+19*NCOLS+4) = 3.0; *(dthresh+19*NCOLS+4) = 50.; // 878 - L1 right panel
        *(vthresh+20*NCOLS+4) = 250.; *(athresh+20*NCOLS+4) = 18.; *(dthresh+20*NCOLS+4) = 100.; // 878 - L1 slab
        *(vthresh+21*NCOLS+4) = 380.; *(athresh+21*NCOLS+4) = 25.; *(dthresh+21*NCOLS+4) = 100.; // 878 - Back slab
        *(vthresh+22*NCOLS+4) = 500.; *(athresh+22*NCOLS+4) = 10.; *(dthresh+22*NCOLS+4) = 40.; // 7725
        *(vthresh+23*NCOLS+4) = 580.; *(athresh+23*NCOLS+4) = 60.; *(dthresh+23*NCOLS+4) = 200.; // 878bar
        *(vthresh+24*NCOLS+4) = 90.; *(athresh+24*NCOLS+4) = 4.; *(dthresh+24*NCOLS+4) = 60.; // ET
        *(vthresh+25*NCOLS+4) = 80.; *(athresh+25*NCOLS+4) = 4.; *(dthresh+25*NCOLS+4) = 60.; // ET
        *(vthresh+26*NCOLS+4) = 30.; *(athresh+26*NCOLS+4) = 1.0; *(dthresh+26*NCOLS+4) = 60.; // 878 - L2 right panel
        *(vthresh+27*NCOLS+4) = 8.; *(athresh+27*NCOLS+4) = 0.4; *(dthresh+27*NCOLS+4) = 30.; // 878 - L0 left panel
        *(vthresh+28*NCOLS+4) = 90.; *(athresh+28*NCOLS+4) = 7.0; *(dthresh+28*NCOLS+4) = 80.; // 878 - L2 slab
        *(vthresh+29*NCOLS+4) = 6.; *(athresh+29*NCOLS+4) = 0.4; *(dthresh+29*NCOLS+4) = 20.; // 878 - L0 right panel
        *(vthresh+30*NCOLS+4) = 30.; *(athresh+30*NCOLS+4) = 1.0; *(dthresh+30*NCOLS+4) = 50.; // 878 - L1 top panel
        *(vthresh+31*NCOLS+4) = 25.; *(athresh+31*NCOLS+4) = 1.5; *(dthresh+31*NCOLS+4) = 60.; // 878 - L2 left panel
    }

    if (RunNum >= 816) { // ET=1100, 878box1=1450V, L3TL_878=1450V, L3BR_7725=1120V, L3ML_7725=1030V, Bars&Slabs=1400V, B=3.8T.
        *(vthresh+0*NCOLS+3) = 600.; *(athresh+0*NCOLS+3) = 60.; *(dthresh+0*NCOLS+3) = 80.; // 878bar
        *(vthresh+1*NCOLS+3) = 500.; *(athresh+1*NCOLS+3) = 65.; *(dthresh+1*NCOLS+3) = 100.; // 878bar
        *(vthresh+2*NCOLS+3) = 680.; *(athresh+2*NCOLS+3) = 70.; *(dthresh+2*NCOLS+3) = 100.; // 878bar
        *(vthresh+3*NCOLS+3) = 700.; *(athresh+3*NCOLS+3) = 80.; *(dthresh+3*NCOLS+3) = 100.; // 878bar
        *(vthresh+4*NCOLS+3) = 550.; *(athresh+4*NCOLS+3) = 75.; *(dthresh+4*NCOLS+3) = 100.; // 878bar
        *(vthresh+5*NCOLS+3) = 700.; *(athresh+5*NCOLS+3) = 28.; *(dthresh+5*NCOLS+3) = 80.; // 7725
        *(vthresh+6*NCOLS+3) = 580.; *(athresh+6*NCOLS+3) = 65.; *(dthresh+6*NCOLS+3) = 100.; // 878bar
        *(vthresh+7*NCOLS+3) = 720.; *(athresh+7*NCOLS+3) = 90.; *(dthresh+7*NCOLS+3) = 100.; // 878bar
        *(vthresh+8*NCOLS+3) = 10.; *(athresh+8*NCOLS+3) = 0.8; *(dthresh+8*NCOLS+3) = 40.; // ET
        *(vthresh+9*NCOLS+3) = 140.; *(athresh+9*NCOLS+3) = 6.; *(dthresh+9*NCOLS+3) = 80.; // ET
        *(vthresh+10*NCOLS+3) = 8.; *(athresh+10*NCOLS+3) = 0.1; *(dthresh+10*NCOLS+3) = 20.; // 878 - L0 top panel
        *(vthresh+11*NCOLS+3) = 8.; *(athresh+11*NCOLS+3) = 0.1; *(dthresh+11*NCOLS+3) = 20.; // 878 - L1 left panel
        *(vthresh+12*NCOLS+3) = 700.; *(athresh+12*NCOLS+3) = 80.; *(dthresh+12*NCOLS+3) = 100.; // 878bar
        *(vthresh+13*NCOLS+3) = 650.; *(athresh+13*NCOLS+3) = 80.; *(dthresh+13*NCOLS+3) = 100.; // 878bar
        *(vthresh+14*NCOLS+3) = 8.; *(athresh+14*NCOLS+3) = 0.1; *(dthresh+14*NCOLS+3) = 20.; // 878 - L2 top panel
        *(vthresh+15*NCOLS+3) = 999.; *(athresh+15*NCOLS+3) = 999; *(dthresh+15*NCOLS+3) = 10.; // LHC clock
        *(vthresh+16*NCOLS+3) = 880.; *(athresh+16*NCOLS+3) = 90.; *(dthresh+16*NCOLS+3) = 100.; // 878bar
        *(vthresh+17*NCOLS+3) = 100.; *(athresh+17*NCOLS+3) = 2.;  *(dthresh+17*NCOLS+3) = 50.; // ET
        *(vthresh+18*NCOLS+3) = 200.; *(athresh+18*NCOLS+3) = 10.; *(dthresh+18*NCOLS+3) = 80.; // 878 - L0 slab
        *(vthresh+19*NCOLS+3) = 8.; *(athresh+19*NCOLS+3) = 0.1; *(dthresh+19*NCOLS+3) = 20.; // 878 - L1 right panel
        *(vthresh+20*NCOLS+3) = 200.; *(athresh+20*NCOLS+3) = 10.; *(dthresh+20*NCOLS+3) = 100.; // 878 - L1 slab
        *(vthresh+21*NCOLS+3) = 300.; *(athresh+21*NCOLS+3) = 10.; *(dthresh+21*NCOLS+3) = 100.; // 878 - Back slab
        *(vthresh+22*NCOLS+3) = 500.; *(athresh+22*NCOLS+3) = 10.; *(dthresh+22*NCOLS+3) = 40.; // 7725
        *(vthresh+23*NCOLS+3) = 580.; *(athresh+23*NCOLS+3) = 60.; *(dthresh+23*NCOLS+3) = 200.; // 878bar
        *(vthresh+24*NCOLS+3) = 90.; *(athresh+24*NCOLS+3) = 4.; *(dthresh+24*NCOLS+3) = 60.; // ET
        *(vthresh+25*NCOLS+3) = 80.; *(athresh+25*NCOLS+3) = 4.; *(dthresh+25*NCOLS+3) = 60.; // ET
        *(vthresh+26*NCOLS+3) = 8.; *(athresh+26*NCOLS+3) = 0.1; *(dthresh+26*NCOLS+3) = 20.; // 878 - L2 right panel
        *(vthresh+27*NCOLS+3) = 8.; *(athresh+27*NCOLS+3) = 0.1; *(dthresh+27*NCOLS+3) = 20.; // 878 - L0 left panel
        *(vthresh+28*NCOLS+3) = 60.; *(athresh+28*NCOLS+3) = 4.0; *(dthresh+28*NCOLS+3) = 80.; // 878 - L2 slab
        *(vthresh+29*NCOLS+3) = 6.; *(athresh+29*NCOLS+3) = 0.1; *(dthresh+29*NCOLS+3) = 20.; // 878 - L0 right panel
        *(vthresh+30*NCOLS+3) = 8.; *(athresh+30*NCOLS+3) = 0.1; *(dthresh+30*NCOLS+3) = 20.; // 878 - L1 top panel
        *(vthresh+31*NCOLS+3) = 8.; *(athresh+31*NCOLS+3) = 0.1; *(dthresh+31*NCOLS+3) = 20.; // 878 - L2 left panel
        *(vthresh+0*NCOLS+4) = 600.; *(athresh+0*NCOLS+4) = 60.; *(dthresh+0*NCOLS+4) = 80.; // 878bar
        *(vthresh+1*NCOLS+4) = 500.; *(athresh+1*NCOLS+4) = 65.; *(dthresh+1*NCOLS+4) = 100.; // 878bar
        *(vthresh+2*NCOLS+4) = 680.; *(athresh+2*NCOLS+4) = 70.; *(dthresh+2*NCOLS+4) = 100.; // 878bar
        *(vthresh+3*NCOLS+4) = 700.; *(athresh+3*NCOLS+4) = 80.; *(dthresh+3*NCOLS+4) = 100.; // 878bar
        *(vthresh+4*NCOLS+4) = 550.; *(athresh+4*NCOLS+4) = 75.; *(dthresh+4*NCOLS+4) = 100.; // 878bar
        *(vthresh+5*NCOLS+4) = 700.; *(athresh+5*NCOLS+4) = 28.; *(dthresh+5*NCOLS+4) = 80.; // 7725
        *(vthresh+6*NCOLS+4) = 580.; *(athresh+6*NCOLS+4) = 65.; *(dthresh+6*NCOLS+4) = 100.; // 878bar
        *(vthresh+7*NCOLS+4) = 720.; *(athresh+7*NCOLS+4) = 90.; *(dthresh+7*NCOLS+4) = 100.; // 878bar
        *(vthresh+8*NCOLS+4) = 10.; *(athresh+8*NCOLS+4) = 0.8; *(dthresh+8*NCOLS+4) = 40.; // ET
        *(vthresh+9*NCOLS+4) = 140.; *(athresh+9*NCOLS+4) = 6.; *(dthresh+9*NCOLS+4) = 40.; // ET
        *(vthresh+10*NCOLS+4) = 8.; *(athresh+10*NCOLS+4) = 0.1; *(dthresh+10*NCOLS+4) = 20.; // 878 - L0 top panel
        *(vthresh+11*NCOLS+4) = 8.; *(athresh+11*NCOLS+4) = 0.1; *(dthresh+11*NCOLS+4) = 20.; // 878 - L1 left panel
        *(vthresh+12*NCOLS+4) = 700.; *(athresh+12*NCOLS+4) = 80.; *(dthresh+12*NCOLS+4) = 100.; // 878bar
        *(vthresh+13*NCOLS+4) = 650.; *(athresh+13*NCOLS+4) = 80.; *(dthresh+13*NCOLS+4) = 100.; // 878bar
        *(vthresh+14*NCOLS+4) = 8.; *(athresh+14*NCOLS+4) = 0.1; *(dthresh+14*NCOLS+4) = 20.; // 878 - L2 top panel
        *(vthresh+15*NCOLS+4) = 999.; *(athresh+15*NCOLS+4) = 999; *(dthresh+15*NCOLS+4) = 10.; // LHC clock
        *(vthresh+16*NCOLS+4) = 880.; *(athresh+16*NCOLS+4) = 90.; *(dthresh+16*NCOLS+4) = 100.; // 878bar
        *(vthresh+17*NCOLS+4) = 100.; *(athresh+17*NCOLS+4) = 2.;  *(dthresh+17*NCOLS+4) = 40.; // ET
        *(vthresh+18*NCOLS+4) = 200.; *(athresh+18*NCOLS+4) = 10.; *(dthresh+18*NCOLS+4) = 80.; // 878 - L0 slab
        *(vthresh+19*NCOLS+4) = 8.; *(athresh+19*NCOLS+4) = 0.1; *(dthresh+19*NCOLS+4) = 20.; // 878 - L1 right panel
        *(vthresh+20*NCOLS+4) = 200.; *(athresh+20*NCOLS+4) = 10.; *(dthresh+20*NCOLS+4) = 100.; // 878 - L1 slab
        *(vthresh+21*NCOLS+4) = 300.; *(athresh+21*NCOLS+4) = 10.; *(dthresh+21*NCOLS+4) = 100.; // 878 - Back slab
        *(vthresh+22*NCOLS+4) = 500.; *(athresh+22*NCOLS+4) = 10.; *(dthresh+22*NCOLS+4) = 40.; // 7725
        *(vthresh+23*NCOLS+4) = 580.; *(athresh+23*NCOLS+4) = 60.; *(dthresh+23*NCOLS+4) = 200.; // 878bar
        *(vthresh+24*NCOLS+4) = 90.; *(athresh+24*NCOLS+4) = 4.; *(dthresh+24*NCOLS+4) = 60.; // ET
        *(vthresh+25*NCOLS+4) = 80.; *(athresh+25*NCOLS+4) = 4.; *(dthresh+25*NCOLS+4) = 60.; // ET
        *(vthresh+26*NCOLS+4) = 8.; *(athresh+26*NCOLS+4) = 0.1; *(dthresh+26*NCOLS+4) = 20.; // 878 - L2 right panel
        *(vthresh+27*NCOLS+4) = 8.; *(athresh+27*NCOLS+4) = 0.1; *(dthresh+27*NCOLS+4) = 20.; // 878 - L0 left panel
        *(vthresh+28*NCOLS+4) = 60.; *(athresh+28*NCOLS+4) = 4.0; *(dthresh+28*NCOLS+4) = 80.; // 878 - L2 slab
        *(vthresh+29*NCOLS+4) = 6.; *(athresh+29*NCOLS+4) = 0.1; *(dthresh+29*NCOLS+4) = 20.; // 878 - L0 right panel
        *(vthresh+30*NCOLS+4) = 8.; *(athresh+30*NCOLS+4) = 0.1; *(dthresh+30*NCOLS+4) = 20.; // 878 - L1 top panel
        *(vthresh+31*NCOLS+4) = 8.; *(athresh+31*NCOLS+4) = 1.5; *(dthresh+31*NCOLS+4) = 20.; // 878 - L2 left panel
    }

    if (RunNum >= 931) { // ET=1450, All878s=1450V, L3BR_7725=1220V, L3ML_7725=1130V, B=3.8T.
        *(vthresh+0*NCOLS+3) = 500.; *(athresh+0*NCOLS+3) = 70.; *(dthresh+0*NCOLS+3) = 200.; // 878bar
        *(vthresh+1*NCOLS+3) = 600.; *(athresh+1*NCOLS+3) = 60.; *(dthresh+1*NCOLS+3) = 200.; // 878bar
        *(vthresh+2*NCOLS+3) = 670.; *(athresh+2*NCOLS+3) = 75.; *(dthresh+2*NCOLS+3) = 200.; // 878bar
        *(vthresh+3*NCOLS+3) = 700.; *(athresh+3*NCOLS+3) = 82.; *(dthresh+3*NCOLS+3) = 200.; // 878bar
        *(vthresh+4*NCOLS+3) = 570.; *(athresh+4*NCOLS+3) = 80.; *(dthresh+4*NCOLS+3) = 200.; // 878bar
        *(vthresh+5*NCOLS+3) = 1100.; *(athresh+5*NCOLS+3) = 50.; *(dthresh+5*NCOLS+3) = 100.; // 7725
        *(vthresh+6*NCOLS+3) = 600.; *(athresh+6*NCOLS+3) = 65.; *(dthresh+6*NCOLS+3) = 200.; // 878bar
        *(vthresh+7*NCOLS+3) = 750.; *(athresh+7*NCOLS+3) = 95.; *(dthresh+7*NCOLS+3) = 200.; // 878bar
        *(vthresh+8*NCOLS+3) = 750.; *(athresh+8*NCOLS+3) = 60.; *(dthresh+8*NCOLS+3) = 200.; // R878bar (new)
        *(vthresh+9*NCOLS+3) = 1100.; *(athresh+9*NCOLS+3) = 85.; *(dthresh+9*NCOLS+3) = 40.; // ET
        *(vthresh+10*NCOLS+3) = 10.; *(athresh+10*NCOLS+3) = 0.6; *(dthresh+10*NCOLS+3) = 40.; // 878 - L0 top panel
        *(vthresh+11*NCOLS+3) = 10.; *(athresh+11*NCOLS+3) = 1.0; *(dthresh+11*NCOLS+3) = 40.; // 878 - L1 top panel
        *(vthresh+12*NCOLS+3) = 720.; *(athresh+12*NCOLS+3) = 80.; *(dthresh+12*NCOLS+3) = 200.; // 878bar
        *(vthresh+13*NCOLS+3) = 650.; *(athresh+13*NCOLS+3) = 80.; *(dthresh+13*NCOLS+3) = 200.; // 878bar
        *(vthresh+14*NCOLS+3) = 10.; *(athresh+14*NCOLS+3) = 0.5; *(dthresh+14*NCOLS+3) = 30.; // 878 - L2 top panel
        *(vthresh+15*NCOLS+3) = 999.; *(athresh+15*NCOLS+3) = 999; *(dthresh+15*NCOLS+3) = 10.; // LHC clock
        *(vthresh+16*NCOLS+3) = 850.; *(athresh+16*NCOLS+3) = 90.; *(dthresh+16*NCOLS+3) = 200.; // 878bar
        *(vthresh+17*NCOLS+3) = 1100.; *(athresh+17*NCOLS+3) = 70.;  *(dthresh+17*NCOLS+3) = 40.; // ET
        *(vthresh+18*NCOLS+3) = 200.; *(athresh+18*NCOLS+3) = 20.; *(dthresh+18*NCOLS+3) = 80.; // 878 - L0 slab
        *(vthresh+19*NCOLS+3) = 20.; *(athresh+19*NCOLS+3) = 1.0; *(dthresh+19*NCOLS+3) = 20.; // 878 - L1 right panel
        *(vthresh+20*NCOLS+3) = 250.; *(athresh+20*NCOLS+3) = 18.; *(dthresh+20*NCOLS+3) = 80.; // 878 - L1 slab
        *(vthresh+21*NCOLS+3) = 300.; *(athresh+21*NCOLS+3) = 15.; *(dthresh+21*NCOLS+3) = 80.; // 878 - Back slab
        *(vthresh+22*NCOLS+3) = 1100.; *(athresh+22*NCOLS+3) = 25.; *(dthresh+22*NCOLS+3) = 40.; // 7725
        *(vthresh+23*NCOLS+3) = 560.; *(athresh+23*NCOLS+3) = 65.; *(dthresh+23*NCOLS+3) = 200.; // 878bar
        *(vthresh+24*NCOLS+3) = 1100.; *(athresh+24*NCOLS+3) = 70.; *(dthresh+24*NCOLS+3) = 20.; // ET
        *(vthresh+25*NCOLS+3) = 1100.; *(athresh+25*NCOLS+3) = 60.; *(dthresh+25*NCOLS+3) = 20.; // ET
        *(vthresh+26*NCOLS+3) = 20.; *(athresh+26*NCOLS+3) = 1.; *(dthresh+26*NCOLS+3) = 20.; // 878 - L2 right panel
        *(vthresh+27*NCOLS+3) = 20.; *(athresh+27*NCOLS+3) = 1.; *(dthresh+27*NCOLS+3) = 20.; // 878 - L0 left panel
        *(vthresh+28*NCOLS+3) = 140.; *(athresh+28*NCOLS+3) = 8.0; *(dthresh+28*NCOLS+3) = 40.; // 878 - L2 slab
        *(vthresh+29*NCOLS+3) = 8.; *(athresh+29*NCOLS+3) = 0.2; *(dthresh+29*NCOLS+3) = 20.; // 878 - L0 right panel
        *(vthresh+30*NCOLS+3) = 20.; *(athresh+30*NCOLS+3) = 1.; *(dthresh+30*NCOLS+3) = 20.; // 878 - L1 left panel
        *(vthresh+31*NCOLS+3) = 20.; *(athresh+31*NCOLS+3) = 1.; *(dthresh+31*NCOLS+3) = 20.; // 878 - L2 left panel
        for(int c=0; c<32; c++) {
            *(vthresh+c*NCOLS+4) = *(vthresh+c*NCOLS+3);
            *(athresh+c*NCOLS+4) = *(athresh+c*NCOLS+3);
            *(dthresh+c*NCOLS+4) = *(dthresh+c*NCOLS+3);
        }
    }
}

#endif
