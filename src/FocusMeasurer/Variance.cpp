#include "Variance.hpp"
#include "../ImageWrapping/ImageFunctions.hpp"

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

    Mat dst(nRows, nCols, CV_64FC1);
    double mean = getMean(inImg);
    double* q;
    uint8_t* p;
    for(int i = 0; i < nRows; i++)
    {
        q = dst.ptr<double>(i);
        p = inImg.ptr<uchar>(i);
        for(int j = 0; j < nCols; j++)
        {
            q[j] = (p[j]-mean)*(p[j]-mean);
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

