% Filename:     loadImagesInDirectory.m
% Author:       Federico MATTA
% Last update:  11/03/2005
% Copyright:    Institut Eurecom
%
% Images = loadImagesInDirectory(Path)
%
% It loads all images present in a directory, automatically resizing them
% to 56 * 46 pixels; if N is the number of pictures in the directory,
% then the output will be a matrix of size N * 2,576.
% 'Path' is the relative path (to the current one) for selecting the directory.
%
% Usage example:
% Images = loadImagesInDirectory('/datas/teaching/courses/image/TpBio/Images/train_A/');

function Images = loadImagesInDirectory(Path);

error(nargchk(1, 1, nargin))

% Initialization: parameters...
ListingOffset = 2;
ResizeValues = [56, 46];


% Execution: loading and resizing pictures in a directory...
FileList = dir(Path);
FileListSizes = size(FileList);
for ImageIndex = 1 : 1 : (FileListSizes(1) - ListingOffset)
    FileName = (strcat(Path, FileList(ImageIndex + ListingOffset).name));
    Images(ImageIndex, :) = double(reshape(imresize(imread(FileName), ResizeValues, 'bicubic'), 1, prod(ResizeValues)));
end,