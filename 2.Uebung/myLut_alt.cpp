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

void mxLut(const mxArray* mxSource, unsigned char* dest);

void mexFunction( int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) 
{  
    int dims[2];
    
    // check paramters: nlhs, nrhs
    if (nlhs > 1 || nrhs != 1) {
		mexErrMsgTxt("Usage: lut = myLut(imIn)");
	}
    
    // check input: uint8
    if (!mxIsUint8(prhs[0]))
        mexErrMsgTxt("myLut: Image must be uint8");
    
    // input / output
   
    // create output array (mxUINT8_CLASS)
    dims[0] = numberIntensities;
    dims[1] = 1;
    
    plhs[0] = mxCreateNumericArray(2, dims, mxUINT8_CLASS, mxREAL);
    
    unsigned char* pDest = (unsigned char*) mxGetData(plhs[0]);
    
    // Lut operation
    mxLut(prhs[0], pDest);
}

void mxLut(const mxArray* mxSource, unsigned char* dest)
{
    unsigned char* source = (unsigned char*) mxGetData(mxSource);
    const int height = mxGetM(mxSource);
	const int width = mxGetN(mxSource);
    const int dimension = height * width;
    const int threshold = 16;
    const int threshold2 = 96;
    
    bool calculated[numberIntensities] = { false };
    int numberCalculated = 0;
    
    int oldIntensity;
    int newIntensity;
    
    for (int i = 0; i < dimension; i++) {
        oldIntensity = source[i];
        
        if (!calculated[oldIntensity]) {
            if (oldIntensity < threshold) {
                newIntensity = (oldIntensity + 1) * 2.5;
            } else if (oldIntensity < threshold2) {
                newIntensity = oldIntensity * 1.5;
            } else {
                newIntensity = oldIntensity;
            }
            
            if (newIntensity > (numberIntensities - 1)){
                newIntensity = numberIntensities - 1;
            }
            
            dest[oldIntensity] = newIntensity;
            calculated[oldIntensity] = true;
            
            numberCalculated++;
            
            if (numberCalculated == numberIntensities) {
                break;
            }
        }
    }
}