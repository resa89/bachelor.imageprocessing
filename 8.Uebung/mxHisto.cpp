#include "mex.h"

void mxHisto(const mxArray* source, mxArray* dest, int bin);

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
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) 
{
    const int bitDepth = 256; // number of max intensity values    
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
    
	bin = mxGetPr(prhs[1])[0];
    dims[0] = binHeight * binWidth; // height
    dims[1] = bitDepth / bin; // width
    
	// check bin: 1 <= bin <= 256
    if (!(1 < bin < bitDepth))
        mexErrMsgTxt("Bin size must be between 1 and 256");
    
    
    // input / output
    
    // create output array
    // output
	plhs[0] = mxCreateNumericArray(2, dims, mxUINT32_CLASS, mxREAL);
	
	// create histogram: mxHisto(...);
    mxHisto(prhs[0], plhs[0], bin);    
}

void mxHisto(const mxArray* source, mxArray* dest, int bin)
{
    const int bitDepth = 256; // number of max intensity values    
    //get dimensions of image
    const int height = mxGetM(source);
	const int width = mxGetN(source);
    const int dimension = height * width;
    int newIntensity;
    
	unsigned char *pSource = (unsigned char*) mxGetData(source);
    unsigned int *pDest = (unsigned int*) mxGetData(dest);
    
    for (int i = 0; i < dimension; i++) {
        newIntensity = pSource[i] / bin; // integer operations only!
        pDest[newIntensity]++;
    }
}