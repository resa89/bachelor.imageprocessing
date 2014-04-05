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

void mxLut(const mxArray* source, mxArray* dest, const mxArray* lut);

void mexFunction( int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) 
{   
    int dims[2];
    int mrows;
    int ncols;
    
    // check paramters: nlhs, nrhs
    if (nlhs > 1 || nrhs < 2|| nrhs > 2)
        mexErrMsgTxt("Usage: picOut = mxLut(picIn, lut);");
    
    // check input: Image
    if (!mxIsUint8(prhs[0]))
        mexErrMsgTxt("mxLut can only process uint8 Image");
    
    // check input: lut - uint8, complex, [1] [256]
    //mrows = mxGetM(prhs[1]);
    //ncols = mxGetN(prhs[1]);
    ncols = mxGetM(prhs[1]);
    mrows = mxGetN(prhs[1]);
    
    if (!mxIsUint8(prhs[1]))
        mexErrMsgTxt("mxLut can only process uint8 Look-up table");
    else if (!(mrows == 1 && ncols == 256)) {
        mexErrMsgTxt("Look-up table size must be [1][256]");
    }
    // input / output
    
	dims[0] = mxGetM(prhs[0]);
	dims[1] = mxGetN(prhs[0]);
    
    // create output array (mxUINT8_CLASS)
    plhs[0] = mxCreateNumericArray(2, dims, mxUINT8_CLASS, mxREAL);
    
    // Lut operation
    mxLut(prhs[0], plhs[0], prhs[1]);
}

void mxLut(const mxArray* source, mxArray* dest, const mxArray* lut)
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