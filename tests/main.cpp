#include "../include/dip.h"

using namespace dip;

int main(int argc, char const *argv[])
{
    Image image;
    image = imread("src/scaled_shapes.pgm");
    imwrite(image, "output.pgm");

    BlobColoring blob;
    blob.coloring(image, 0, 244);

    // image.printHistogram();

    return 0;
}
