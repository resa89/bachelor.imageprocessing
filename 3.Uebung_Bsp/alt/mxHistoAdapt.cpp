#include <math.h>
#include "mex.h"

void adaptHisto(const mxArray* refHisto, const mxArray* adaptHisto, 
                    mxArray* adaptLUT)
{    
    unsigned int length = mxGetN(adaptHisto);
    const double* ref = mxGetPr(refHisto);
    const double* adapt = mxGetPr(adaptHisto);
    double* lut = mxGetPr(adaptLUT);
    double tempRef = 0.0;
    double tempAdapt = 0.0;
    
    unsigned int i;
    unsigned int j;
	double* nRefHisto;
    double* nAdaptHisto;
    
    // sum of histoData (ref and adaptHisto)    
    for (i = 0; i < length; ++i)
    {
        tempRef += ref[i];
        tempAdapt += adapt[i];
    }
    
    // normalize histo + create normHisto
    nRefHisto = new double[length];
    nAdaptHisto = new double[length];
    
    for (i = 0; i < length; ++i)
    {
        nRefHisto[i] = ref[i] / tempRef;
        nAdaptHisto[i] = adapt[i] / tempAdapt;
    }   
    
	// CDFSum    
    for (i = 1; i < length; ++i)
    {
        nRefHisto[i] = nRefHisto[i-1] + nRefHisto[i];
        nAdaptHisto[i] = nAdaptHisto[i-1] + nAdaptHisto[i];
    }
    
    // LUT (easy)
    j = 0;
    i = 0;
    while (i < length && j < length)      
    {
        if (nRefHisto[j] >= nAdaptHisto[i])
        {
           lut[i] = j;                           
           ++i;
        }
        else 
            ++j;
    }
	while (i < length)
	{
		lut[i] = j;
		++i;
	}
        
	// delete
    delete[] nRefHisto;
    delete[] nAdaptHisto;
}

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{    
    int dims[2];
    
	// check: nlhs ,nrhs
    if (nlhs > 1 || nrhs != 2)
        mexErrMsgTxt("using: lut = mxHistoAdapt(HistoRef, HistoAdapt);");
    
    // check Image: 8 bit
    if (!mxIsDouble(prhs[0]) || !mxIsDouble(prhs[1]))
        mexErrMsgTxt("Histogram data must be double!");
	
    // check: similar dimension
    if (mxGetN(prhs[0]) != mxGetN(prhs[1])
            && mxGetM(prhs[0]) != mxGetM(prhs[1]))
        mexErrMsgTxt("Histograms have different dimension!");
  
    // create output
    dims[0] = mxGetM(prhs[0]);
    dims[1] = mxGetN(prhs[0]);
    plhs[0] = mxCreateNumericArray(2, dims, mxDOUBLE_CLASS, mxREAL);
      
	// adapt Histo
    adaptHisto(prhs[0], prhs[1], plhs[0]);    
}