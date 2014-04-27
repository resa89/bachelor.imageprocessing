% -------------------------------------------------------------------------
%   Uebung 4, Di Martino, Stefano, 286021,
%   Semester 7, stemarti@htwg-konstanz.de, 29. April 2014
%
%   Uebung 4, Willhelm, Andreas, 286297,
%   Semester 7, anwilhel@htwg-konstanz.de, 29. April 2014
%
%   Uebung 4, Kocher, Theresa, 291235
%
% -------------------------------------------------------------------------

function medianFilter( imageFile )
    mex mxMedianFilter.cpp;
    mex mxHisto.cpp;
    
    filter3 = [ 1 2 1; 2 3 2; 1 2 1] ./ 15;
    
    filter9 = ones(9, 9) ./ 81;
    
	filter5 = ones(5, 5) ./ 25;
    filter7 = ones(7, 7) ./ 49;
    filter51 = ones(51, 51) ./ 2601;
    
    filterBox5 = [0 0 0 0 0; 0 1 1 1 0; 0 1 1 1 0; 0 1 1 1 0; 0 0 0 0 0] ./ 25;
    filterGaus5 = [0 1 2 1 0; 1 3 5 3 1; 2 5 9 5 2; 1 3 5 3 1; 0 1 2 1 0] ./ 25;
    
    originalImage = imread(imageFile);
    imageFiltered = mxMedianFilter(originalImage, filter9, uint8(0));
    imagesc(imageFiltered);
    
    origHistogram = mxHisto(originalImage, 1);
    filteredHistogram = mxHisto(imageFiltered, 1);
    
    colormap('gray');
    subplot(2,2,1), subimage(originalImage);
    title('Original');
    subplot(2,2,2), subimage(imageFiltered);
    title('Filtered');
    subplot(2,2,3), area(origHistogram);
    title('Original Histogram');
    subplot(2,2,4), area(filteredHistogram);
    title('Filtered Histogram');
    
    truesize;
end