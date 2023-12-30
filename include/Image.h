#pragma once

#include <vector>
using namespace std;

#include "Pixel.h"
#include "Frame.h"

namespace dip {

    class Image
    {
    private:
        vector<vector<unsigned int>> image;
        vector<vector<char>> raw_image;
        int histogram[256];
        int numrows, numcols;
        int max_val;

        void calHistogram();
    public:
        Image();
        Image(vector<vector<char>>, vector<vector<unsigned int>>, int, int, int);
        Image(vector<vector<unsigned int>>, int, int, int);
        ~Image();

        // function
        int rows();
        int cols();
        int max();

        vector<vector<char>> getRaw();
        vector<vector<unsigned int>> get();

        int get(Pixel);
        bool isOutOfImage(Pixel);
        void printHistogram();

        Image crop(Frame);
    };

    Image::Image()
    {
    }

    Image::Image(vector<vector<char>> raw_image, vector<vector<unsigned int>> image, int numrows, int numcols, int max_val)
    {
        this->raw_image = raw_image;
        this->image = image;
        this->numrows = numrows;
        this->numcols = numcols;
        this->max_val = max_val;
        calHistogram();
    }

    Image::Image(vector<vector<unsigned int>> image, int numrows, int numcols, int max_val)
    {
        this->image = image;
        this->numrows = numrows;
        this->numcols = numcols;
        this->max_val = max_val;
        calHistogram();
    }

    Image::~Image()
    {
    }

    int Image::rows(){
        return this->numrows;
    }

    int Image::cols(){
        return this->numcols;
    }

    int Image::max(){
        return this->max_val;
    }

    vector<vector<char>> Image::getRaw(){
        return this->raw_image;
    }

    vector<vector<unsigned int>> Image::get(){
        return this->image;
    }

    int Image::get(Pixel p){
        if(isOutOfImage(p)) return -1;
        return this->image[p.x][p.y];
    }

    bool Image::isOutOfImage(Pixel p){
        int x = p.x;
        int y = p.y;
        return !(0 <= x && x < numrows && 0 <= y && y < numcols);
    }

    void Image::calHistogram(){
        for(int i = 0; i < 256; i++){
            histogram[i] = 0;
        }
        for(int row = 0; row < this->numrows; ++row) {
            for(int col = 0; col < this->numcols; ++col) {
                this->histogram[this->image[row][col]]++;
            }
        }
    }

    void Image::printHistogram(){
        for(int i = 0; i < 256; i++){
            cout << i << ": " << histogram[i] << endl;
        }
    }

    Image Image::crop(Frame frame){
        Pixel top = frame.getTop();
        Pixel bottom = frame.getBottom();

        int c_rows = bottom.x-top.x+1;
        int c_cols = bottom.y-top.y+1;

        vector<vector<char>> raw_cropedImage;

        raw_cropedImage.resize(c_rows, vector<char>(c_cols));

        for(int row = 0; row < c_rows; ++row) {
            for(int col = 0; col < c_cols; ++col) {
                raw_cropedImage[row][col] = image[top.x+row][top.y+col];
            }
        }

        return Image(raw_cropedImage, image, c_rows, c_cols, max_val);
    }
}
