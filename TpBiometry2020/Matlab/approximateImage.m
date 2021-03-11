% Filename:     approximateImage.m
% Author:       Federico MATTA & Florent PERRONIN
% Last update:  07/03/2005
% Copyright:    Institut Eurecom
%
% FigureHandle = approximateImage(FileName, Means, Space, Threshold)
%
% It approximates the image contained in 'FileName' using the first 'Threshold' eigenfaces. 
% 'Means', the average of all the faces used to train the space, and 'Space', 
% the eigenspace, must be provided.
% The original face image and its approximation are displayed.
% FileName contains the relative path (to the current one) and the image
% filename.
%
% Usage example:
% approximateImage('/datas/teaching/courses/image/TpBio/Images/train_A/s11_
% 5.jpg', Means, Space, 88);

function FigureHandle = approximateImage(FileName, Means, Space, Threshold)

error(nargchk(4, 4, nargin))

% Initialization: checking FileName and path...
FileList = dir(FileName);
FileListSizes = size(FileList);
if (FileListSizes(1) == 0)
    error('The image does not exist: check the path or filename');
end,

% Initialization: parameters...
ResizeValues = [56, 46];


% Execution: approximating image...
ImageOriginal = double(reshape(imresize(imread(FileName), ResizeValues, 'bicubic'), 1, prod(ResizeValues)));
Locations = projectImages(ImageOriginal, Means, Space);
LocationsSizes = size(Locations);
VectorApproximated = Locations(:, 1 : Threshold) * Space(1 : Threshold, :) + Means;
ImageApproximated = reshape(VectorApproximated, ResizeValues(1), ResizeValues(2));

% Execution: plotting original and approximated images...
FigureHandle = figure;
subplot(1, 2, 1);
imshow(uint8(reshape(ImageOriginal, ResizeValues(1), ResizeValues(2))));
xlabel('Original face image');
subplot(1, 2, 2);
imshow(uint8(ImageApproximated));
xlabel(['Approximation with ', num2str(Threshold), ' eigenfaces']);