#include "Variance.hpp"
using namespace std;
using namespace cv;

Mat Variance::measureFocus(Mat& inImg)
{
    nRows = inImg.rows;
    nCols = inImg.cols;
    channels = inImg.channels();
    if (channels>1) {
        cvtColor(inImg, inImg, CV_RGB2GRAY);
    }

    Mat& dst(inImg);
    double mean = getMean(inImg);
    uchar* q;
    for(int i = 0; i < nRows; i++)
    {
        q = dst.ptr<uchar>(i);
        for(int j = 0; j < nCols; j++)
        {
            q[j] = (q[j]-mean)*(q[j]-mean);
        }
    }
    return dst;
}

double Variance::getMean(Mat& inImg)
{
    double mean = 0.0;
    uchar* p;
    for(int i = 0; i < nRows; i++)
    {
        p = inImg.ptr<uchar>(i);
        for(int j = 0; j < nCols; j++)
        {
            mean += p[j];
        }
    }
    mean /= nCols*nRows;
    return mean;
}

