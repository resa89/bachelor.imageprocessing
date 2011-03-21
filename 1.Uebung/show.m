% ------------------------------------------------------------
% Syntax:     
%        
%   [] = show(im)
%
%   Description:     
%       show scale data and display as image.
%
%       show takes, 
%       im        is a string (path), im = 'bild1.jpg';
%
%   Example:
%       show('bild1.jpg');
% ------------------------------------------------------------
function [] = show( im )
    i = imread(im);
    [m, n, d] = size(i);
    imagesc(uint8(i));   
    if (d == 1)
        colormap(gray), axis image;
    end
end