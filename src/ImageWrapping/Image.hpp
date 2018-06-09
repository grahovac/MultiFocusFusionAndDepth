
#ifndef IMAGE_HPP
#define IMAGE_HPP
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;
using namespace std;


class Image
{
public:

    Image(const Mat& inImg) : nRows(inImg.rows), nCols(inImg.cols), channels(inImg.channels())
    {
        pixels.reserve(nRows*nCols*channels);
        if (inImg.isContinuous())
            pixels.assign(inImg.datastart, inImg.dataend);
        else
        {
            int i,j;
            for( i = 0; i < nRows; ++i)
            {
                pixels.insert(pixels.end(), inImg.ptr<uint8_t>(i), inImg.ptr<uint8_t>(i)+inImg.cols);
            }
        }
    }
    Image(int rows, int cols, int chan):nRows(rows),nCols(cols),channels(chan),pixels(rows*cols*chan)
    {
    }
    uint8_t& at(int row, int col, int channel = 0)
    {
        return pixels[(row * nCols + col) * channels + channel];
    }

    Image& grayImg();

    int nRows;
    int nCols;
    int channels;
    vector<uint8_t> pixels;
};

#endif





