#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "Image.h"

using namespace std;

namespace dip {
    Image imread(string filename){
        int count = 0;

        string version;
        int numrows = 0, numcols = 0;
        int max_val;

        ifstream file(filename, ios::binary);
        stringstream ss;
        stringstream temp;    
        string line;

        if (!file.is_open()) {
            throw runtime_error("File not found: " + filename);
        }

        while (getline(file, line))
        {
            if(line[0] != '#'){
                if(count == 0){ version = line; }
                if(count == 1){ temp << line; temp >> numcols >> numrows; }
                if(count == 2){ temp.clear(); temp << line; temp >> max_val; }
                count++;
            }
            if(count == 3) break;
        }
        
        int imsize = 0;

        vector<vector<unsigned int>> image;
        vector<char> raw_image;
        raw_image.reserve(numcols * numrows);

        char pixel;

        for(int row = 0; row < numrows; row++){
            vector<unsigned int> v_row;
            for(int col = 0; col < numcols; col++){
                file.read(&pixel, 1);
                v_row.push_back(static_cast<int>(static_cast<unsigned char>(pixel)));
                raw_image.push_back(pixel);
            }
            image.push_back(v_row);
        }
        file.close();

        return Image(raw_image, image, numrows, numcols, max_val);
    }

    void imwrite(Image image, string filename){
        ofstream file(filename, std::ios::binary);
        file << "P5" << endl;
        file << image.cols() << " " << image.rows() << endl;
        file << image.max() << endl;
        file.write(image.getRaw().data(), image.getRaw().size());
        file.close();
    }

    void imshow(Image image){
        for(int row = 0; row < image.rows(); ++row) {
            for(int col = 0; col < image.cols(); ++col) {
                cout << image.get()[row][col] << " ";
            }
            cout << endl;
        }
    }
}
