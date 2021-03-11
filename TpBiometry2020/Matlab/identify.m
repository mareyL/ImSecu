% Filename:     identify.m
% Author:       Federico MATTA & Florent PERRONIN
% Last update:  09/03/2005
% Copyright:    Institut Eurecom
%
% IdentificationRate = identify(Models, Test, Threshold, NBest)
%
% It evaluates the percentage of identification. 
% 'Threshold' is the number of eigenfaces used for the identification;
% 'NBest' is the number of candidates that are retained for each test image (N-best).
% 'Models' and 'Test' contain respectively the coordinates of training
% models and test images. We assume that 'Models' contains ONE model (or point) per 
% individual. 'Test' may contain many points per individual but individuals should
% be sorted in the same manner in 'Models' and 'Test', and all the images of one
% individual should be contiguous in 'Test'.
%
% Usage example:
% Score = identify(TrainAModels, TestA, 5, 1);

function IdentificationRate = identify(Models, Test, Threshold, NBest)

error(nargchk(4, 4, nargin))


% Execution: computing the identification scores...
ModelsSizes = size(Models);
TestSizes = size(Test);
Truth = reshape(repmat([ 1 : ModelsSizes(1)], (TestSizes(1) / ModelsSizes(1)), 1), 1, TestSizes(1));
for Index = 1 : ModelsSizes(1),
    Distances(Index, :) = sum(( (repmat(Models(Index, 1 : Threshold), TestSizes(1), 1) - Test(:, 1 : Threshold))  .^ 2)', 1);
end,

% Execution: computing the identification rate...
[Values, Indeces] = sort(Distances);
TempRates = size(find((Indeces(1 : NBest, :) == repmat(Truth, NBest, 1))));
if (NBest == 1)
    IdentificationRate = TempRates(2);
else
    IdentificationRate = TempRates(1);
end,