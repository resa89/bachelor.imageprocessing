/* -------------------------------------------------------------------------
%   Uebung 3, Di Martino, Stefano, 286021,
%   Semester 7, stemarti@htwg-konstanz.de, 15. April 2014
%
%   Uebung 3, Willhelm, Andreas, 286297,
%   Semester, anwilhel@htwg-konstanz.de, 15. April 2014
%
%   Uebung 3, Kocher, Theresa,
%
% -------------------------------------------------------------------------
*/

#include <math.h>
#include "mex.h"

static const int intensities = 256;

// returns the cumul. distribution function for histogram h
static void createCumulativeDistributionFunction ( unsigned int *h, double *P) {    
    double hValue = 0.0, sum = 0.0; // cumulate histogram values
    
    for (int i = 0; i < intensities; i++) {
        sum += h[i];
    }

    for (int i = 0; i < intensities; i++) {
        hValue += h[i];	//cumulative
        P[i] = (double) hValue / sum; //normalize
    }
}

// returns the mapping function F () to be applied to image I A
static void adaptHisto (unsigned int *hReference, unsigned int *hOriginal, unsigned int *hAdapt) {
    double POriginal[intensities]; 
    double PReference[intensities];
    
    createCumulativeDistributionFunction(hReference, PReference); // create CDF table
    createCumulativeDistributionFunction(hOriginal, POriginal); // create CDF table
    
    int newIntensity;
    // compute mapping function f hs ():
    for (int intensity = 0; intensity < intensities; intensity++) {
        newIntensity = intensities - 1;
        
        do {
            hAdapt[intensity] = newIntensity;
            newIntensity--;
        } while (newIntensity >= 0 && POriginal[intensity] <= PReference[newIntensity]);
    }
}


void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{       
	int mrows1, ncols1, mrows0, ncols0;
    int dims[2];
    
    // check: nlhs ,nrhs
    mrows1 = mxGetM(prhs[1]);
    ncols1 = mxGetN(prhs[1]);
    mrows0 = mxGetM(prhs[0]);
    ncols0 = mxGetN(prhs[0]);
    
    if (!(mrows0 == 1 && ncols0 == 256)) {
        mexErrMsgTxt("Look-up table size must be [1][256]");
    }
    if (!(mrows1 == 1 && ncols1 == 256)) {
        mexErrMsgTxt("Look-up table size must be [1][256]");
    }
    if (mrows1 != mrows0 || ncols1 != ncols0) {
        mexErrMsgTxt("The given array must have the same size");
    }
	
    // check paramters: nlhs, nrhs
    if (nlhs > 1 || nrhs != 2)
        mexErrMsgTxt("Usage: mxHistoAdapt(refHisto, adaptHisto);");

    // input / output
	dims[0] = mrows0;
	dims[1] = ncols0;
    
    // create output array
    plhs[0] = mxCreateNumericArray(2, dims, mxUINT32_CLASS, mxREAL);
    
    unsigned int *phRef = (unsigned int*) mxGetData(prhs[0]);
    unsigned int *phOrig = (unsigned int*) mxGetData(prhs[1]);
    unsigned int *pLUT = (unsigned int*) mxGetData(plhs[0]);
    
    adaptHisto(phRef, phOrig, pLUT);     
}