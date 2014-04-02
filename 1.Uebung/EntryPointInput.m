% -------------------------------------------------------------------------
% Syntax: 
%   
%   imOut = EntryPoint(imIn)
%
%   Description: 
%       Entrypoint reprocess the input image. 
%   
%   Entrypoint(imIn) takes,    
%       imIn          input image (Eingangsbild), uint8
%    and returns,
%       imOut         output image (Ausgangsbild), uint8
%
%   Example:
%       imOut = EntryPoint('bild1.jpg');    
% -------------------------------------------------------------------------
%
%   Übung 1, Di Martino, Stefano, 286021,
%   Semester 7, stemarti@htwg-konstanz.de, 1. April 2014
%
%   Übung 1, Willhelm, Andreas, 286297,
%   Semester, anwilhel@htwg-konstanz.de, 1. April 2014
%
% -------------------------------------------------------------------------


function [imgout] = EntryPointInput( im )
    mex EntryPoint.cpp
    
    image = imread(im);
    [~, ~, d] = size(image);

    if (d == 1)
        colormap('gray');
        imgout = imagesc(EntryPoint(image));
    elseif(d == 3)
        imgout = EntryPointColor(im);
    end
end