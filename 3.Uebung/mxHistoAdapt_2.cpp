#include <math.h>
#include "mex.h"

void adaptHisto(const mxArray* refHisto, const mxArray* adaptHisto, mxArray* adaptLUT)
{    
    //(ref and adapt), obtain the number of pixel elements    
    
    // normalize histogram values, and create normHisto
    
	// CDFSum, compute cumulative distribution function   

    // compute look-up table

    // delete ?
}
static void matchHistograms (unsigned int *cumulativeHistogramOriginal, unsigned int *cumulativeHistogramReference, unsigned int *dest);

static const int intensities = 256;
static int dimension;

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{       
	int mrows1, ncols1, mrows0, ncols0;
    int dims[2];
    
    // check: nlhs ,nrhs
    
    mrows1 = mxGetM(prhs[1]);
    ncols1 = mxGetN(prhs[1]);
    mrows0 = mxGetM(prhs[0]);
    ncols0 = mxGetN(prhs[0]);
    
    if (!mxIsUint8(prhs[0])) {
        //mexErrMsgTxt("mxHistAdapt can only process uint8 Look-up table");
    } else if (!(mrows0 == 1 && ncols0 == 256)) {
        mexErrMsgTxt("Look-up table size must be [1][256]");
    }
    
    if (!mxIsUint8(prhs[1])) {
        //mexErrMsgTxt("mxHistAdapt can only process uint8 Look-up table");
    } else if (!(mrows1 == 1 && ncols1 == 256)) {
        mexErrMsgTxt("Look-up table size must be [1][256]");
    }
    
    if (mrows1 != mrows0 || ncols1 != ncols0) {
        mexErrMsgTxt("The given array must have the same size");
    }
  
    dimension = mrows1 * ncols1;
    
    // check paramters: nlhs, nrhs
    if (nlhs > 1 || nrhs < 2|| nrhs > 2)
        mexErrMsgTxt("Usage: mxHistoAdapt(refHisto, adaptHisto);");
    
    // input / output
	dims[0] = mrows0;
	dims[1] = ncols0;
    
    // create output array (mxUINT8_CLASS)
    plhs[0] = mxCreateNumericArray(2, dims, mxUINT8_CLASS, mxREAL);
        
    unsigned int *phRef = (unsigned int*) mxGetData(prhs[0]);
    unsigned int *phAdapt = (unsigned int*) mxGetData(prhs[1]);
    unsigned int *pLUT = (unsigned int*) mxGetData(plhs[0]);
    
    matchHistograms(phRef, phAdapt, pLUT);    
}

// returns the cumul. distribution function for histogram h
static void createCumulativeDistributionFunction (unsigned int *h, double *P) {    
    unsigned int hValue = 0, sum = 0; //h[0]; // cumulate histogram values
    
   for (int i=0; i < intensities; i++) {
        sum += h[i];
    }
    
    for (int i = 0; i < intensities; i++) {
        hValue += h[i];
        P[i] = (double) hValue / sum;
    }
}

// returns the mapping function F () to be applied to image I A
static int[] matchHistograms (unsigned int *adaptHisto, unsigned int *refHisto, unsigned int *dest) {

    double cumAdaptHisto[intensities]; 
    double cumRefHisto[intensities];
    int[] lut = new int[adaptHisto.length];
    
    createCumulativeDistributionFunction(refHisto, cumRefHisto); // create CDF table
    createCumulativeDistributionFunction(adaptHisto, cumAadaptHisto); // create CDF table
    
    int newIntensity;
    int intensities = adaptHisto.length;
    
    // compute mapping function f hs ():
    for (int intensity = 0; intensity < intensities; intensity++) {
        newIntensity = intensities - 1;
        
        do {
            lut[intensity] = newIntensity;
            newIntensity--;
        } while (newIntensity >= 0 && cumAdaptHisto[intensity] <= cumRefHisto[newIntensity]);
    }
    return lut;
}

void changeImage(const mxArray* source, mxArray* dest, const mxArray* lut)
{
   const int height = mxGetM(source);
    const int width = mxGetN(source);
   const int dimension = height * width;
   
   unsigned char* pSource = (unsigned char*) mxGetData(source);
   unsigned char* pDest = (unsigned char*) mxGetData(dest);
   unsigned char* pLut = (unsigned char*) mxGetData(lut);
   
   int oldIntensity;
   
   for (int i = 0; i < dimension; i++) {
       oldIntensity = pSource[i];
       pDest[i] = pLut[oldIntensity];
   }
}