function sequentialLabeling( imagePath, foregroundColor )
    mex mxSequentialLabeling.cpp;
    
    originalImage = imread(imagePath);
    
    if (isa(originalImage, 'uint8'))
        originalImage = mxGray2Bin(originalImage);
    end
    
    toBeProcessedImage = originalImage;
    
    if (foregroundColor == 'B')
        toBeProcessedImage = ~originalImage;
    elseif (foregroundColor ~= 'W')
        error('Foreground color must be "B" or "W" (Black or White)');
    end
    
    labeledImage = mxSequentialLabeling(toBeProcessedImage);
    
    colormap('gray');
    subplot(2,1,1), subimage(originalImage);
    title('Original');
    
    subplot(2,1,2), subimage(labeledImage);
    title('Region labeled');

    %truesize;
    
end