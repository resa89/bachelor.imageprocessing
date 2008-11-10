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

void straight(const mxArray* source, mxArray* dest)
{
    int mrows;
    int ncols;
    int i;
            
    const unsigned char* input;
    unsigned char* output;
    
    mrows = mxGetM(source);
    ncols = mxGetN(source);
    input = (unsigned char*) mxGetPr(source);
    output = (unsigned char*) mxGetPr(dest);    
    
    for (i = 0; i < mrows*ncols; ++i)
        output[i] = input[i];    
}

void invert(const mxArray* source, mxArray* dest)
{
    int mrows;
    int ncols;
    int i;
    
    const unsigned char* input;
    unsigned char* output;
    
    mrows = mxGetM(source);
    ncols = mxGetN(source);
    input = (unsigned char*) mxGetPr(source);
    output = (unsigned char*) mxGetPr(dest);
    
    for (i = 0; i < mrows*ncols; ++i)
        output[i] = 255 - input[i];    
}


int modifyValue(int value)
{
    if ( (value * 1.10) > 255
         || value < 50 || value > 200 )
        return value;
    return (int)(value * 1.10);   
}

void outshine(const mxArray* source, mxArray* dest)
{
    int mrows;
    int ncols;
    int i;
    
    const unsigned char* input;
    unsigned char* output;
    
    mrows = mxGetM(source);
    ncols = mxGetN(source);
    input = (unsigned char*) mxGetPr(source);
    output = (unsigned char*) mxGetPr(dest);
    
    for (i = 0; i < mrows*ncols; ++i)
        output[i] = input[i] + modifyValue(input[i]);    
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
    
    // check paramters: nlhs, nrhs
    if (nlhs > 1 || nrhs > 1 || nrhs < 1)
        mexErrMsgTxt("Usage: picOut = myLut(picIn);");
    
    // check input: uint8
    if (!mxIsUint8(prhs[0]))
        mexErrMsgTxt("myLut: Image must be uint8");
    
    // input / output
    dims[0] = mxGetM(prhs[0]);
	dims[1] = mxGetN(prhs[0]);
    
    // create output array (mxUINT8_CLASS)
    plhs[0] = mxCreateNumericArray(2, dims, mxUINT8_CLASS, mxREAL);
    
    // Lut operation
    outshine(prhs[0], plhs[0]);
}
