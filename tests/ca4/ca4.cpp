#include "../../include/dip.h"

#include <array>
#include <cmath>

using namespace std;
using namespace dip;

int main(int argc, char const *argv[])
{
    Image distlenna = imread("../src/ca4/distlenna.pgm");
    Image distgrid = imread("../src/ca4/distgrid.pgm");
    Image lenna(distlenna.rows(), distlenna.cols());

    vector<Pixel> distgrid_points = gridFormTextFile("../src/ca4/distgrid.txt");
    vector<Pixel> grid_points = gridFormTextFile("../src/ca4/grid.txt");

    Mask grid_labels = gridBoxing(distgrid, distgrid_points);
    imwrite(distgrid.mark(grid_labels, 125), "../out/ca4/test.pgm");

    array<vector<double>,16*16> w;
    array<bool, 16*16> isCalculate = {false};

    for(int row = 1; row <= distlenna.rows(); row++){
        for(int col = 1; col <= distlenna.cols(); col++){

            int label = grid_labels.get(row-1, col-1);

            if(!isCalculate[label-1]){
                int i = floor(label/16.0);
                int j = label - (i * 16) - 1;

                Pixel tl = grid_points[j + (i * (16+1))];
                tl = Pixel(tl.x()+1, tl.y()+1);
                Pixel tr = grid_points[(j + 1) + (i * (16+1))];
                tr = Pixel(tr.x()+1, tr.y()+1);
                Pixel bl = grid_points[j + ((i + 1) * (16+1))];
                bl = Pixel(bl.x()+1, bl.y()+1);
                Pixel br = grid_points[(j + 1) + ((i + 1) * (16+1))];
                br = Pixel(br.x()+1, br.y()+1);

                Pixel tl_d = distgrid_points[j + (i * (16+1))];
                tl_d = Pixel(tl_d.x()+1, tl_d.y()+1);
                Pixel tr_d = distgrid_points[(j + 1) + (i * (16+1))];
                tr_d = Pixel(tr_d.x()+1, tr_d.y()+1);
                Pixel bl_d = distgrid_points[j + ((i + 1) * (16+1))];
                bl_d = Pixel(bl_d.x()+1, bl_d.y()+1);
                Pixel br_d = distgrid_points[(j + 1) + ((i + 1) * (16+1))];
                br_d = Pixel(br_d.x()+1, br_d.y()+1);

                vector<double> A_tl = {(double)tl.x(), (double)tl.y(), (double)tl.x()*tl.y(), 1};
                vector<double> A_tr = {(double)tr.x(), (double)tr.y(), (double)tr.x()*tr.y(), 1};
                vector<double> A_bl = {(double)bl.x(), (double)bl.y(), (double)bl.x()*bl.y(), 1};
                vector<double> A_br = {(double)br.x(), (double)br.y(), (double)br.x()*br.y(), 1};

                vector<vector<double>> A = {A_tl, A_tr, A_bl, A_br};

                vector<double> b_x = {(double)tl_d.x(), (double)tr_d.x(), (double)bl_d.x(), (double)br_d.x()};
                vector<double> w_x = linear::gaussianElimination(A, b_x);

                vector<double> b_y = {(double)tl_d.y(), (double)tr_d.y(), (double)bl_d.y(), (double)br_d.y()};
                vector<double> w_y = linear::gaussianElimination(A, b_y);

                w[label - 1].reserve(w_x.size() + w_y.size());
                w[label - 1].insert(w[label - 1].end(), w_x.begin(), w_x.end());
                w[label - 1].insert(w[label - 1].end(), w_y.begin(), w_y.end());

                isCalculate[label - 1] = true;
            }

            int x_d = (int)(w[label - 1][0]*row + w[label - 1][1]*col + w[label - 1][2]*row*col + + w[label - 1][3]);
            int y_d = (int)(w[label - 1][4]*row + w[label - 1][5]*col + w[label - 1][6]*row*col + + w[label - 1][7]);
        
            lenna.set(row-1, col-1, distlenna.get(x_d-1, y_d-1));
        }
    }

    imwrite(lenna, "../out/ca4/lenna.pgm");
    return 0;
}
