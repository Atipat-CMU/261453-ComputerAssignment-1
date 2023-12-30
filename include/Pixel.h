#pragma once

#include <vector>
using namespace std;

namespace dip {

    class Pixel
    {
    private:
        int x_ = 0, y_ = 0;
    public:
        const int& x = x_;
        const int& y = y_;
        Pixel();
        Pixel(int, int);
        ~Pixel();
    };

    Pixel::Pixel()
    {
    }
    
    Pixel::Pixel(int x, int y)
    {
        this->x_ = x;
        this->y_ = y;
    }
    
    Pixel::~Pixel()
    {
    }
}
