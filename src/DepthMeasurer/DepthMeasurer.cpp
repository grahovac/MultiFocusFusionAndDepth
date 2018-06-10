#include "DepthMeasurer.hpp"
#include "../ImageWrapping/ImageFunctions.hpp"

using namespace cv;
using namespace std;

double minFocusMeasure = 3e6;

Mat measureDepth(vector<Mat> focusMeasured)
{
    int rows = focusMeasured[0].rows;
    int cols = focusMeasured[0].cols;
    Mat dst(rows,cols,CV_64FC1);
    Mat dst2(rows,cols,CV_64FC1);
    Mat indices = bestIndices(focusMeasured);
    int setSize = focusMeasured.size();
    vector<int> compression_params;
    compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
    compression_params.push_back(9);
    vector<Mat> focused;
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            double pixelValue = indexToFocusPoint(indices.at<uint8_t>(row,col), setSize);
            //double pixelV = applyApproximateMean(focusMeasured, indices.at<uint8_t>(row,col), row, col);
            //dst2.at<double>(row,col) = pixelV;

            if(focusMeasured[indices.at<uint8_t>(row,col)].at<double>(row,col) < minFocusMeasure)
                pixelValue = 0.0;
            dst.at<double>(row,col) = pixelValue;
        }
    }
    //imwrite(("ResultsFM.png"), convertToU8<double>(dst2), compression_params);
    //imwrite(("ResultsFM2.png"), dst2, compression_params);

    Mat output = convertToU8<double>(dst);
    return output;
}

double applyApproximateMean(vector<Mat> focusMeasured, int index, int row, int col)
{

    int imagesSet = focusMeasured.size();
    int previdx = max(index-1, imagesSet-1);
    int nextidx = min(index+1,0);
    double fmPreviousFocus = log(focusMeasured[previdx].at<double>(row,col));
    double fmCurrentFocus = log(focusMeasured[index].at<double>(row,col));
    double fmNextFocus = log(focusMeasured[nextidx].at<double>(row,col));
    double dmPrevious = indexToFocusPoint(previdx,imagesSet);
    double dmCurrent = indexToFocusPoint(index,imagesSet);
    double dmNext = indexToFocusPoint(nextidx,imagesSet);
    double depth_numerator = (fmCurrentFocus - fmNextFocus)*(dmCurrent*dmCurrent-dmPrevious*dmPrevious) -
                                 (fmCurrentFocus - fmPreviousFocus)*(dmCurrent*dmCurrent-dmNext*dmNext);
    double depth_denominator = 2 * ((fmCurrentFocus - fmNextFocus)+(fmCurrentFocus - fmPreviousFocus));
    double depth = depth_numerator/depth_denominator;
    double sigma_sqd = ((dmCurrent*dmCurrent-dmPrevious*dmPrevious)+ (dmCurrent*dmCurrent-dmNext*dmNext))/depth_denominator;
    double fm = focusMeasured[index].at<double>(row,col);
    double exponent = (dmCurrent-depth)*(dmCurrent-depth)/(sigma_sqd);
    return fm/exp(-0.5*exponent);

}


Mat bestIndices(vector<Mat> focusMeasured) {
    int rows = focusMeasured[0].rows;
    int cols = focusMeasured[0].cols;
    Mat dst(rows, cols, CV_8UC1);
    vector<double> currentPixel(focusMeasured.size());
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            for (int j = 0; j < focusMeasured.size(); ++j) {
                currentPixel[j] = focusMeasured[j].at<double>(row, col);
            }
            int bestIndex = distance(currentPixel.begin(), std::max_element(currentPixel.begin(), currentPixel.end()));
            dst.at<uint8_t>(row,col) = bestIndex;
        }
    }
    return dst;
}

double  indexToFocusPoint(int index, size_t imgCount)
{
    return  255.0 -(index * 255.0 /(imgCount));
}
