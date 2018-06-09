#pragma once

#ifndef SML_HPP
#define SML_HPP

#include "FocusMeasurer.hpp"

class SML: public FocusMeasurer
{
public:
    cv::Mat measureFocus(cv::Mat& inImg);
    cv::Mat getML(cv::Mat& gray, int step);
};

#endif