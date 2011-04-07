#include "mex.h"

/*=========================================================================
 *  Compiling und Linking
 *  Use     mex -setup  to select a C++ compiler, then tpye:
 *          mex filename.cpp
 *=======================================================================*/

enum edge
{
    MIN,
    MAX,
    CONTINUE,
    MIRROR
};

/*=========================================================================
 *  inImage:	Input Image (uint8)
 *  outImage:	Output Image(uint8)
 *	filter: 	matrix (double)
 *  offset:     value (uint8)
 *=======================================================================*/
void mxFilter(const mxArray* inImage, mxArray* outImage, 
        const mxArray* matrix, double offset)
{    
    // Image size

    // Filter size

	// Get Pointer (inImage, outImage, matrix)

	// center of filter
    
    // copy Image;    
    
    // To Do: Convolution:

            // compute filter result for position (u, v)
    
			// check range of (filter)inputImage index
            
            // add offset
            
            // check result
            
            // outputImage(u,v) = result value;
            
    // delete ?
    
};

/*=========================================================================
 *  Entry point to C MEX-file 
 *=========================================================================
 *  prhs: An array of right-hand input arguments
 *  plhs: An array of left-hand output arguments
 *  nrhs: The number of right-hand arguments, or the size of the prhs array
 *  nlhs: The number of left-hand arguments, or the size of the plhs array
 *=======================================================================*/
void mexFunction( int nlhs, mxArray* plhs[],
    int nrhs, const mxArray* prhs[]) 
{    
	
    // check paramters: nlhs, nrhs
        
    // check input: inputImage
    
	// check input: filter asymmetric   
	
	// check input: filtermatrix must be smaller than inputImage

    // check offset: uint8, complex
    
	// load offset = mxGetPr(prhs[1])[0];
    
	// check offset range
    
    // create output Image
	
	// Filter operation    
}