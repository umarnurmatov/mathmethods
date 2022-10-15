#include "polynomial_regression.hpp"

void Polynomial_regression::get_coeffs(std::vector<float>* coeff)
{
    int N = x.size();
    for(int m = 0; m < K + 1; m++)
    {
        for(int r = 0; r < K + 1; r++)
        {
            float sum_x_r = 0;
            for(int i = 0; i < N; i++) sum_x_r += pow(x[i], r + m);
            gsl_matrix_set(equasion_mat, m, r, sum_x_r);
        }
        float sum_x_y = 0;
        for(int i = 0; i < N; i++) sum_x_y += pow(x[i], m) * y[i];
        gsl_vector_set(equasion_vec, m, sum_x_y);
    }

    gsl_vector *_coeff = gsl_vector_alloc(K + 1);
    int s;
    gsl_permutation *p = gsl_permutation_alloc(K + 1);
    gsl_linalg_LU_decomp(equasion_mat, p, &s);

    gsl_linalg_LU_solve(equasion_mat, p, equasion_vec, _coeff);
    gsl_permutation_free(p);

    for(int i = 0; i < K + 1; i++) coeff->push_back(gsl_vector_get(_coeff, i));
    gsl_vector_free(_coeff);
}

// void print_mat_content(gsl_matrix *matrix)
// {
//     for (size_t i = 0; i < matrix->size1; i++) {
//         for (size_t j = 0; j < matrix->size2; j++) {
//             std::cout << gsl_matrix_get(matrix, i, j) << " ";
//         }
//         std::cout << std::endl;
//     }
// }
