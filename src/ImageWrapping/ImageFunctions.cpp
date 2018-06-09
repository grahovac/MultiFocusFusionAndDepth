#include "ImageFunctions.hpp"
#include <iostream>
using namespace std;
cv::Mat getGrayscaleImg(cv::Mat& BGRImg)
{
    cv::Mat dst(BGRImg.rows,BGRImg.cols,1);
    int channels = BGRImg.channels();
    if (channels>1) {
        cvtColor(BGRImg, dst, CV_BGR2GRAY);
    }
    return dst;
}


cv::Mat convolve2D(cv::Mat &inImg, std::vector<int> filter, int kernelSize)

{
    int kernelHalf = kernelSize/2;
    if(inImg.channels()>1)
        inImg = getGrayscaleImg(inImg);

    int rows = inImg.rows;
    int cols = inImg.cols;
    cv::Mat dst = cv::Mat::zeros(rows, cols, CV_64FC1);
    for(int row = kernelHalf; row < rows-kernelHalf; ++row)
    {
        for(int col = kernelHalf; col < cols-kernelHalf; ++col)
        {
            double convoluted = 0;
            for(int i = -kernelHalf; i <= kernelHalf; ++i)
                for(int j = -kernelHalf; j <= kernelHalf; ++j)
                    convoluted += inImg.at<uint8_t>(row+i,col+j) *
                                  filter[kernelSize*(kernelHalf+i) + j + kernelHalf];
            dst.at<double>(row,col) = convoluted;
        }
    }

    //cv::Mat output = convertToU8<double>(dst);
    return dst;
}

cv::Mat convertFromDblToU8(cv::Mat& inImg)
{
    double minVal = std::numeric_limits<double>::max();
    double maxVal = std::numeric_limits<double>::min();
    double* rowPtr;
    int cols = inImg.cols;
    for(int row = 0; row < inImg.rows; ++row)
    {
        rowPtr = inImg.ptr<double>(row);
        double minRow = *min_element(rowPtr, rowPtr+cols);
        double maxRow = *max_element(rowPtr, rowPtr+cols);
        if(minRow<minVal)
            minVal = minRow;
        if(maxRow>maxVal)
            maxVal = maxRow;
    }
    cv::Mat dst= cv::Mat::zeros(inImg.rows,cols, CV_8UC1);
    double difference = 255.f/(maxVal-minVal);
    uint8_t* uPtr;
    for(int row = 0; row < inImg.rows; ++row)
    {
        uPtr = dst.ptr<uint8_t>(row);
        rowPtr = inImg.ptr<double>(row);
        for (int j = 0; j < cols; ++j) {
            uPtr[j] = (uint8_t)(rowPtr[j]*difference);
        }
    }
    return dst;
}

cv::Mat scaleFloatImage(cv::Mat &inImg)
{
    double minVal = std::numeric_limits<double>::max();
    double maxVal = std::numeric_limits<double>::min();
    double* rowPtr;
    double* rowDstPtr;
    int cols = inImg.cols;
    for(int row = 0; row < inImg.rows; ++row)
    {
        rowPtr = inImg.ptr<double>(row);
        double minRow = *min_element(rowPtr, rowPtr+cols);
        double maxRow = *max_element(rowPtr, rowPtr+cols);
        if(minRow<minVal)
            minVal = minRow;
        if(maxRow>maxVal)
            maxVal = maxRow;
    }
    cv::Mat dst= cv::Mat::zeros(inImg.rows, cols, CV_64FC1);
    double difference = 1.0/(maxVal-minVal);
    for(int row = 0; row < inImg.rows; ++row)
    {
        rowPtr = inImg.ptr<double>(row);
        rowDstPtr = dst.ptr<double>(row);
        for (int j = 0; j < cols; ++j) {
            rowDstPtr[j] = rowPtr[j]*difference;
        }
    }
    return dst;

}