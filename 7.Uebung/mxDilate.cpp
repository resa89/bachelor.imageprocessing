#include "mex.h"

/*=========================================================================
 *  inImage:	Input Image (uint8)
 *  outImage:	Output Image(uint8)
 *	filter: 	matrix	
 *  number:     double value (uint8)
 *=======================================================================*/
void mxDilate(const mxArray* inImage, mxArray* outImage, 
        const mxArray* matrix, double number)
{    
    // Image size

    // Filter size

	// Get Pointer (inImage, outImage, matrix)

	// define center of filter
    
    // copy Image;    
    
    // To Do: Gray - Dilate (Maximum):
	// ****************************************//
    // check range of (filter)inputImage index
    // Maximumfilter                    
    // check max
    // outputImage(u,v) = result value;
	// ****************************************//
    
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

   	// load number = mxGetPr(prhs[2])[0];
    
	// check number   

    // create output Image

	// Filter operation    
    
}