#include "../include/dip.h"

#include <iostream>
#include <vector>
using namespace std;

using namespace dip;

int main(int argc, char const *argv[])
{
    Image image;
    image = imread("src/cameraman.pgm");
    imwrite(image, "output.pgm");
    image.printHistogram();

    BlobColoring blob;
    vector<Frame> frames = blob.coloring(image, 0, 100);

    Image cropedImage = image.crop(frames[0]);
    imwrite(cropedImage, "output3.pgm");
    cropedImage.printHistogram();

    return 0;
}
