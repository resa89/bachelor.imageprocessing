% -------------------------------------------------------------------------
% Example
%   mex -setup    
%   mex -I../h -DMATLAB -DNO_INFO ip_wavelet.cpp ../src/filter.cpp
%   ../src/scsp.cpp ../src/smooth.cpp ../src/scale.cpp ../src/bspline.cpp ../src/stats.cpp
%   
% -------------------------------------------------------------------------
mex EntryPoint.cpp;