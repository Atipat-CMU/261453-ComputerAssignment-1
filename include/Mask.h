#pragma once

#include <vector>
using namespace std;

namespace dip  {
    class Mask
    {
    private:
        vector<vector<int>> mask;
        int numrows = 0, numcols = 0;
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
        this->numrows = numrows;
        this->numcols = numcols;

        for(int x = 0; x < numrows; x++){
            vector<int> row;
            for(int y = 0; y < numcols; y++){
                row.push_back(0);
            }
            this->mask.push_back(row);
        }
    }
    
    Mask::~Mask()
    {
    }

    int Mask::rows(){
        return this->numrows;
    }

    int Mask::cols(){
        return this->numcols;
    }

    void Mask::set(Pixel p, int d){
        if(isOutOfMask(p)) return;
        this->mask[p.x][p.y] = d;
    }

    int Mask::get(Pixel p){
        if(isOutOfMask(p)) return -1;
        return this->mask[p.x][p.y];
    }

    bool Mask::isOutOfMask(Pixel p){
        int x = p.x;
        int y = p.y;
        return !((0 <= x && x < numrows) && (0 <= y && y < numcols));
    }
    
}
