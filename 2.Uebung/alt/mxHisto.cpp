#include "mex.h"

/*=========================================================================
 *  Compiling und Linking
 *  Use     mex -setup  to select a C++ compiler, then tpye:
 *          mex filename.cpp
 *=======================================================================*/

/*=========================================================================
 *  !Memory Consideration For Class Destructors!
 *  Do not use the mxFree or mxDestroyArray functions in a C++ destructor
 *  of a class used in a MEX-function. MATLAB performs cleanup of MEX-file
 *  variables if an error is thrown from the MEX-function, as described in 
 *  AUTOMATIC CLEANUP OF TEMPORARY ARRAYS.
 *=======================================================================*/

/*=========================================================================
 *  Entry point to C MEX-file 
 *=========================================================================
 *  prhs: An array of right-hand input arguments
 *  plhs: An array of left-hand output arguments
 *  nrhs: The number of right-hand arguments, or the size of the prhs array
 *  nlhs: The number of left-hand arguments, or the size of the plhs array
 *=======================================================================*/
void mexFunction( int nlhs, mxArray *plhs[],
    int nrhs, const mxArray *prhs[]) 
{
    int binHeight;
    int binWidth;
    int bin;
    int dims[2];
    
    // check paramters: nlhs, nrhs
    if (nlhs > 2 || nrhs < 2 || nrhs > 2)
        mxErrMsgTxt("Usage: histo = mxHisto(Image, binSize)");
        
    // check input: uint8
    if (!mxIsUint8(prhs[0]))
        mxErrMsgTxt("mxHisto: Image must be uint8");
    
    binHeight = mxGetM(prhs[1]);
    binWidth = mxGetN(prhs[1]);
    // check bin: double, complex, height and width
    if (!mxIsDouble(prhs[1]) || mxIsComplex(prhs[1])
            || !(binHeight == 1 && binWidth == 1))
        mxErrMsgTxt("binSize must be non-complex scalar uint8");
    
	// load bin = mxGetPr(prhs[1])[0];
    
	// check bin: 1 <= bin <= 256
    
    // input / output
    
    // create output array
	
	// create histogram: mxHisto(...);
    mxHisto(prhs[0], plhs[0], bin);    
}

void mxHisto(const mxArray* source, mxArray* dest, int bin)
{
	
}


