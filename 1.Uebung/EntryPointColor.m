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
function [imgout] = EntryPointColor( im )
    image = imread(im);

    % size: Größe der jeweiligen Dimension (592 X 470 X 3)
    [m, n, d] = size(image);

    if (d == 3)
                
        % zeros: Matrix mit m X n X d mit Nullen auffüllen.
        rotatedImage = uint8(zeros([m, n, d]));

        % Hole die einzelnen Seiten von image (Rot, Grün, Blau), drehe und setze sie
        % in rotatedImage
        rotatedImage(:,:,1) = EntryPoint(image(:,:,1));
        rotatedImage(:,:,2) = EntryPoint(image(:,:,2));
        rotatedImage(:,:,3) = EntryPoint(image(:,:,3));

        imgout = imagesc(rotatedImage);
    elseif (d == 1)
        imgout = EntryPoint(im);
    end
end