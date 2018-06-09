
#ifndef DEPTHMEASURER_HPP
#define DEPTHMEASURER_HPP
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

cv::Mat measureDepth(std::vector<cv::Mat> focusMeasured);
uint8_t indexToDepth(int index, size_t imgCount);
cv::Mat bestIndices(std::vector<cv::Mat> focusMeasured);
double applyApproximateMean(std::vector<cv::Mat> focusMeasured, int index, int row, int col);
double indexToFocusPoint(int index, size_t imgCount);


#endif
