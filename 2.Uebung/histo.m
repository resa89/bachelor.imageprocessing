% -------------------------------------------------------------------------
%   Übung 2, Di Martino, Stefano, 286021,
%   Semester 7, stemarti@htwg-konstanz.de, 8. April 2014
%
%   Übung 2, Willhelm, Andreas, 286297,
%   Semester, anwilhel@htwg-konstanz.de, 8. April 2014
% -------------------------------------------------------------------------

clear all;
!del mxHisto.mexw64

mex mxHisto.cpp;
bin = 32;
image = uint8(imread('bild1.jpg'));
histogram = mxHisto(image, bin);

area(histogram);