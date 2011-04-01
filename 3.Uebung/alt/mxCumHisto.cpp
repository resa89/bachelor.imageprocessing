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
    // check paramters: nlhs, nrhs
	
    // check input: uint8
    
    // check bin: double, complex, height and width
    
	// load bin = mxGetPr(prhs[1])[0];
                
	// check bin: 1 <= bin <= 256
    
    // input / output
    
    // create output array
	
    // create histogram: cumulative histogram (...);
    // mxHisto(prhs[0], plhs[0], bin);    
}