addpath D:\Eurecom\ImSecu\TpBiometry2020\Matlab;

%% Exercie 1 Part A

train_A = loadImagesInDirectory('D:\Eurecom\ImSecu\TpBiometry2020\Images\train_A\');

[means_A, space_A, eigenvalues_A] = buildSpace(train_A);

%% Part B

cumsum_A = cumsum(eigenvalues_A);
x = 1:100;
figure;
plot(x, cumsum_A);
title('cumulative sum of eigenvalues');

%% Part C

approximateImage('D:\Eurecom\ImSecu\TpBiometry2020\Images\train_A\s1_1.jpg', means_A, space_A, 70);

%% Part D

train_into_space_A = projectImages(train_A, means_A, space_A);

plotFirst3Coordinates(train_into_space_A, 5, 5);

%% Exercice 2 Part A

test_A = loadImagesInDirectory('D:\Eurecom\ImSecu\TpBiometry2020\Images\test_A\');

test_into_space_A = projectImages(test_A, means_A, space_A);

plotFirst3Coordinates(test_into_space_A, 5, 5);

%% Part B

approximateImage('D:\Eurecom\ImSecu\TpBiometry2020\Images\test_A\s1_6.jpg', means_A, space_A, 100);

%% Part C

identifcationratesA = zeros(100, 1);
for n=1:100
    identifcationratesA(n) = identify(train_into_space_A, test_into_space_A, n, 1);
end
x = 1:100;


plot(x, identifcationratesA);

%% Part D

mean_train_into_space_A = zeros(20,1);
mean_test_into_space_A = zeros(20,1);
mean_identifcationratesA = zeros(20,1);
for n=1:20
    mean_train_into_space_A(n) = mean(train_into_space_A(5*(n-1)+1:5*(n)));
    mean_test_into_space_A(n) = mean(test_into_space_A(5*(n-1)+1:5*(n)));
end
for n=1:20
    mean_identifcationratesA(n) = identify(mean_train_into_space_A, mean_test_into_space_A, n, 1);
end
x = 1:20;

plot(x, mean_identifcationratesA);

