#include "mex.h"
#include <math.h>

#define PI 3.14159265

/*=========================================================================
 *  inImage:        Input Image (uint8)
 *  houghArray:     double[][]
 *	angleSteps:     double value
 *  radiusSteps:    double value
 *=======================================================================*/
void mxLinearHT(const mxArray* inImage, mxArray* houghArray, 
        double angleSteps, double radiusSteps)
{   
    
    // mrows & ncols
    
    // x/y-coordinate of image center    
    
    // stepsize of angle and radius
    
    // get inputImage
    
    // get houghArray
        
    // initiate array[][] = 0
    
    // fill houghArray

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
    
	// check input: angleSteps - double, complex

	// check input: radiusSteps - double, complex
    
	// load angleSteps, radiusSteps    

	// check angleSteps, radiusSteps: (steps < 1) => 256    

    // create output: houghArray 	

	// houghtransformation operation
    
}