#include <math.h>
#include "mex.h"

void adaptHisto(const mxArray* refHisto, const mxArray* adaptHisto, 
                    mxArray* adaptLUT)
{    
    
    //(ref and adapt), obtain the number of pixel elements    
    
    // normalize histogram values, and create normHisto
    
	// CDFSum, compute cumulative distribution function   

    // compute look-up table

    // delete ?
}

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{    
    int dims[2];
    
	// check: nlhs ,nrhs
    
    // check Image: 8 bit
	
    // check: similar dimension ?
  
    // create output
      
	// adapt Histo ?    
    // adaptHisto(prhs[0], prhs[1], plhs[0]);    

}