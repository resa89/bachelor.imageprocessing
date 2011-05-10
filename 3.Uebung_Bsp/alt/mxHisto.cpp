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

void mxHisto(const mxArray* source, mxArray* dest, int bin)
{
    int mrows;
    int ncols;
    const unsigned char* image;
    double* histo;
    int i;
    
    mrows = mxGetM(source);
    ncols = mxGetN(source);
    image = (unsigned char*) mxGetData(source);
    histo = mxGetPr(dest);
    
    for (i = 0; i < mrows*ncols; ++i)
        histo[image[i]/bin] += 1.0;
}

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
        mexErrMsgTxt("Usage: histo = mxHisto(Image, binSize)");
        
    // check input: uint8
    if (!mxIsUint8(prhs[0]))
        mexErrMsgTxt("mxHisto: Image must be uint8");
    
    binHeight = mxGetM(prhs[1]);
    binWidth = mxGetN(prhs[1]);
    // check bin: double, complex, height and width
    if (!mxIsDouble(prhs[1]) || mxIsComplex(prhs[1])
            || !(binHeight == 1 && binWidth == 1))
        mexErrMsgTxt("binSize must be non-complex scalar uint8");
    
	// load bin = mxGetPr(prhs[1])[0];
    bin = 0;
    bin = mxGetPr(prhs[1])[0];
    
	// check bin: 1 <= bin <= 256
    if (bin < 1)
        bin = 1;
    else if (bin > 256)
        bin = 256;
    
    // input / output
    dims[0] = 1;
    dims[1] = 256/bin;
    
    // create output array
    plhs[0] = mxCreateNumericArray(2, dims, mxDOUBLE_CLASS, mxREAL);
	// create histogram: mxHisto(...);
    mxHisto(prhs[0], plhs[0], bin);    
}