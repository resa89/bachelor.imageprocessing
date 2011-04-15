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

void mxLut(const mxArray* source, mxArray* dest, const mxArray* lut)
{
    int mrows;
    int ncols;
    int i;
    const unsigned char* in;
    unsigned char* out;
    double* pLut;
    
    mrows = mxGetM(source);
    ncols = mxGetN(source);
    in = (unsigned char*) mxGetPr(source);
    out = (unsigned char*) mxGetPr(dest);
    pLut = (double*) mxGetPr(lut);
    
    for (i = 0; i < mrows*ncols; ++i)
        out[i] = pLut[in[i]];    
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
    mrows = mxGetM(prhs[1]);
    ncols = mxGetN(prhs[1]);
    if (!mxIsDouble(prhs[1]))
        mexErrMsgTxt("mxLut can only process double Look-up table");
    else if (!(mrows == 1 && ncols == 256))
        mexErrMsgTxt("Look-up table size must be [1][256]");
    
    // input / output
    dims[0] = mxGetM(prhs[0]);
    dims[1] = mxGetN(prhs[0]);
    
    // create output array (mxUINT8_CLASS)
    plhs[0] = mxCreateNumericArray(2, dims, mxDOUBLE_CLASS, mxREAL); 
    
    // Lut operation
    mxLut(prhs[0], plhs[0], prhs[1]);
}