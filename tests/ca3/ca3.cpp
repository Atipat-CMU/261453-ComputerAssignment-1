#include "../../include/dip.h"

using namespace std;
using namespace dip;

int main(int argc, char const *argv[])
{
    Image b = imread("../src/ca3/SanFranPeak_blue.pgm");
    Image r = imread("../src/ca3/SanFranPeak_red.pgm");
    Image g = imread("../src/ca3/SanFranPeak_green.pgm");

    Image result1 = (3.0*g)+(2.0*r)-(5.0*b);
    imwrite(result1, "../out/ca3/findplant.pgm");

    Image result2 = b-(2.0*((g-(b/3)+(r-(b/3)))));
    imwrite(result2, "../out/ca3/findsky.pgm");
    return 0;
}
