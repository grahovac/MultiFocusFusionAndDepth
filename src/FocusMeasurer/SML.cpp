#include "SML.hpp"
#include "../ImageWrapping/ImageFunctions.hpp"

using namespace std;
using namespace cv;


Mat SML::measureFocus(Mat &inImg) {
    Mat gray = getGrayscaleImg(inImg);
    Mat focus = getML(gray,1);
    return focus;
}

Mat SML::getML(Mat &gray, int step) {
    Mat dst(gray.rows,gray.cols,1);
    uint8_t* inputRow;
    uint8_t* outputRow;
    uint8_t* inputRowMinusStep;
    uint8_t* inputRowPlusStep;
    for (int i = step; i < gray.rows-step; ++i) {
        inputRow = gray.ptr<uint8_t>(i);
        outputRow = dst.ptr<uint8_t>(i);
        inputRowMinusStep = gray.ptr<uint8_t>(i-step);
        inputRowPlusStep = gray.ptr<uint8_t>(i-step);
        for (int j = step; j < gray.cols-step; ++j) {
            outputRow[j] = abs(2*inputRow[j]-inputRow[j-step]-inputRow[j+step]) +
                    abs(2*inputRow[j]-inputRowMinusStep[j]-inputRowPlusStep[j]);
        }
    }
    return dst;

}