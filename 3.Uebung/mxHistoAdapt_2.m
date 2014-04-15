function [ output_args ] = mxHistoAdapt_2( input_args )
%MXCUMHISTO Summary of this function goes here
%   Detailed explanation goes here

    bin = 1;
    adaptImage = uint8(imread(input_args));
    refImage = uint8(imread(input_args));

    refHisto = mxCumHisto(refImage, bin);
    adaptHisto = mxCumHisto(adaptImage, bin);
    
    lut = mexHistoAdapt(refHisto, adaptHisto);
    changeImage(adaptImage, newImage, lut);
    
    area(newImage);

end

