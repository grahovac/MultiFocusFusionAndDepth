#pragma once

#ifndef FOCUSMEASURER_HPP
#define FOCUSMEASURER_HPP

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>




class FocusMeasurer
{
public:
    virtual cv::Mat measureFocus(cv::Mat& inImg) = 0;
protected:
    int nRows, nCols, channels;

};



#endif
