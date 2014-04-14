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

function [ output_args ] = mxCumHistogram( input_args )
%MXCUMHISTO Summary of this function goes here
%   Detailed explanation goes here

    mex mxCumHisto.cpp;
    bin = 1;
    image = uint8(imread(input_args));
    output_args = mxCumHisto(image, bin);

    area(output_args);

end

