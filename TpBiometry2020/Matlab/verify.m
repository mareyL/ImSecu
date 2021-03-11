% Filename:     verify.m
% Author:       Federico MATTA & Florent PERRONIN
% Last update:  09/03/2005
% Copyright:    Institut Eurecom
%
% [DistancesClients, DistancesImpostors] = verify(Models, Test, Threshold)
%
% It computes scores for all clients and impostors. 
% 'Threshold' is the number of eigenfaces used for the identification.
% 'Models' and 'Test' contain respectively the coordinates of training 
% models and test images. The same restrictions on 'Models' and 'Test'
% as for identify apply to verify. 
% Client (resp. impostor) scores are returned in 'DistancesClients'
% (resp. 'DistancesImpostors'); more precisely, these scores are the
% Euclidean distances of vectors in face space.
%
% Usage example:
% [DistancesClients, DistancesImpostors] = verify(Models, Test, 5);

function [DistancesClients, DistancesImpostors] = verify(Models, Test, Threshold)

error(nargchk(3, 3, nargin))


% Execution: computing client and impostor scores...
ModelsSizes = size(Models);
TestSizes = size(Test);
N = TestSizes(1) / ModelsSizes(1);
for Index = 1 : ModelsSizes(1);
  Distances(Index, :) = sum(( (repmat(Models(Index, 1 : Threshold), TestSizes(1), 1) - Test(:, 1 : Threshold))  .^ 2)', 1);
  DistancesClients(Index, :) = Distances(Index, ((Index - 1) * N + 1) : (Index * N));
  DistancesImpostors(Index, :) = [Distances(Index, 1 : ((Index - 1) * N)), Distances(Index, (Index * N + 1) : TestSizes(1))];
end,

% Execution: rearranging distances in a vector...
DistancesClients = reshape(DistancesClients, 1, TestSizes(1));
DistancesImpostors = reshape(DistancesImpostors, 1, ((ModelsSizes(1) - 1) * TestSizes(1)));