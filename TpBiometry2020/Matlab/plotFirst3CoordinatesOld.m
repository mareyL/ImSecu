% Filename:     plotFirst3Coordinates.m
% Author:       Federico MATTA & Florent PERRONIN
% Last update:  08/03/2005
% Copyright:    Institut Eurecom
%
% FigureHandle = plotFirst3Coordinates(Locations, ThresholdIndividuals,
% ThresholdFaces)
%
% If 'Locations' contains the coordinates of the faces of various individuals, 
% then this function plots the first 3 coordinates of the first 'ThresholdFaces' faces
% of the first 'ThresholdIndividuals' individuals. Of course, the coordinates
% of different faces of the same individual should be contiguous in 'Locations'.
% No more than 5 individuals are allowed.
% 
% Usage example:
% plotFirst3Coordinates(Locations, 4, 3);

function FigureHandle = plotFirst3Coordinates(Locations, ThresholdIndividuals, ThresholdFaces)

error(nargchk(3, 3, nargin))

% Initialization: parameters...
Aspect = ['bo';'rx'; 'g+'; 'kd'; 'm*'];
ThresholdIndividuals = min(ThresholdIndividuals, 5);


% Execution: retrieving the limits...
LocationsMinimums = min(Locations(:, 1 : 3));
LocationsMaximums = max(Locations(:, 1 : 3));

% Execution: plotting points...
FigureHandle = figure;
hold on;
for IndexPerson = 1 : ThresholdIndividuals
  plot3(Locations((IndexPerson - 1) * ThresholdFaces + 1 : IndexPerson * ThresholdFaces, 1), Locations((IndexPerson - 1) * ThresholdFaces + 1 : IndexPerson * ThresholdFaces, 2), Locations((IndexPerson - 1) * ThresholdFaces + 1 : IndexPerson * ThresholdFaces, 3), Aspect(IndexPerson , :));
end,
axis([LocationsMinimums(1) LocationsMaximums(1) LocationsMinimums(2) LocationsMaximums(2) LocationsMinimums(3) LocationsMaximums(3)]);
view(69, 50);
xlabel('Eigenface 1');
ylabel('Eigenface 2');
zlabel('Eigenface 3');
grid;