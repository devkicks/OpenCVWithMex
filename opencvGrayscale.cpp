/**
 * Copyright 2013 B. Schauerte. All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions are 
 * met:
 * 
 *    1. Redistributions of source code must retain the above copyright 
 *       notice, this list of conditions and the following disclaimer.
 * 
 *    2. Redistributions in binary form must reproduce the above copyright 
 *       notice, this list of conditions and the following disclaimer in 
 *       the documentation and/or other materials provided with the 
 *       distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY B. SCHAUERTE ''AS IS'' AND ANY EXPRESS OR 
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
 * DISCLAIMED. IN NO EVENT SHALL B. SCHAUERTE OR CONTRIBUTORS BE LIABLE 
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR 
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *  
 * The views and conclusions contained in the software and documentation
 * are those of the authors and should not be interpreted as representing 
 * official policies, either expressed or implied, of B. Schauerte.
 */

/** opencv_matlab - how to call OpenCV from Matlab
 *  A simple example (with some type conversions) on how to invoke OpenCV
 *  functions from a Matlab C++-.mex file.
 * 
 *  \author B. Schauerte
 *  \email  <schauerte@kit.edu>
 *  \date   2013
 */

/** Modified opencv_matlab to create a much simpler OpenCVGrayscale example
 * A basic function call that converts the input image to grayscale
 *
 * Author: Muhammad Asad
 * email: masad.801@gmail.com
 * date: 18/05/2015
 */

#include <opencv2/opencv.hpp>
#include "mex.h"
#include "opencv_matlab.hpp"

void 
mexFunction(int nlhs, mxArray *plhs[], 
            int nrhs, const mxArray *prhs[])
{
	// simple handling of the expected input arguments from matlab
	
	// these checks would ideally be dependent on your code functionality
    if (nrhs == 0)
    {
        mexErrMsgTxt("An image is required!");
    }
    
    if(mxGetNumberOfDimensions(prhs[0]) != 3) 
    {
        mexErrMsgTxt("Input image should be colored.");
    }

    if(!mxIsDouble(prhs[0]))
    {
        mexErrMsgTxt("Input image should be of Double type.");
    }
    if(nrhs > 1)
    {
        mexErrMsgTxt("Only one input argument is required.");
    } 
    
    // determine input image properties
    const int *dims    = mxGetDimensions(prhs[0]);
    const int nDims    = mxGetNumberOfDimensions(prhs[0]);
    const int rows     = dims[0];
    const int cols     = dims[1];
    const int channels = (nDims == 3 ? dims[2] : 1);
    
    // Allocate, copy, and convert the input image
    // @note: input is double
    cv::Mat inImage = cv::Mat::zeros(cv::Size(cols, rows), CV_64FC(channels));
    mexPrintf("Got the Image \n");
    
	// use the helper library to copy the data from input mxArray to cv::Mat
	om::copyMatrixToOpencv(mxGetPr(prhs[0]), inImage);
    mexPrintf("Converted to Mat \n");
    inImage.convertTo(inImage, CV_8U);
	// create a single channel Matrix to store the output grayscale image
    cv::Mat outImage = cv::Mat::zeros(rows, cols, CV_8UC1);
    
	// convert the image to grayscale
	cv::cvtColor(inImage, outImage, CV_RGB2GRAY);
    mexPrintf("Applied the operations \n");

	int outDims[2];
	outDims[0] = outImage.rows;
	outDims[1] = outImage.cols;
	int outNDims = 2;

    // Convert opencv to Matlab and set as output
    plhs[0] = mxCreateNumericArray(outNDims, outDims, mxUINT8_CLASS, mxREAL);
    
	// use the helper library to copy the cv::Mat data to mxArray for return
	om::copyMatrixToMatlab<unsigned char>(outImage, (unsigned char*)mxGetPr(plhs[0]));
    mexPrintf("Converted to mxArry for return \n");
}