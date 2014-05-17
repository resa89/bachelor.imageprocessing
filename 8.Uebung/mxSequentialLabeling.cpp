#include "mex.h"
#include <vector>
#include <utility> // std::pair
#include <map>
#include <set>
#include <string.h> // memcpy
    
using namespace std;

typedef unsigned char Label;
typedef unsigned char Color;
typedef pair<Label, Label> Collision; 

static int imageHeight;
static int imageWidth;
static int dimension;

static bool withinImageBoundaries(const int w, const int h)
{
    return 0 <= w && w < imageWidth && 0 <= h && h < imageHeight;
}

static void setLabelOfNeighbours(unsigned char *outImage, const int w, const int h, set<Label> &neighbours)
{
    int currentW, currentH;
    
    // N1
    currentW = w - 1;
    currentH = h;
    
    if (withinImageBoundaries(currentW, currentH)) {
        if (outImage[currentW * imageHeight + currentH] > 1) {
            neighbours.insert(outImage[currentW * imageHeight + currentH]);
        }
    }
    
    // N2
    currentW = w - 1;
    currentH = h - 1;
    
    if (withinImageBoundaries(currentW, currentH)) {
        if (outImage[currentW * imageHeight + currentH] > 1) {
            neighbours.insert(outImage[currentW * imageHeight + currentH]);
        }
    }
    
    // N3
    currentW = w;
    currentH = h - 1;
    
    if (withinImageBoundaries(currentW, currentH)) {
        if (outImage[currentW * imageHeight + currentH] > 1) {
            neighbours.insert(outImage[currentW * imageHeight + currentH]);
        }
    }
    
    // N4
    currentW = w + 1;
    currentH = h - 1;
    
    if (withinImageBoundaries(currentW, currentH)) {
        if (outImage[currentW * imageHeight + currentH] > 1) {
            neighbours.insert(outImage[currentW * imageHeight + currentH]);
        }
    }
}

static vector< set<Label> >::iterator getLabelSet(vector< set<Label> >& labelsInRegions, Label labelToBeSearched)
{   
    for (vector< set<Label> >::iterator itLabelsInRegion = labelsInRegions.begin(); itLabelsInRegion != labelsInRegions.end(); itLabelsInRegion++) {    
        set<Label>& labels = *itLabelsInRegion;

        for (set<Label>::iterator it = labels.begin(); it != labels.end(); it++) {
            Label label = *it;
            
            if (label == labelToBeSearched) {
                return itLabelsInRegion;
            }
        }
    }
    
    char errorMsg[90];
    sprintf(errorMsg, "mxSequentialLabeling.cpp: label %u not found in function getLabelSet()", labelToBeSearched);
    mexErrMsgTxt(errorMsg);
}

static map<Label, Color> getColorForRegions(vector< set<Label> >& labelsInRegions)
{
    map<Label, Color> colorForRegions;
    vector< set<Label> >::iterator itRegions;
    
    const unsigned char regionNumber = labelsInRegions.size();
    const Color colorGapBetweenRegions = 255 / regionNumber;
    unsigned char regionCounter = 1;
    
    for (itRegions = labelsInRegions.begin(); itRegions != labelsInRegions.end(); itRegions++) {    
        set<Label> labels = *itRegions;
        
        // map all labels to one color
        for (set<Label>::iterator itLabels = labels.begin(); itLabels != labels.end(); itLabels++) {
            colorForRegions[*itLabels] = regionCounter * colorGapBetweenRegions;
        }
        
        regionCounter++;
    }
    
    return colorForRegions;
}

// Step 3
static void relabelImage(unsigned char *outImage, vector< set<Label> >& labelsInRegions)
{
    mexPrintf("%d regions\n", labelsInRegions.size());
    
    map<Label, Color> colorForRegions = getColorForRegions(labelsInRegions);
    
    for (int i = 0; i < dimension; i++) {
        Label label = outImage[i];
        
        if (label > 1) {
            outImage[i] = colorForRegions[label];
        }
    }
}

// Step 2
static vector< set<Label> > resolveLabelCollisions(vector<Collision>& collisions, const unsigned char numberOfLabels, const Label labelBegin)
{
    vector< set<Label> > labelsInRegions;
    
    // Create a partitioning of the labels as a vector of sets, one set for each label
    for (int label = labelBegin; label < numberOfLabels; label++) {
        set<Label> labelSet;
        labelSet.insert(label);
        
        labelsInRegions.push_back(labelSet);
    }
    
    for (int i = 0; i < collisions.size(); i++) {
        Collision collision = collisions[i];
        
        // Get the label set that contains A
        set<Label>& labelSetA = *getLabelSet(labelsInRegions, collision.first);
        
        // Get the label set that contains B
        vector< set<Label> >::iterator itLabelSetB = getLabelSet(labelsInRegions, collision.second);
        set<Label>& labelSetB = *itLabelSetB;
        
        // Are they different sets?
        if (labelSetA != labelSetB) {
            // Union of labelSetA and labelSetB.
            labelSetA.insert(labelSetB.begin(), labelSetB.end());

            // Delete labelSetB
            labelsInRegions.erase(itLabelSetB);
        }
    }
    
    return labelsInRegions;
}

// Step 1
static void mxSequentialLabeling(const mxArray* mxInImage, mxArray* mxOutImage)
{
	// Get Pointer (inImage, outImage)
    unsigned char *inImage = (unsigned char*) mxGetData(mxInImage);
    unsigned char *outImage = (unsigned char*) mxGetData(mxOutImage);

    Collision collision;
    vector<Collision> collisions;
    
    const Label labelBegin = 2;
    Label currentLabel = labelBegin;
    
    memcpy(outImage, inImage, dimension);

    for (int h = 0; h < imageHeight; h++) {
        for (int w = 0; w < imageWidth; w++) {
			if (outImage[w * imageHeight + h] == 1) {
                set<Label> neighbours;
                setLabelOfNeighbours(outImage, w, h, neighbours);
                
                const int numberOfNeighbours = neighbours.size();
                
                if (numberOfNeighbours == 0) {
                    outImage[w * imageHeight + h] = currentLabel;
                    currentLabel++;
                } else if (numberOfNeighbours == 1) {
                    set<Label>::iterator it = neighbours.begin();
                    
                    // Assign the first element
                    outImage[w * imageHeight + h] = *it;
                } else if (numberOfNeighbours > 1) {
                    set<Label>::iterator it = neighbours.begin();
                    
                    // First element is the new label
                    Label newLabel = *it;
                    it++;
                    
                    // Assign the new label
                    outImage[w * imageHeight + h] = newLabel;
                    
                    // register collisions
                    for (; it != neighbours.end(); it++) {
                        collision.first = *it;
                        collision.second = newLabel;
                        
                        collisions.push_back(collision);
                    }
                }
            }
		}
    }
    
    vector< set<Label> > labelsInRegions = resolveLabelCollisions(collisions, currentLabel, labelBegin);
    relabelImage(outImage, labelsInRegions);
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
    if (!mxIsLogical(prhs[0])) {
		mexErrMsgTxt("mxSequentialLabeling.cpp can only process logical arrays.");
	}

    imageHeight = mxGetM(prhs[0]);
    imageWidth = mxGetN(prhs[0]);
    dimension = imageWidth * imageHeight;
    
    // create output Image
    const int dims[2] = { imageHeight, imageWidth };
    plhs[0] = mxCreateNumericArray(2, dims, mxUINT8_CLASS, mxREAL);
    
	// Filter operation    
    mxSequentialLabeling(prhs[0], plhs[0]);
}