#include "MatrixM.hpp"

void MatrixM::identity(float *matrix, int width, int height){
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            matrix[i*height + j] = (i == j);
        }
    }
}
