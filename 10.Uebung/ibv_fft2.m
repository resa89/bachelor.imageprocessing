% -------------------------------------------------------------------------
%   [] = ibv_fft2(img, window_type)
%
%
%
% -------------------------------------------------------------------------
function [] = ibv_fft2(img, window_type)
    % Lab exercise 'Industrial Image Processing' 2D FFT with windowing
    % 2008, Gregor Jehle <gjehle@htwg-konstanz.de>

    % 1: view the output as is
    % 2: view image processing style centered spectrum
    
    img = imread('shutter.jpg');
    window_type = 'parzen'; %'sgauss',  'elliptic', 'bartlett', 'hanning', 'parzen'
        
    ViewMode = 1;

    % windowing
    img = fft2_window(double(img),window_type);

    % do the FFT
    Y = fft2(img);
    Yr = real(Y);
    Yi = imag(Y);

    Xaxis = [0:size(Y,2)];
    Yaxis = [0:size(Y,1)];

    if (ViewMode == 2);
        % center style display
        Y = fft2_center(Y);
        Yr = fft2_center(Yr);
        Yi = fft2_center(Yi);

        % adjust axes
        Nx2 = int32(length(Xaxis)/2);
        Ny2 = int32(length(Yaxis)/2);
        Xaxis = [ -Nx2:Nx2 ];
        Yaxis = [ -Ny2:Ny2 ];
    end

    subplot(2,2,1);
    subimage(img,colormap(gray(255)));
    title('Signal i(x,y)');
    xlabel('Width (px)');
    ylabel('Height (px)');

    subplot(2,2,2);
    imagesc(Xaxis,Yaxis,optview(2*abs(Y)));
    colorbar;
    title('Amplitude Spectrum of I(x,y)');
    xlabel('Spatial Frequency X (Hz)');
    ylabel('Spatial Frequency Y (Hz)');

    subplot(2,2,3);
    imagesc(Xaxis,Yaxis,optview(Yr));
    colorbar;
    title('Real Spectrum of I(x,y)');
    xlabel('Spatial Frequency X (Hz)');
    ylabel('Spatial Frequency Y (Hz)');

    subplot(2,2,4);
    imagesc(Xaxis,Yaxis,optview(Yi));
    colorbar;
    title('Imaginary Spectrum of I(x,y)');
    xlabel('Spatial Frequency X (Hz)');
    ylabel('Spatial Frequency Y (Hz)');

%     colormap('jet');
    colormap('gray');
end
