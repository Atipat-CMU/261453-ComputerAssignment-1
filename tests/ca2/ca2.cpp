#include "../../include/dip.h"

using namespace std;
using namespace dip;

int eq_linear1(int x){
    return 1.5*x;
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
    return x + (0.005*x*(Dmax-x));
}

int eq_boostdown(int x, int Dmax){
    return x + (-0.005*x*(Dmax-x));
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
    Image image = imread("../src/ca2/SEM256_256.pgm");

    // Image imageL1 = poperation(image, eq_linear1);
    // imwrite(imageL1, "out/ca2/SEM256_256_eq_linear1.pgm");

    Image imageH = poperation(image, eq_boostdown);
    imageH = poperation(imageH, eq_equalize);
    imwrite(imageH, "../out/ca2/SEM256_256_best.pgm");

    return 0;
}
