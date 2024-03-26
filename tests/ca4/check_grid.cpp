#include "../../include/dip.h"

using namespace std;
using namespace dip;

int main(int argc, char const *argv[])
{
    Image disgrid = imread("../src/ca4/distgrid.pgm");
    Mask grid_point(disgrid.rows(), disgrid.cols());
    grid_point.fromTextFile("disgrid.txt", 1);
    imwrite(disgrid.highlight(grid_point), "../out/ca4/distgrid_mark.pgm");
    return 0;
}
