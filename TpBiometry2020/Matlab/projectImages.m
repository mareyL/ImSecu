% Filename:     projectImages.m
% Author:       Federico MATTA & Florent PERRONIN
% Last update:  03/05/2006
% Copyright:    Institut Eurecom
%
% Locations = projectImages(Vectors, Means, Space)
%
% It projects vectors 'Vectors' into the space spanned by vectors 'Space'.
% 'Means', the average of all the faces used to train the space,
% must be provided.
%
% Usage example:
% Locations = projectImages(Vectors, Means, Space);

function Locations = projectImage(Vectors, Means, Space)

error(nargchk(3, 3, nargin))


% Execution: projecting vectors onto space...
VectorsSizes = size(Vectors);
Locations = (Vectors - repmat(Means, VectorsSizes(1), 1)) * Space';