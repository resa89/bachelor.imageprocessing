function ibv_fft()
% Lab exercise 'Industrial Image Processing'
% 2008, Gregor Jehle <gjehle@htwg-konstanz.de>
% 

% 1: view whole spectrum, one-sided
% 2: view half spectrum, one-sided
% 3: view image processing style centered spectrum
ViewMode = 3;

% sampling frequency
Fs = 1000;
% length of signal
L = 1000;

% sample time (do not change)
T = 1/Fs;
% time vector (do not change)
t = (0:L-1)*T;

% function
% x = x * cos(2 * pi * 0 * t) + 1 * sin(2 * pi * 100 * t);
%   = x * cos(0)              + 1 * sin(2 * pi * 100 * t);
%   = x * 1     [DC]          + 1 * sin(2 * pi * 100 * t) [AC];

x = 0;                             % amplitude 1, 0 Hz (DC)
x =  x + 1 * cos(2 * pi * 100 * t);
%x = x + 1 * cos( 2*pi * 100 * t ); % amplitude 1, 100 Hz
%x = x + 2 * cos( 2*pi * 200  * t ); % amplitude 2, 23 Hz
%x = x + 3 * cos( 2*pi * 300  * t ); % amplitude 3, 42 Hz
%x = x + 5 * sin( 2*pi * 443 * t ); % amplitude 5, 443 Hz 

% additive noise
NoiseFactor = 1;

% here comes the (zero-mean random) noise (do not change)
y = x + NoiseFactor*randn(size(t));

%%%%%%%%%%%%%%%%%%%%
NFFT = 2^nextpow2(L); % Next power of 2 from length of y

SpecDiv = 1;
LinSpaceStart = 0;
PlotStart = 1;
PlotEnd = NFFT/SpecDiv;

if (ViewMode == 1);
    SpecDiv = 1;
    LinSpaceStart = 0;
    PlotStart = 1;
    PlotEnd = NFFT/SpecDiv;
elseif (ViewMode == 2);
    SpecDiv = 2;
    LinSpaceStart = 0;
    PlotStart = 1;
    PlotEnd = NFFT/SpecDiv;
else
    SpecDiv = 1;
    LinSpaceStart = -1;   
    PlotStart = 1;
    PlotEnd = NFFT;
end

% do the FFT
Y = fft(y,NFFT)/L;

if (ViewMode == 3);
    % switch left and right half of spectrum
    Y = [ Y(NFFT/2+1:NFFT) Y(1:NFFT/2) ];
end


% create frequency scale for x-axis
f = Fs/SpecDiv/(1-LinSpaceStart)*linspace(LinSpaceStart,1,NFFT/SpecDiv);

subplot(2,2,1);
plot(Fs*t(1:50),y(1:50));
title('Signal');
xlabel('Time (ms)');

subplot(2,2,2);
plot(f,(Y(PlotStart:PlotEnd)));
title('Amplitude Spectrum of y(t)');
xlabel('Frequency (Hz)');
ylabel('|Y(f)|');

subplot(2,2,3);
plot(f,real(Y(PlotStart:PlotEnd)));
title('Real Spectrum of y(t)');
xlabel('Frequency (Hz)');
ylabel('Re(Y(f))');

subplot(2,2,4);
plot(f,imag(Y(PlotStart:PlotEnd)),'r');
title('Imaginary Spectrum of y(t)');
xlabel('Frequency (Hz)');
ylabel('Im(Y(f))');
