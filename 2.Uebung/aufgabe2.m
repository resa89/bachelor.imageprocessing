% -------------------------------------------------------------------------
%   Uebung 2, Di Martino, Stefano, 286021,
%   Semester 7, stemarti@htwg-konstanz.de, 8. April 2014
%
%   Uebung 2, Wilhelm, Andreas, 286297,
%   Semester 7, anwilhel@htwg-konstanz.de, 8. April 2014
%
%   Uebung 2, Kocher, Theresa, ,
%
% -------------------------------------------------------------------------

clear all;

mex myLut.cpp;
mex mxLut.cpp;

lut = [(50:177),(128:255)];

image = imread('bild1.jpg');

mxLutOut = mxLut(image, uint8(lut));
myLutOut = myLut(image);

colormap('gray');
subplot(2,2,1), subimage(image);
title('Original');
subplot(2,2,2), subimage(myLutOut);
title('myLut');
subplot(2,2,3), subimage(image);
title('Original');
subplot(2,2,4), subimage(mxLutOut);
title('mxLut');
truesize;