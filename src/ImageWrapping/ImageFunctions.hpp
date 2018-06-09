#pragma once

#ifndef IMAGEFUNCTIONS_HPP
#define IMAGEFUNCTIONS_HPP

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector>
#include <iostream>

cv::Mat getGrayscaleImg(cv::Mat& BGRImg);
cv::Mat convolve2D(cv::Mat &inImg, std::vector<int> filter, int kernelSize);
cv::Mat convertFromDblToU8(cv::Mat &inImg);
cv::Mat scaleFloatImage(cv::Mat &inImg);

template<typename T>
cv::Mat convertToU8(cv::Mat& inImg)
{
    T minVal = std::numeric_limits<T>::max();
    T maxVal = -std::numeric_limits<T>::max();
    T* rowPtr;
    int cols = inImg.cols;

    for(int row = 0; row < inImg.rows; ++row)
    {
        rowPtr = inImg.ptr<T>(row);
        T minRow = *std::min_element(rowPtr, rowPtr+cols);
        T maxRow = *std::max_element(rowPtr, rowPtr+cols);
        if(minRow<minVal)
            minVal = minRow;
        if(maxRow>maxVal)
            maxVal = maxRow;

    }
    cv::Mat dst(inImg.rows,cols, CV_8UC1);
    double difference = 255.f/(maxVal-minVal);
    uint8_t* uPtr;
    for(int row = 0; row < inImg.rows; ++row)
    {
        uPtr = dst.ptr<uint8_t>(row);
        rowPtr = inImg.ptr<T>(row);
        for (int j = 0; j < cols; ++j) {
            uPtr[j] = (uint8_t)(rowPtr[j]*difference);
        }
    }
    return dst;
}


#endif
