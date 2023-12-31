#ifndef MASK_H
#define MASK_H

#include <vector>
using namespace std;

namespace dip  {
    class Mask
    {
    private:
        Vector2D<int> mask;
    public:
        Mask();
        Mask(int, int);
        ~Mask();

        int rows();
        int cols();

        void set(Pixel, int);

        int get(Pixel);
        bool isOutOfMask(Pixel);
    };
    
    Mask::Mask()
    {
    }

    Mask::Mask(int numrows, int numcols)
    {
        this->mask = Vector2D<int>(numrows, numcols);
    }
    
    Mask::~Mask()
    {
    }

    int Mask::rows(){
        return this->mask.rows();
    }

    int Mask::cols(){
        return this->mask.cols();
    }

    void Mask::set(Pixel p, int d){
        if(isOutOfMask(p)) return;
        this->mask.set(p.x, p.y, d);
    }

    int Mask::get(Pixel p){
        if(isOutOfMask(p)) return -1;
        return this->mask.get(p.x, p.y);
    }

    bool Mask::isOutOfMask(Pixel p){
        int x = p.x;
        int y = p.y;
        return !((0 <= x && x < this->rows()) && (0 <= y && y < this->cols()));
    }
    
}

#endif
