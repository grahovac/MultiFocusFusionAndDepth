#include "VarianceOfLaplacians.hpp"
#include "../ImageWrapping/ImageFunctions.hpp"
#include <iostream>
#include <ctime>
using namespace std;
using namespace cv;


Mat VarianceOfLaplacians::measureFocus(Mat &inImg) {
    //clock_t begin = clock();
    nRows = inImg.rows;
    nCols = inImg.cols;
    if(inImg.channels()>1)
        inImg = getGrayscaleImg(inImg);

    /*
    clock_t end1 = clock();
    double elapsed_secs = double(end1- begin) / CLOCKS_PER_SEC;
    cout << "FirstPhase "<< elapsed_secs << endl;*/

    int kernelSize = 9;
    vector<int> kernel = getLaplacian(kernelSize);
    /*
    clock_t end2 = clock();
    elapsed_secs = double(end2- end1) / CLOCKS_PER_SEC;
    cout << "SecondPhase "<< elapsed_secs << endl;

     */
    if(kernel.size()!= kernelSize*kernelSize)
        kernelSize = (int)sqrt(kernel.size());
    Mat laplacianed = convolve2D(inImg, kernel, kernelSize);
    /*
    clock_t end3 = clock();
    elapsed_secs = double(end3- end2) / CLOCKS_PER_SEC;
    cout << "ThirdPhase "<< elapsed_secs << endl;
     */

    Mat varianceOfLaplacians= getVariance(laplacianed, 3);
    /*
    clock_t end4 = clock();
    elapsed_secs = double(end4- end3) / CLOCKS_PER_SEC;
    cout << "FinalPhase "<< elapsed_secs << endl;
     */
    return varianceOfLaplacians;
}

Mat VarianceOfLaplacians::getVariance(Mat &inImg, int windowSize) {
    Mat dst = Mat::zeros(nRows, nCols, CV_64FC1);
    int windowHalf = windowSize/2;

    vector<int> varianceWindow(windowSize* windowSize);

    for(int row = windowHalf; row < nRows-windowHalf; ++row)
    {
        for(int col = windowHalf; col < nCols-windowHalf; ++col)
        {
            for(int i = -windowHalf; i <= windowHalf; ++i)
                for(int j = -windowHalf; j <= windowHalf; ++j) {
                    varianceWindow[windowSize * (i + windowHalf) + j + windowHalf] = inImg.at<double>(row + i, col + j);
                }

            double windowMean = (double)accumulate(varianceWindow.begin(), varianceWindow.end(), 0)/((double)varianceWindow.size());
            double variance = 0.0;
            for_each(varianceWindow.begin(), varianceWindow.end(), [&](int element){variance+=(element-windowMean)*(element-windowMean);});
            dst.at<double>(row, col) = variance;
        }
    }


    return dst;
}

vector<int> VarianceOfLaplacians::getLaplacian(int kernelsize) {
    vector<int> retVector(kernelsize*kernelsize);
    switch(kernelsize) {
        case 3:
            retVector = {0, -1, 0,
                         -1, 4, -1,
                         0, -1, 0};
            break;
        case 5:
            retVector = {0, 0, -1, 0, 0,
                         0, -1, -2, -1, 0,
                         -1, -2, 16, -2, -1,
                         0, -1, -2, -1, 0,
                         0, 0, -1, 0, 0};
            break;
        case 9:
            retVector = {0, 0, 3, 2, 2, 2, 3, 0, 0,
                         0, 2, 3, 5, 5, 5, 3, 2, 0,
                         3, 3, 5, 3, 0, 3, 5, 3, 3,
                         2, 5, 3, -12, -23, -12, 3, 5, 2,
                         2, 5, 0, -23, -40, -23, 0, 5, 2,
                         2, 5, 3, -12, -23, -12, 3, 5, 2,
                         3, 3, 5, 3, 0, 3, 5, 3, 3,
                         0, 2, 3, 5, 5, 5, 3, 2, 0,
                         0, 0, 3, 2, 2, 2, 3, 0, 0};
            break;
        default:
            retVector.resize(9);
            retVector = {0, -1, 0,
                         -1, 4, -1,
                         0, -1, 0};
    }
    return retVector;
}