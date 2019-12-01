#ifndef __MATRIXM__
#define __MATRIXM__

class MatrixM{
public:
    static void identity(float *matrix, int width, int height);
    static void translate(float *matrix, int width, int height, float tx, float ty, float tz);
};

#endif
