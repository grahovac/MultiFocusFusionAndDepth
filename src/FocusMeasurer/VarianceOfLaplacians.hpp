#pragma once

#ifndef VARIANCEOFLAPLACIANS_HPP
#define VARIANCEOFLAPLACIANS_HPP

#include "FocusMeasurer.hpp"

#include <numeric>


class VarianceOfLaplacians: public FocusMeasurer
{
public:
    cv::Mat measureFocus(cv::Mat& inImg);
    std::vector<int> getLaplacian(int kernelsize);
    cv::Mat getVariance(cv::Mat& inImg, int windowSize);

};

#endif

