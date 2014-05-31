% -------------------------------------------------------------------------
%   [ Yo ] = optview( Y )
%
%
%
% -------------------------------------------------------------------------
function [ Yo ] = optview( Image )
    %OPTVIEW Optimize fourier results for viewing
    % Lab exercise 'Industrial Image Processing' 2D FFT with windowing
    % 2008, Gregor Jehle <gjehle@htwg-konstanz.de>

    % identity implementation
    Yo = real(log(Image));

    % here be dragons
    
    [X,Y,Z] = peaks(256); % surface
    I = Yo; % image  

    figure;
    mesh(X, Y, Z, I); % overlay image as texture
    colormap gray; hold on; 
    c = 1.5*min(Z(:)); % scaling Z- location of image 
    mesh(X, Y, c*ones(size(Z)), I) % underlay image as a constant-height surface
    
    % display('opt_view.m IMPLEMENT ME!');
    Yo = real(log(abs(Image)));
    Yo = sqrt(abs(Image));
    Yo = log10(abs(Image));
end