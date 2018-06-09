#include "Image.hpp"

Image& Image::grayImg() {
    if(channels == 1)
        return *this;
    else
    {
        Image dstImg(nRows,nCols,1);
        int size = nRows*nCols;
        for (int i = 0; i < size; ++i) {
            dstImg.pixels[i] = pixels[i];
        }
    }
}