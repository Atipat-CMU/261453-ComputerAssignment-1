#pragma once

#include "object/Image.h"

namespace dip {
    Image poperation(Image image, int (*fun)(int)){
        Vector2D<unsigned int> new_image = Vector2D<unsigned int>(image.rows(), image.cols());

        for(int row = 0; row < image.rows(); row++){
            for(int col = 0; col < image.cols(); col++){
                int d = fun(image.get(row, col));
                if(d < 0) d = 0;
                if(d > 255) d = 255;
                new_image.set(row, col, d);
            }
        }

        return Image(new_image);
    }

    Image poperation(Image image, int (*fun)(int, int)){
        Vector2D<unsigned int> new_image = Vector2D<unsigned int>(image.rows(), image.cols());

        for(int row = 0; row < image.rows(); row++){
            for(int col = 0; col < image.cols(); col++){
                int d = fun(image.get(row, col), image.max());
                if(d < 0) d = 0;
                if(d > 255) d = 255;
                new_image.set(row, col, d);
            }
        }

        return Image(new_image);
    }
}
