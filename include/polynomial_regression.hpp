#pragma once
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_linalg.h>
#include <vector>
#include <cmath>
#include <iostream>

class Polynomial_regression
{
    std::vector<float> x;
    std::vector<float> y;

    gsl_matrix *equasion_mat;
    gsl_vector *equasion_vec;
    
    int K;

public:
    // _x size should be equal to _y!
    Polynomial_regression(std::vector<float>* _x, std::vector<float>* _y, int _K = 4)
    : K{_K}
    {   
        x = *_x;
        y = *_y;
        equasion_mat = gsl_matrix_alloc(K + 1, K + 1);
        equasion_vec = gsl_vector_alloc(K + 1);
    }

    void get_coeffs(std::vector<float>* coeff);

    ~Polynomial_regression()
    {
        gsl_vector_free(equasion_vec);
        gsl_matrix_free(equasion_mat);
    }
};