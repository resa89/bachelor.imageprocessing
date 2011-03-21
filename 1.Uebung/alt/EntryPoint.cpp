#include "mex.h"

void copy(unsigned char* pDest, unsigned char* pSource,
        int height, int width)
{

}

void upsideDown(unsigned char* pDestBase, unsigned char* pSourceBase, 
     int height, int width)
{

	
}

void mirror(unsigned char* pDestBase, unsigned char* pSourceBase, 
     int height, int width)
{

	
}

/*=========================================================================
 *  Compiling und Linking
 *  Use     mex -setup  to select a C++ compiler, then type:
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
 *  prhs: An array of right-hand input arguments (INPUT)
 *  plhs: An array of left-hand output arguments (OUTPUT)
 *  nrhs: The number of right-hand arguments, or the size of the prhs array
 *  nlhs: The number of left-hand arguments, or the size of the plhs array
 *=======================================================================*/
void mexFunction( int nlhs, mxArray *plhs[],
    int nrhs, const mxArray *prhs[]) 
{    
    int dims[2];
    int height;
    int width;
    int x;
    int y;    
    unsigned char* pSource;    
    unsigned char* pDest;
    
    // check parameters, only allow 1
    if(nlhs > 1 || nrhs != 1)
        mexErrMsgTxt("Usage: imOut = EntryPoint(imIn)");
    
    // Get image size, don't mess up dims 1 and 0! 
    height = dims[1] =  mxGetN(prhs[0]);
    width = dims[0] = mxGetM(prhs[0]);

    // we only support 8 bit images (char*)
	if (!mxIsUint8(prhs[0]))
		mexErrMsgTxt("EntryPoint can only process UINT8.");

    //input
    pSource = (unsigned char*) mxGetData(prhs[0]);
    
    // output
    plhs[0] = mxCreateNumericArray(2, dims, mxUINT8_CLASS, mxREAL);
    pDest = (unsigned char*) mxGetData(plhs[0]);    

	// To Do: copy possibly modified image data to right hand side results
    mirror(pDest, pSource, height, width);
    // delete local objects ?     
}
