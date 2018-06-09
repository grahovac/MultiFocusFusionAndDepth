#pragma once

#ifndef VARIANCE_HPP
#define VARIANCE_HPP

#include "FocusMeasurer.hpp"

class Variance : public FocusMeasurer
{
public:
    cv::Mat measureFocus(cv::Mat& inImg);
    double getMean(cv::Mat& inImg);
};


#endif
