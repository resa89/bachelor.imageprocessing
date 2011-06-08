% -------------------------------------------------------------------------
%   [ Yc ] = fft2_center( Y )
%
%
%
% -------------------------------------------------------------------------
function [ Yc ] = fft2_center( Y )
    % FFT2CENTER Converts a 2D fft result to the image processing style centered view
    % Lab exercise 'Industrial Image Processing' 2D FFT with windowing
    % 2008, Gregor Jehle <gjehle@htwg-konstanz.de>

    % identity implementation
    Yc = Y;

    M = size(Y,1);
    N = size(Y,2);

    Mc = int32(M/2);
    Nc = int32(N/2);

    c11 = Y(1:Mc, 1:Nc);
    c12 = Y(Mc+1:M, 1:Nc);
    c21 = Y(1:Mc, Nc+1:N);
    c22 = Y(Mc+1:M, Nc+1:N);

    Yc = [c22 c12; c21 c11];

	% To Do:
	%display('fft2_center.m IMPLEMENT ME!');

end