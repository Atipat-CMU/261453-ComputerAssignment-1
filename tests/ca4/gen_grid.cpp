#include "../../include/dip.h"

using namespace std;
using namespace dip;

int main(int argc, char const *argv[])
{
    Image grid = imread("../src/ca4/grid.pgm");
    Mask grid_point = gridIntersect(grid);
    grid_point.toTextFile("../src/ca4/test.txt", 1);
    return 0;
}
