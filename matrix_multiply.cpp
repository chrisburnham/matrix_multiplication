///////////////////////////////////////////////////////////////////////

#include "matrix_multiply.h"

Matrix Matrix_multiply::Multiply_matricies(const Matrix &mat_a, const Matrix &mat_b)
{
  const size_t size = mat_a.size();

  if(mat_b.size() != size)
  {
    throw std::runtime_error("Matrix sizes need to be the same");
  }

  Matrix output_mat(size);

  for(size_t i = 0; i < size; i++)
  {
    // Will throw as well on size mismatch
    output_mat[i] = Multiply_row(mat_a.at(i), mat_b);
  }

  return output_mat;
}

///////////////////////////////////////////////////////////////////////

std::vector<double> Matrix_multiply::Multiply_row(const std::vector<double> &row, const Matrix &mat_b)
{
  if(row.size() != mat_b.size())
  {
    throw std::runtime_error("Matrix sizes do not match");
  }

  std::vector<double> output_row(row.size());

  for(size_t i = 0; i < row.size(); i++)
  {
    if(mat_b.at(i).size() != row.size())
    {
      throw std::runtime_error("Row size does not match");
    }

    double calc_val = 0;
    for(size_t j = 0; j < row.size(); j++)
    {
      calc_val += (row.at(j) * mat_b.at(j).at(i));
    }

    output_row[i] = calc_val;
  }

  return output_row;
}

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
