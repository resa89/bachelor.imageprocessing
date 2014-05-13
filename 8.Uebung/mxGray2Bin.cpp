#include "mex.h"

static int imageHeight;
static int imageWidth;

/*=========================================================================
 *  inImage:	Input Image (uint8)
 *  outImage:	Output Image(uint8)
 *	filter: 	matrix	
 *  number:     double value (uint8)
 *=======================================================================*/
void mxGray2Bin(const mxArray* mxInImage, mxArray* mxOutImage)
{
	// Get Pointer (inImage, outImage, matrix)
    unsigned char *inImage = (unsigned char*) mxGetData(mxInImage);
    unsigned char *outImage = (unsigned char*) mxGetData(mxOutImage);

    const int dimension = imageHeight * imageWidth;
    
    for (int i = 0; i < dimension; i++) {
        if (inImage[i] < 128)
            outImage[i] = 0;
        else
            outImage[i] = 1;
    }
};

/*=========================================================================
 *  Entry point to C MEX-file 
 *=========================================================================
 *  prhs: An array of right-hand input arguments
 *  plhs: An array of left-hand output arguments
 *  nrhs: The number of right-hand arguments, or the size of the prhs array
 *  nlhs: The number of left-hand arguments, or the size of the plhs array
 *=======================================================================*/
void mexFunction(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]) 
{    	
    // check paramters: nlhs, nrhs
        
    // check input: inputImage
    if (!mxIsUint8(prhs[0])) {
		mexErrMsgTxt("mxGray2Bin can only process UINT8.");
	}

	// check input: filtermatrix must be smaller than inputImage
    imageHeight = mxGetM(prhs[0]);
    imageWidth = mxGetN(prhs[0]);
    
    // create output Image
    plhs[0] = mxCreateLogicalMatrix(imageHeight, imageWidth);
    
	// Filter operation    
    mxGray2Bin(prhs[0], plhs[0]);
}