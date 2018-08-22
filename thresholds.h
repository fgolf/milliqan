#ifndef thresholds_h
#define thresholds_h

// Set voltage and area thresholds for pulses to count as hits.
// These thresholds differ across channels and differ by event category (0=All, 1=SPE, 2=Small, 3=Cosmic, 4=Thru).
void set_thresholds(float*, float*, float*, int);

#endif
