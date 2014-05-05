#include "mex.h"
#include <math.h>

#define PI 3.14159265

static int imageHeight;
static int imageWidth;
static int imageDimension;
static int hCenter;
static int wCenter;

static int nAng, nRad;
static double dAng, dRad;

void doPixel(int w, int h, unsigned char *houghArray) {
	int x = w - wCenter;
	int y = h - hCenter;
	for (int a = 0; a < nAng; a++) {
		double theta = dAng * a;
		int r = (int) (((x * cos(theta) + y * sin(theta)) / dRad) + nRad/2);
		if (r >= 0 && r < nRad) {
			houghArray[a * nAng + r]++;
		}
	}
}


/*=========================================================================
 *  inImage:        Input Image (uint8)
 *  houghArray:     double[][]
 *	angleSteps:     double value
 *  radiusSteps:    double value
 *=======================================================================*/
void mxLinearHT(const mxArray* mxInImage, mxArray* mxHoughArray, int offset)
{   
	unsigned char *inImage = (unsigned char*) mxGetData(mxInImage);
    unsigned char *houghArray = (unsigned char*) mxGetPr(mxHoughArray);

    // fill houghArray
	for (int h = 0; h < imageHeight; h++) {
		for (int w = 0; w < imageWidth; w++) {
			if (inImage[w * imageHeight + h] > 0) {
				doPixel(w, h, houghArray);
			}
		}
	}
	
	//treshold operation
	for (int h = 0; h < nAng; h++) {
		for (int w = 0; w < nRad; w++) {
			if (houghArray[w * nAng + h] < offset) {
				houghArray[w * nAng + h] = 0;
			}
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
void mexFunction( int nlhs, mxArray* plhs[],
    int nrhs, const mxArray* prhs[]) 
{    
	double angleSteps, radiusSteps;
	int offset;
    // check paramters: nlhs, nrhs
    if (nlhs != 1) {
        mexErrMsgTxt("mxFilter: nlhs (Output-Arg)must be 1");
    }
	if (nrhs != 4) {
        mexErrMsgTxt("mxFilter: nrhs (Input-Args) must be over 3");
    }
	
    // check input: inputImage    
    if (!mxIsLogical(prhs[0])) {
       mexErrMsgTxt("mxFilter: Image must be uint8");
    }
    // imageHeight & imageWidth
    imageHeight = mxGetM(prhs[0]);
    imageWidth = mxGetN(prhs[0]);
	imageDimension = imageHeight * imageWidth;
	
	// x/y-coordinate of image center    
    hCenter = imageHeight / 2;
	wCenter = imageWidth / 2;
	
	// check input: angleSteps - double, complex
	if (!mxIsDouble(prhs[1]))
        mexErrMsgTxt("mxLinearHT: angleSteps must be double");

	// check input: radiusSteps - double, complex
    if (!mxIsDouble(prhs[2]))
        mexErrMsgTxt("mxLinearHT: radiusSteps must be double");
    
	// check offset
    if (!mxIsUint8(prhs[3]))
        mexErrMsgTxt("mxLinearHT: offset must be Uint8");

	// load angleSteps, radiusSteps, offset
    angleSteps = ((double*) mxGetPr(prhs[1]))[0];
    radiusSteps = ((double*) mxGetPr(prhs[2]))[0];
    offset = ((int*) mxGetData(prhs[3]))[0];
	
	// check angleSteps, radiusSteps, offset: (steps < 1) => 256    
    if (angleSteps < 1 || angleSteps > 256) {
        mexErrMsgTxt("mxFilter: angleSteps must be between 1 and 256");
    }
    if (radiusSteps < 1 || radiusSteps > 256) {
        mexErrMsgTxt("mxFilter: radiusSteps must be between 1 and 256");
    }
	if (offset < 0 || offset > 256) {
        mexErrMsgTxt("mxFilter: offset must be between 0 and 256");
    }
    // stepsize of angle and radius
	nAng = angleSteps;
	nRad = radiusSteps;
    dAng = (PI/angleSteps);
	double rMax = sqrt((double) (wCenter * wCenter + hCenter * hCenter));
	dRad = (2*rMax)/radiusSteps;

	// create output: houghArray 	
    const int dims[2] = { nAng, nRad };
	plhs[0] = mxCreateNumericArray(2, dims, mxUINT8_CLASS, mxREAL);
	
	// houghtransformation operation
    mxLinearHT(prhs[0], plhs[0], offset);
}