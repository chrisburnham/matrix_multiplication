/*!
 * \file   matrix_multiply.h
 * \brief  Interface to matrix multiplier. Based on Peter Chapins
 *         linear equations solver
 */

#ifndef MATRIX_MULTIPLY_H
#define MATRIX_MULTIPLY_H

#include <stdlib.h>
#include <vector>
#include <stdexcept>

// Matrix shorthand
typedef std::vector<std::vector<double> > Matrix;

namespace Matrix_multiply
{
/**
         // TODO: Square matricies is just out of convience
 * @brief Multiply two square matricies and return the output
 * @param mat_a First matrix
 * @param mat_b Second matrix
 * @return Output matrix of the product
 * @throws runtime_error if the multiplication cannot be done
 */
Matrix Multiply_matricies(const Matrix& mat_a, const Matrix& mat_b);
}


#endif
