#ifndef IMAGE_H
#define IMAGE_H

#include <vector>
#include <iostream>
using namespace std;

#include "Pixel.h"
#include "Frame.h"
#include "Vector2D.h"

namespace dip {

    class Image
    {
    private:
        Vector2D<unsigned int> image;
        Vector2D<char> raw_image;
        int histogram[256];
        int max_val = 0;

        void calHistogram();
        bool isOutOfImage(Pixel);
    public:
        Image();
        Image(int, int);
        Image(Vector2D<char>, Vector2D<unsigned int>);
        ~Image();

        // function
        int rows();
        int cols();
        int max();

        Vector2D<char> getRaw();
        Vector2D<unsigned int> get();

        int get(Pixel);
        int get(int, int);
        void printHistogram();

        Image crop(Frame);
    };

    Image::Image()
    {
    }

    Image::Image(int numrows, int numcols)
    {
        this->raw_image = Vector2D<char>(numrows, numcols);
        this->image = Vector2D<unsigned>(numrows, numcols);
        this->calHistogram();
    }

    Image::Image(Vector2D<char> raw_image, Vector2D<unsigned int> image)
    {
        this->raw_image = raw_image;
        this->image = image;
        this->calHistogram();
    }

    Image::~Image()
    {
    }

    int Image::rows(){
        return this->image.rows();
    }

    int Image::cols(){
        return this->image.cols();
    }

    int Image::max(){
        return this->max_val;
    }

    Vector2D<char> Image::getRaw(){
        return this->raw_image;
    }

    Vector2D<unsigned int> Image::get(){
        return this->image;
    }

    int Image::get(Pixel p){
        if(isOutOfImage(p)) return -1;
        return this->image.get(p.x, p.y);
    }

    int Image::get(int x, int y){
        return this->get(Pixel(x,y));
    }

    bool Image::isOutOfImage(Pixel p){
        int x = p.x;
        int y = p.y;
        return !(0 <= x && x < this->rows() && 0 <= y && y < this->cols());
    }

    void Image::calHistogram(){
        for(int i = 0; i < 256; i++){
            histogram[i] = 0;
        }
        for(int row = 0; row < this->rows(); ++row) {
            for(int col = 0; col < this->cols(); ++col) {
                int d = this->image.get(row, col);
                this->histogram[d]++;
                if(d > max_val) max_val = d;
            }
        }
    }

    void Image::printHistogram(){
        for(int i = 0; i < 256; i++){
            cout << i << ": " << this->histogram[i] << endl;
        }
    }

    Image Image::crop(Frame frame){
        Pixel top = frame.getTop();
        Pixel bottom = frame.getBottom();

        int c_rows = bottom.x-top.x+1;
        int c_cols = bottom.y-top.y+1;

        Vector2D<char> raw_cropedImage = raw_image.crop(top.x, top.y, bottom.x, bottom.y);
        Vector2D<unsigned int> cropedImage = image.crop(top.x, top.y, bottom.x, bottom.y);

        return Image(raw_cropedImage, cropedImage);
    }
}

#endif
