% build optimizeTest
% addpath(genpath('opencv\\'));
mex -Iopencv\include -Lopencv\lib -lopencv_core247 -lopencv_imgproc247 opencvGrayscale.cpp