% Filename:     computeEER.m
% Author:       Federico MATTA & Florent PERRONIN
% Last update:  11/03/2005
% Copyright:    Institut Eurecom
%
% EqualErrorRate = computeEER(DistancesClients, DistancesImpostors)
%
% It computes the Equal Error Rate (EER)  based on the client scores
% 'DistancesClients' and impostor scores 'DistancesImpostors'.
%
% Usage example:
% EqualErrorRate = computeEER(DistancesClients, DistancesImpostors);

function EqualErrorRate = computeEER(DistancesClients, DistancesImpostors)

error(nargchk(2, 2, nargin))


% Execution: computing EER...
DistancesClientsSizes = size(DistancesClients);
DistancesImpostorsSizes = size(DistancesImpostors);
DistancesClients = - sort(- DistancesClients);
DistancesImpostors = - sort(- DistancesImpostors);
IndexImpostors = 1;
for IndexThreshold = 1 : DistancesClientsSizes(2),
    while (IndexImpostors <= DistancesImpostorsSizes(2) & DistancesImpostors(IndexImpostors) > DistancesClients(IndexThreshold)),
        IndexImpostors = IndexImpostors + 1;
    end,
    if ((IndexThreshold / DistancesClientsSizes(2)) >= (DistancesImpostorsSizes(2) - IndexImpostors) / DistancesImpostorsSizes(2)),
        EqualErrorRate = 0.5 * (IndexThreshold / DistancesClientsSizes(2) + (DistancesImpostorsSizes(2) - IndexImpostors) / DistancesImpostorsSizes(2));
        break;
    end,
end,