#include "MatrixM.hpp"

void MatrixM::identity(float *matrix, int width, int height){
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            matrix[i*height + j] = (i == j);
        }
    }
}

void MatrixM::translate(float *matrix, int width, int height, float tx, float ty, float tz){
    matrix[3 * height] += tx;
    matrix[3 * height + 1] += ty;
    matrix[3 * height + 2] += tz;
}
