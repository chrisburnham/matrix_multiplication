///////////////////////////////////////////////////////////////////////

#include "matrix_multiply.h"

Matrix Matrix_multiply::Multiply_matricies(const Matrix &mat_a, const Matrix &mat_b)
{
  const size_t size = mat_a.size();

  if(mat_b.size() != size)
  {
    throw std::runtime_error("Matrix sizes need to be the same");
  }

  // TODO: Need to check second dimension as we work through

}

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
