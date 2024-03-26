#include "../../include/dip.h"

using namespace std;
using namespace dip;

int main(int argc, char const *argv[])
{
    Image disgrid = imread("../src/ca4/distgrid.pgm");
    vector<Pixel> grid_points = gridFormTextFile("../src/ca4/distgrid.txt");
    Mask mask = gridBoxing(disgrid, grid_points);
    mask = mask.toBinary(1);
    imwrite(disgrid.mark(mask, 125), "../out/ca4/test.pgm");
    return 0;
}
