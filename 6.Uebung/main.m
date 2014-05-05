% -------------------------------------------------------------------------
%   Uebung 6, Di Martino, Stefano, 286021,
%   Semester 7, stemarti@htwg-konstanz.de, 6. Mai 2014
%
%   Uebung 6, Willhelm, Andreas, 286297,
%   Semester 7, anwilhel@htwg-konstanz.de, 6. Mai 2014
%
%   Uebung 6, Kocher, Theresa, 291235
%
% -------------------------------------------------------------------------

function main()
    close all;
    
    %im = imread('cactus.jpg'); % canny
    %im = imread('fhorn.jpg'); % canny
    im = imread('bild1.jpg'); % zerocross
    [m n d] = size(im);
    
    if (d == 3)
        im = color2gray(im);
    end
    
    angle_steps = 256;
    radius_steps = 256;
    %im_edge = edge(im, 'canny', [0.1 0.2], 3); % extract edges
    im_edge = edge(im, 'zerocross', [4 -1], 2); % roberts, log, zerocross

    out = mxLinearHT(im_edge, angle_steps, radius_steps, uint8(90));    
    max_out = max(max(out));
    out = double(out) ./ double(max_out);
    out = out * 255;

    out = 255 - out;        % invert image
    out = im2double(out);
    
    showImage(im, im_edge, out, d);
    
    figure;
    imagesc(out);
    colormap(gray);
end

function showImage(im, im_edge, reIm, d)
    figure;
    subplot(2,2,1);
    imagesc(uint8(im));
    axis image, title Original

    subplot(2,2,2);
    imagesc(uint8(im_edge));
    axis image, title 'Binary edge image'

    subplot(2,2,3);
    imagesc(uint8(reIm));
    axis image, title 'Hough-Transformation'
        
    colormap(gray);
end

function out = color2gray(im)
    [m n] = size(im);    
    out(1:m, 1:n) = (im(1:m,1:n, 1) + im(1:m,1:n, 2) + im(1:m,1:n, 3)) / 3;    
%     for i = 1:m
%         for j = 1:n
%             out(i,j) = (im(i,j, 1) + im(i,j, 2) + im(i,j, 3)) / 3;
%         end    
end
