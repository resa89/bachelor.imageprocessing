#include "mex.h"
#include <algorithm>

/*=========================================================================
 *  Compiling und Linking
 *  Use     mex -setup  to select a C++ compiler, then tpye:
 *          mex filename.cpp
 *=======================================================================*/



static int imageHeight;
static int imageWidth;
static int imageDimension;

static int filterHeight;
static int filterWidth;

/*=========================================================================
 *  n:		length of array
 *  data:	array
 *=======================================================================*/
void heapSort(int n, int data[])
{
    std::sort_heap(data, data + n);
}

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

/*=========================================================================
 *  inImage:	Input Image (uint8)
 *  outImage:	Output Image(uint8)
 *	filter: 	matrix	
 *  offset:     double value (uint8)
 *=======================================================================*/
void mxFilter(const mxArray* mxInImage, mxArray* mxOutImage, const mxArray* mxFilter, double offset) {    
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
	
	//copy-overwrite InImage into bufferMatrix
	for (int w = 0; w < imageWidth; w++) {
		for (int h = 0; h < imageHeight; h++) {
			bufferMatrix[(w + filterHotspot) * bufHeight + h + filterHotspot] = inImage[w * imageHeight + h];
		}
	}

    borderMirrorFilter(bufferMatrix, inImage, bufHeight, bufWidth);
    const int filterDimension = filterHeight * filterWidth;
    const int filterCenter = filterDimension / 2;
    int *region = new int[filterDimension];
    
	for (int w = filterHotspot; w < bufWidth - filterHotspot; w++) {
        for (int h = filterHotspot; h < bufHeight - filterHotspot; h++) {
            
            int k = 0;
            
            for (int j= -filterHotspot; j <= filterHotspot; j++) {
                for (int i = -filterHotspot; i <= filterHotspot; i++) {
                    region[k] = bufferMatrix[(h + i) + ((w + j) * bufHeight)];
                    k++;
                }
            }
            
            heapSort(filterDimension, region);
            
            outImage[(w - filterHotspot) * imageHeight + h - filterHotspot] = region[filterCenter];
        }
    }


    delete[] region;

    // Image size

	// Filter size

	// Get Pointer (inImage, outImage, matrix)

	// define center of filter
    
    // copy Image;    
    
    // To Do: Medianfilter

	// heapsort

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
	
    // create output Image
    const int dims[2] = { imageHeight, imageWidth };
	plhs[0] = mxCreateNumericArray(2, dims, mxUINT8_CLASS, mxREAL);

	// Filter operation
    mxFilter(prhs[0], plhs[0], prhs[1], offset);
}