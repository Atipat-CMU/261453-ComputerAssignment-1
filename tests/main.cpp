#include "../include/dip.h"
#include <iostream>
#include <vector>
using namespace std;

using namespace dip;

int main(int argc, char const *argv[])
{
    Image image;
    image = imread("src/scaled_shapes.pgm");
    imwrite(image, "output.pgm");

    BlobColoring blob;
    blob.coloring(image, 0, 254);
    
    return 0;
}
