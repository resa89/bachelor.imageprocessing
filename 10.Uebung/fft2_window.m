% -------------------------------------------------------------------------
%   [ ywin ] = fft2_window(y, window_type)
%
%
%
% -------------------------------------------------------------------------
function [ ywin ] = fft2_window(y, window_type)
    %FFT2WINDOW performs the windowing operation on an input matrix
    % Lab exercise 'Industrial Image Processing' 2D FFT with windowing
    % 2008, Gregor Jehle <gjehle@htwg-konstanz.de>

%     display('fft2_window.m IMPLEMENT ME!');

    if(isempty(window_type) || strcmpi(window_type,'none'))
        % identity implementation
        ywin = y;
        return;
    end

    % input factors
    % inputfact(m,n) = distance( (m,n) , center )
    % normed to matrix limits
    inputfact = ones(size(y));
    Nm = size(y,1);
    Nn = size(y,2);
    for m = 1:Nm;
        for n = 1:Nn;
            inputfact(m,n) = sqrt(((n-Nn/2)/(Nn/2))^2+((m-Nm/2)/(Nm/2))^2);
        end
    end

    % switch?
    if(strcmpi(window_type,'elliptic'))
        ywin = y .* (inputfact < 1);
    elseif(strcmpi(window_type,'gauss'))
        ywin = y .* exp(-inputfact.^2./(2*0.3^2));
    elseif(strcmpi(window_type,'sgauss'))
        ywin = y .* exp(-(inputfact.^6) ./ 0.4);
    elseif(strcmpi(window_type,'bartlett'))
        ywin = y .* (1 - inputfact) .* (inputfact < 1);
    elseif(strcmpi(window_type,'hanning'))
        ywin = (y .* (0.5 * cos(pi * inputfact + 1)) .* (inputfact <1));
    elseif(strcmpi(window_type,'parzen'))
        ywin = y .* ((1 - 6*inputfact.^2 + 6*inputfact.^3) .* ...
            (inputfact < 0.5) + (2*(1-inputfact).^3) .* ...
            (inputfact >= 0.5) .* (inputfact < 1));
    else
        % nothing works, well.. whatever
        display(sprintf('unkown windowing type: %s. using no windowing.',...
            window_type));
        ywin = y;
    end
end