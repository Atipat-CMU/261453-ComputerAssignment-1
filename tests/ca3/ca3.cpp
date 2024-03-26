#include "../include/dip.h"

using namespace std;
using namespace dip;

int main(int argc, char const *argv[])
{
    Image b = imread("src/ca3/SanFranPeak_blue.pgm");
    Image r = imread("src/ca3/SanFranPeak_red.pgm");
    Image g = imread("src/ca3/SanFranPeak_green.pgm");

    Image result = (2.0*r);
    result = result-r;
    imwrite(result, "out/ca3/test1.pgm");
    return 0;
}
