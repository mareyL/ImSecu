% Filename:     loadImage.m
% Author:       Federico MATTA
% Last update:  11/03/2005
% Copyright:    Institut Eurecom
%
% Image = loadImage(FileName, Path)
%
% It loads an image, automatically resizing it to 56 * 46 pixels;
% the output will be a vector of size 1 * 2,576.
% 'FileName' is the image FileName and 'Path' (optional) is the relative path
% (to the current one) for selecting the directory.
%
% Usage example:
% Image =
% loadImage('baboon.pgm', '/datas/teaching/courses/image/TpBio/Images/detection/');
% Alternative usage example:
% Image = loadImage('/datas/teaching/courses/image/TpBio/Images/detection/baboon.pgm');

function Image = loadImage(FileName, varargin)

error(nargchk(1, 2, nargin))
if (length(varargin) > 0 && ~isempty(varargin{1}))
    Path = varargin{1};
else
    Path = '';
end,

% Initialization: parameters...
ResizeValues = [56, 46];


% Execution: loading and resizing picture...
Image = double(reshape(imresize(imread(strcat(Path, FileName)), ResizeValues, 'bicubic'), 1, prod(ResizeValues)));