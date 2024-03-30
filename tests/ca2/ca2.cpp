#include "../../include/dip.h"

using namespace std;
using namespace dip;

int eq_linear1(int x){
    return 2*x;
}

int eq_equalize(int x, int Dmax){
    return x*(255.0/Dmax);
}

int eq_offsetup(int x, int Dmax){
    return x+(255-Dmax);
}

int eq_inverse(int x, int Dmax){
    return Dmax-x;
}

int eq_boostup(int x, int Dmax){
    return x + (0.01*x*(Dmax-x));
}

int eq_boostdown(int x, int Dmax){
    return x + (-0.00001*x*(Dmax-x));
}

int eq_sinC96(int x, int Dmax){
    return (Dmax/2.0)*(1+( (1/sin(1*M_PI/2)) * sin(1*M_PI*( (float(x)/Dmax)-0.5 )) ));
}

int eq_tanC96(int x, int Dmax){
    return (Dmax/2.0)*(1+( (1/tan(0.5*M_PI/2)) * tan(0.5*M_PI*( (float(x)/Dmax)-0.5 )) ));
}

int eq_light(int x){
    return 50*log(1+x);
}

int main(int argc, char const *argv[])
{
    Image image1 = imread("../src/ca2/Cameraman.pgm");
    Image imageL1 = poperation(image1, eq_tanC96);
    imageL1 = poperation(image1, eq_sinC96);
    imwrite(imageL1, "../out/ca2/Cameraman_eq_mix_95.pgm");

    Image image2 = imread("../src/ca2/SEM256_256.pgm");
    Image imageL2 = poperation(image2, eq_tanC96);
    imwrite(imageL2, "../out/ca2/SEM256_256_eq_tanC96.pgm");

    Image image_cam = imread("../src/ca2/Cameraman.pgm");
    Image imageH1 = poperation(image_cam, eq_light);
    imageH1 = poperation(imageH1, eq_boostdown);
    imwrite(imageH1, "../out/ca2/Cameraman_best2.pgm");

    Image image_sem = imread("../src/ca2/SEM256_256.pgm");
    Image imageH2 = equalizeHist(image_sem);
    imageH2 = poperation(imageH2, eq_tanC96);
    
    imwrite(imageH2, "../out/ca2/SEM256_256_best.pgm");

    return 0;
}
