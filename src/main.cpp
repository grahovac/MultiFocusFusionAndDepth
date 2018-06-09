
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <sys/types.h>
#include <dirent.h>
#include <regex>
#include "FocusMeasurer/VarianceOfLaplacians.hpp"
#include "ImageWrapping/ImageFunctions.hpp"
#include "DepthMeasurer/DepthMeasurer.hpp"

using namespace std;
using namespace cv;

class FocusContext
{
private:
    FocusMeasurer* fm_;
public:
    FocusContext(FocusMeasurer* fm): fm_(fm)
    {
    }
    void setFM(FocusMeasurer* fm)
    {
        fm_ = fm;
    }

    Mat measure(cv::Mat& inImg)
    {
        return fm_->measureFocus(inImg);
    }
};



vector<string> getCorrectFiles(string pathDir)
{
    regex fileRegex("b_bigbug00[[:digit:]]{2}_croppped.png");
    DIR* dirpath = opendir(pathDir.c_str());
    struct dirent* ent;
    vector<string> imageNames;
    vector<string> correctImageNames;
    while ((ent = readdir(dirpath)) != NULL) {
        imageNames.push_back(ent->d_name);
    }
    for(auto it=imageNames.begin(); it!=imageNames.end();it++)
    {
        if(regex_match(*it,fileRegex))
        {
            correctImageNames.push_back(*it);
        }
    }
    sort(correctImageNames.begin(), correctImageNames.end());
    return correctImageNames;
}

vector<Mat> readImages(string pathDir)
{
    cout << "Using input image path:" << pathDir << endl;
    vector<Mat> images;
    string filepath;
    vector<string> imageNames = getCorrectFiles(pathDir);
    for (int i = 0; i < imageNames.size(); ++i) {
        images.push_back(imread((pathDir+imageNames[i]), IMREAD_COLOR));

    }
    return images;

}

Mat GetMaxFocus(vector<Mat>& focusMeasured, vector<Mat>& inputImages)
{
    int rows = focusMeasured[0].rows;
    int cols = focusMeasured[0].cols;
    Mat dst(rows,cols,CV_8UC3);
    Mat indices = bestIndices(focusMeasured);
    vector<double> currentPixel(focusMeasured.size());
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            int bestIndex =  indices.at<uint8_t>(row,col);
            dst.at<Vec3b>(row,col) = inputImages[bestIndex].at<Vec3b>(row,col);
        }
    }
    return dst;
}


int main( int argc, char** argv )
{
    string pathDir = "../data/bug/";
    if(argc > 1)
        pathDir = argv[1];

    vector<Mat> images = readImages(pathDir);
    vector<Mat> grayimages;
    int totalImgs = images.size();

    for(int i = 0; i<totalImgs; i++) {
        Mat tmp = getGrayscaleImg(images[i]);
        grayimages.push_back(tmp);
    }
    vector<int> compression_params;
    compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
    compression_params.push_back(9);

    vector<Mat> focusMeasured;
    VarianceOfLaplacians focusm;
    FocusContext focusctx(&focusm);

    for(int i = 0; i<grayimages.size(); i++) {
        Mat tmp = focusctx.measure(grayimages[i]);
        focusMeasured.push_back(tmp);
    }

    Mat maxFocus = GetMaxFocus(focusMeasured, images);
    Mat depthMap = measureDepth(focusMeasured);

    imwrite(("../../results/FocusMax.png"), maxFocus, compression_params);
    imwrite(("../../results/Depth.png"), depthMap, compression_params);

    return 0;
}

