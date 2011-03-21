% -------------------------------------------------------------------------
% Syntax:     
%        
%   [] = showImage(im)
%
%   Description:     
%       showImage scale data and display as image.
%
%       showImage takes,
%       im        is a uint8 image
%
%   Example:
%       showImage(im);
% -------------------------------------------------------------------------
function [ ] = showImage( im )
    [m, n, d] = size(im);
    imagesc(uint8(im));   
    if (d == 1)
        colormap(gray), axis image;
    end
end