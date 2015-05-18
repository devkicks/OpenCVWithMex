% demo script showing the usage of the opencv based mex

% Author: Muhammad Asad
% Date: 18/05/2015

close all
clear al
clc

inImage = double(imread('inImage.jpg'));
outImage = opencvGrayscale(inImage);

figure;
title('OpenCV funciont with Matlab Mex');
subplot(1,2,1);
imshow(uint8(inImage));
xlabel('Input');

subplot(1, 2, 2);
imshow(outImage);
xlabel('Output');