#include "mex.h"
#include <string.h>
#include <math.h>
#include <stdlib.h>

/*=========================================================================
 *  Compiling und Linking
 *  Use     mex -setup  to select a C++ compiler, then tpye:
 *          mex filename.cpp
 *=======================================================================*/
    //unsigned char *copyImage = new unsigned char[imageHeight * imageWidth];

enum edge
{
    MIN,
    MAX,
    CONTINUE,
    MIRROR
};

static int imageHeight;
static int imageWidth;
static int imageDimension;

static int filterHeight;
static int filterWidth;

static enum edge status;

void borderMirrorFilter(unsigned char* bufferMatrix, unsigned char* inImage, int bufHeight, int bufWidth) {
    const int filterHotspot = filterHeight / 2;
    
    for(int w = 0; w < imageWidth; ++w) {
        for(int h = 0; h < imageHeight; ++h) {
            
            // linke obere ecke
            if(w == 0 && h == 0) {
                int l = filterHotspot-1;
                int m = filterHotspot-1;

                for(int j = 0; j < filterHotspot; j++) {
                    m = filterHotspot-1;
                    for(int k = 0; k < filterHotspot; k++) {
                        bufferMatrix[(w + j) * bufHeight + k] = inImage[(w + l) * imageHeight + m];

                        m--;
                    }
                    l--;
                }
            }
            
            // linke untere ecke
            if(w == 0  && h == imageHeight - 1) {
                int l = filterHotspot;
                int m = 0;

                for(int j = 0; j < filterHotspot; j++) {
                    m = 0;
                    for(int k = 1; k <= filterHotspot; k++) {
                        bufferMatrix[(w + j) * bufHeight + h + filterHotspot + k] 
                                = inImage[l * imageHeight - 1 - m];
                        m++;
                    }
                    l--;
                }
            }

            // rechte obere ecke
            if(w == imageWidth -1  && h == 0) {
                int l = filterHotspot-1;
                int m = filterHotspot-1;

                for(int j = 1; j <= filterHotspot; j++) {
                    m = filterHotspot-1;
                    for(int k = 0; k < filterHotspot; k++) {
                        bufferMatrix[(w + filterHotspot + j) * bufHeight + k] = inImage[(w - k) * imageHeight + m];

                        m--;
                    }
                    l--;
                }
            }

            // rechte untere ecke
            if(w == imageWidth -1  && h == imageHeight - 1) {
                int l = 0;
                int m = 0;
                
                for(int j = 1; j <= filterHotspot; j++) {
                    m = 0;
                    
                    for(int k = 1; k <= filterHotspot; k++) {
                        bufferMatrix[(w + filterHotspot + j) * bufHeight + h + filterHotspot + k] = inImage[(imageWidth - l) * imageHeight - 1 - m];
                        m++;

                    }
                    l++;
                }
            }

            //linker rand
            if(w == 0) {   
                int k = filterHotspot - 1;
                
                for(int j = 0; j < filterHotspot; j++) {
                    bufferMatrix[(w + j) * bufHeight + h + filterHotspot] = inImage[(w + k) * imageHeight + h];
                    k--;
                }
            }

            //oberer rand
            if(h == 0) {
                int k = filterHotspot - 1;

                for(int j = 0; j < filterHotspot; j++) {
                    bufferMatrix[(w + filterHotspot) * bufHeight + h  + j] = inImage[w  * imageHeight + k];
                    k--;
                }
            }

            //rechter rand
            if(w == imageWidth - 1) {
                int k = 0;

                for(int j = 1; j <= filterHotspot; j++) {
                    bufferMatrix[(w + filterHotspot + j) * bufHeight + h + filterHotspot] = inImage[(w - k) * imageHeight + h];
                    k++;
                }

            }

            //unterer rand
            if(h == imageHeight - 1) {   
                int k = 0;

                for(int j = 1; j <= filterHotspot; j++) {
                    bufferMatrix[(w + filterHotspot) * bufHeight + h + filterHotspot + j]
                        = inImage[w * imageHeight + h - k];
                    k++;
                }
            }
        }
    }
}

void borderContinueFilter(unsigned char *bufferMatrix, unsigned char *inImage, int bufHeight, int bufWidth) {
	const int filterHotspot = filterHeight / 2;
	int bufDimension = bufHeight * bufWidth;
	
	//linker und rechter Rand
	for (int w = 0; w < filterHotspot; w++) {
		for (int h = filterHotspot; h < imageHeight + filterHotspot; h++) {
			bufferMatrix[w * bufHeight + h] = inImage[h];
			bufferMatrix[bufDimension - ((w + 1) * bufHeight) + 1 + h] = inImage[imageDimension - imageHeight - filterHotspot + 1 + h];
		}
	}
	//oberer und unterer Rand
	for (int w = filterHotspot; w < imageWidth + filterHotspot; w++) {
		for (int h = 0; h < filterHotspot; h++) {
			bufferMatrix[w * bufHeight + h] = inImage[w * imageHeight];
			bufferMatrix[w * bufHeight + bufHeight - 1 - h] = inImage[w * imageHeight + imageHeight - 1];
		}
	}
	//Ecken
	for (int w = 0; w < filterHotspot; w++) {
		for (int h = 0; h < filterHotspot; h++) {
			//links oben
			bufferMatrix[w * bufHeight + h] = inImage[0];
			//links unten
			bufferMatrix[((w + 1) * bufHeight) - 1 - h] = inImage[imageHeight - 1];
			//rechts oben
			bufferMatrix[bufDimension - ((w + 1) * bufHeight) + 1 + h] = inImage[imageDimension - imageHeight + 1];
			//rechts unten
			bufferMatrix[bufDimension - (w * bufHeight) - h] = inImage[imageDimension];
		}
	}
}

