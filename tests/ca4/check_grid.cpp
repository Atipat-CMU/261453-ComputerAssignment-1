#include "../../include/dip.h"

using namespace std;
using namespace dip;

int main(int argc, char const *argv[])
{
    Image distgrid = imread("../src/ca4/distgrid.pgm");
    Image distlenna = imread("../src/ca4/distlenna.pgm");
    Mask grid_point(distgrid.rows(), distgrid.cols());
    grid_point.fromTextFile("../src/ca4/distgrid.txt", 1);
    imwrite(distgrid.highlight(grid_point), "../out/ca4/distgrid_mark.pgm");
    imwrite(distlenna.highlight(grid_point), "../out/ca4/distlenna_mark.pgm");
    return 0;
}
