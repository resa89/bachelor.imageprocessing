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

static const int numberIntensities = 256; // number of max intensity values    

void myLut_func(const mxArray* source, mxArray* dest);

void mexFunction( int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) 
{  
    int dims[2];
    int height, width;
    
    // check paramters: nlhs, nrhs
    if (nlhs > 1 || nrhs != 1) {
		mexErrMsgTxt("Usage: lut = myLut(imIn)");
	}
    
    // check input: uint8
    if (!mxIsUint8(prhs[0]))
        mexErrMsgTxt("myLut: Image must be uint8");
    
    // input / output
    width = mxGetM(prhs[0]);
    height = mxGetN(prhs[0]);
    dims[0] = width;
    dims[1] = height;
    
    // create output array (mxUINT8_CLASS)
    plhs[0] = mxCreateNumericArray(2, dims, mxUINT8_CLASS, mxREAL);
    
    // Lut operation
    myLut_func(prhs[0], plhs[0]);
}

void myLut_func(const mxArray* source, mxArray* dest)
{
    unsigned char* pSource = (unsigned char*) mxGetData(source);
    unsigned char* pDest = (unsigned char*) mxGetData(dest);
    
    const int width = mxGetM(source);
	const int height = mxGetN(source);
    const int dimension = height * width;
    
    unsigned int lut[numberIntensities];
    
    for(int i = 0; i < numberIntensities; i++) {
       if(i < 128)
           lut[i] = i + 50;
       else
           lut[i] = i;
    }
    
    for (int i = 0; i < dimension; i++) {
        pDest[i] = lut[pSource[i]];
    }
}


