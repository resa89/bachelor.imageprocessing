% -------------------------------------------------------------------------
%   Uebung 7, Di Martino, Stefano, 286021,
%   Semester 7, stemarti@htwg-konstanz.de, 20. Mai 2014
%
%   Uebung 7, Willhelm, Andreas, 286297,
%   Semester 7, anwilhel@htwg-konstanz.de, 20. Mai 2014
%
%   Uebung 7, Kocher, Theresa, 291235, 20. Mai 2014
%
% -------------------------------------------------------------------------

function Gray2Bin( imagePath )
    mex mxGray2Bin.cpp;
    
    originalImage = imread(imagePath);
    
    if (isa(originalImage, 'uint8'))
        binImage = mxGray2Bin(originalImage);

        colormap('gray');
        subplot(2,1,1), subimage(originalImage);
        title('Original');
        subplot(2,1,2), subimage(binImage);
        title('Binary');

        truesize;
    else
        error('Input is not a greycolor image');
    end
end