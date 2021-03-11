% Filename:     computeDistanceFromSpace.m
% Author:       Federico MATTA & Florent PERRONIN
% Last update:  10/03/2005
% Copyright:    Institut Eurecom
%
% Distance = computeDistanceFromSpace(Vectors, Means, Space, Threshold)
%
% It computes the distance of one or many images contained in 'Vectors' to
% the projected ones in the space spanned by the first 'Threshold' vectors
% of 'Space'; 'Means', the average of all the faces used to train the eigenspace,
% must be provided. 'Distance', is the Euclidean distance in the face space.
%
% Usage example:
% Distance = computeDistanceFromSpace(Vectors, Means, Space, 5);

function Distance = computeDistanceFromSpace(Vectors, Means, Space, Threshold)

error(nargchk(4, 4, nargin))


% Execution: projecting vectors and calculating distance...
Locations = projectImages(Vectors, Means, Space);
VectorsApproximated = Locations(:, 1 : Threshold) * Space(1 : Threshold, :) + repmat(Means, size(Locations, 1), 1);
Distance = sum((Vectors - VectorsApproximated) .^ 2, 2);