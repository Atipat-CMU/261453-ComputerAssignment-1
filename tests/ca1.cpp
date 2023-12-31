#include "../include/dip.h"

#include <iostream>
#include <vector>
using namespace std;
using namespace dip;

int main(int argc, char const *argv[])
{
    Image image;
    image = imread("src/random_shape.pgm");
    // image.printHistogram();

    BlobColoring blobs(image, 0, 230);
    vector<Frame> frames = blobs.getComponents();

    cout << blobs.nums() << endl;

    // for(int i = 1; i <= blobs.nums(); i++){
    //     Mask obj = blobs.getLabelMask().toBinary(i);
    //     Moment obj_moment(obj);
    //     cout << "invariant of Object " << i << ": " << obj_moment.getInvariant() << endl;
    // }

    Image cropedImage = image.crop(frames[7]);
    imwrite(cropedImage, "out/crop.pgm");

    return 0;
}