/*=========================================================================
 *  inImage:	Input Image (uint8)
 *  outImage:	Output Image(uint8)
 *	filter: 	matrix (double)
 *  offset:     value (uint8)
 *=======================================================================*/
void mxFilter(const mxArray* mxInImage, mxArray* mxOutImage, const mxArray* mxFilter, double offset)
{    
	// Get Pointer (inImage, outImage, matrix)
    unsigned char *inImage = (unsigned char*) mxGetData(mxInImage);
    unsigned char *outImage = (unsigned char*) mxGetData(mxOutImage);
    double *filter = (double*) mxGetPr(mxFilter);

    int dims[2];
    int bufHeight, bufWidth;
    unsigned char *bufferMatrix;
    
	// center of filter
    const int filterHotspot = filterHeight / 2;
    
    mexPrintf("imageHeight: %d, width: %d\n", imageHeight, imageWidth);
    dims[0] = bufHeight = imageHeight + (2 * filterHotspot);
	dims[1] = bufWidth = imageWidth + (2 * filterHotspot);
    bufferMatrix = (unsigned char*) mxGetData(mxCreateNumericArray(2, dims, mxUINT8_CLASS, mxREAL));
    int bufDimension = bufHeight * bufWidth;
	
	//set bufferMatrix for MIN-Filter and MAX-Filter
    if(status == MIN) {
		memset(bufferMatrix, 0, bufDimension);
    }
    else if(status == MAX) {
        memset(bufferMatrix, 255, bufDimension);
    }
	
	//copy-overwrite InImage into bufferMatrix
	for (int w = 0; w < imageWidth; w++) {
		for (int h = 0; h < imageHeight; h++) {
			bufferMatrix[(w + filterHotspot) * bufHeight + h + filterHotspot] = inImage[w * imageHeight + h];
		}
	}
	
	//MIRROR-Filter
	if(status == MIRROR) {
		borderMirrorFilter(bufferMatrix, inImage, bufHeight, bufWidth);
    }
	
	//CONTINUE-Filter
	if(status == CONTINUE) {
		borderContinueFilter(bufferMatrix, inImage, bufHeight, bufWidth);
    }

    double sum;
	for (int w = filterHotspot; w < bufWidth - filterHotspot; w++) {
        for (int h = filterHotspot; h < bufHeight - filterHotspot; h++) {
            // compute filter result for position (u, v)
            sum = 0.0;
            
            for (int j= -filterHotspot; j <= filterHotspot; j++) {
                for (int i = -filterHotspot; i <= filterHotspot; i++) {
                    int imageValue = bufferMatrix[(h + i) + ((w + j) * bufHeight)];
                    double filterCoefficient = filter[(i + filterHotspot) + (j + filterHotspot) * filterHeight];
                    sum += filterCoefficient * imageValue;
                }
            }
            
            sum += offset;
            
            int newValue = (int) sum + 0.5;
            if (newValue < 0) newValue = 0;
            if (newValue > 255) newValue = 255;
            outImage[(w - filterHotspot) * imageHeight + h - filterHotspot] = newValue;
        }
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
void mexFunction( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]) 
{    
    // check input: filter asymmetric   
    filterHeight = mxGetM(prhs[1]);
    filterWidth = mxGetN(prhs[1]);
    
    if (filterHeight != filterWidth || filterWidth % 2 == 0) {
        mexErrMsgTxt("mxFilter: filter matrix must be symmetric and odd!");
    }
    
    // check input: inputImage
    if (!mxIsUint8(prhs[0])) {
       mexErrMsgTxt("mxFilter: Image must be uint8");
    }
    
    imageHeight = mxGetM(prhs[0]);
    imageWidth = mxGetN(prhs[0]);
	imageDimension = imageHeight * imageWidth;
	
	// check input: filtermatrix must be smaller than inputImage
    if (filterHeight > imageHeight || filterWidth > imageWidth) {
        mexErrMsgTxt("mxFilter: filter matrix must be smaller than image");
    }

    // check offset: uint8, complex
    if (!mxIsUint8(prhs[2])) {
        mexErrMsgTxt("mxFilter: offset must be unint8");
    }
    
	// load offset = mxGetPr(prhs[1])[0];
    const int offset = ((unsigned char*) mxGetData(prhs[2]))[0];
    
	// check offset range
    if (offset < 0 || offset > 150) {
        mexErrMsgTxt("mxFilter: offset must be between 0 and 150");
    }
    
    mexPrintf("offset: %d\n", offset);
    
    const int stringSize = mxGetN(prhs[3]) + 1;
    char *edge = (char*) malloc(stringSize * sizeof(char));
    
    mxGetString(prhs[3], edge, stringSize);
    
    if (strncmp("min", edge, strlen("min") + 1) == 0) {
        status = MIN; mexPrintf("min!\n");
    } else if (strncmp("max", edge, strlen("max") + 1) == 0) {
        status = MAX; mexPrintf("max!\n");
    } else if (strncmp("mirror", edge, strlen("mirror") + 1) == 0) {
        status = MIRROR; mexPrintf("mirror!\n");
    } else if (strncmp("continue", edge, strlen("continue") + 1) == 0) {
        status = CONTINUE; mexPrintf("continue!\n");
    }
	
    // create output Image
    const int dims[2] = { imageHeight, imageWidth };
	plhs[0] = mxCreateNumericArray(2, dims, mxUINT8_CLASS, mxREAL);
	
	// Filter operation
    mxFilter(prhs[0], plhs[0], prhs[1], offset);
    
    //delete
    free(edge);
}