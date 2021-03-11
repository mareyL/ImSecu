% Filename:     computeVerificationRates.m
% Author:       Federico MATTA & Florent PERRONIN
% Last update:  16/06/2005
% Copyright:    Institut Eurecom
%
% [FalseRejectionRates, FalseAcceptanceRates] = computeVerificationRates
% (DistancesClients, DistancesImpostors)
%
% It computes the False Rejection Rate (FRR) and the False Acceptance Rate
% (FAR) based on the client scores 'DistancesClients' and impostor scores
% 'DistancesImpostors'.
%
% Usage example:
% [FalseRejectionRates, FalseAcceptanceRates] =
% computeVerificationRates(DistancesClients, DistancesImpostors);

function [FalseRejectionRates, FalseAcceptanceRates] = computeVerificationRates(DistancesClients, DistancesImpostors)

error(nargchk(2, 2, nargin))


% Execution: sorting descending all distances...
DistancesClientsSizes = size(DistancesClients);
DistancesImpostorsSizes = size(DistancesImpostors);
DistancesClients = - sort(- DistancesClients);
DistancesImpostors = - sort(- DistancesImpostors);

% Execution: computing FRR & FAR comparing distances...
FalseRejectionRates(1) = 0;
FalseAcceptanceRates(1) = 1;
IndexImpostors = 1;
for IndexThreshold = 1 : DistancesClientsSizes(2),
    while (IndexImpostors < DistancesImpostorsSizes(2) & DistancesImpostors(IndexImpostors) > DistancesClients(IndexThreshold)),
       IndexImpostors = IndexImpostors + 1;
   end,
   FalseRejectionRates(IndexThreshold + 1) = IndexThreshold / DistancesClientsSizes(2);
   FalseAcceptanceRates(IndexThreshold + 1) = (DistancesImpostorsSizes(2) - IndexImpostors) / DistancesImpostorsSizes(2);
end,