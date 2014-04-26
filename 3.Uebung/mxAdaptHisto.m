% -------------------------------------------------------------------------
%   Uebung 3, Di Martino, Stefano, 286021,
%   Semester 7, stemarti@htwg-konstanz.de, 15. April 2014
%
%   Uebung 3, Willhelm, Andreas, 286297,
%   Semester, anwilhel@htwg-konstanz.de, 15. April 2014
%
%   Uebung 3, Kocher, Theresa,
%
% -------------------------------------------------------------------------

function [ adaptHist ] = mxAdaptHisto( refInput, origInput )
    mex mxHistoAdapt.cpp;
    mex mxHisto.cpp;
    mex mxCumHisto.cpp;
    mex mxLut.cpp;

    bin = 1;

    refImage = uint8(imread(refInput));
    origImage = uint8(imread(origInput));
    refHist = mxHisto(refImage, bin);
    origHist = mxHisto(origImage, bin);

    adaptHist = mxHistoAdapt(refHist, origHist);
    adaptImage = mxLut(origImage, uint8(adaptHist));

    colormap('gray');
    subplot(2,3,1), image(refImage);
    title('refImage');
    subplot(2,3,2), image(origImage);
    title('origImage');
    subplot(2,3,3), image(adaptImage);
    title('adaptImage');
    subplot(2,3,4), area(mxCumHisto(refImage,1));
    title('refHisto');
    subplot(2,3,5), area(mxCumHisto(origImage,1));
    title('origHisto');
    subplot(2,3,6), area(mxCumHisto(adaptImage,1));
    title('adaptHisto');
end