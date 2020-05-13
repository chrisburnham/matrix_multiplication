/*!
 *  \file   main.c
 *  \brief  Multiply two matricies
 */

#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <chrono>
#include <ratio>

#include "matrix_multiply.h"

// Namespace shortcut
namespace chr = std::chrono;

int main( int argc, char *argv[] )
{
    FILE* file_a;
    FILE* file_b;
    int   size_a, size_b;

    if( argc != 3 )
    {
        printf( "Error: Expected the names of two matricies to multiply.\n" );
        return EXIT_FAILURE;
    }

    if( (file_a = fopen( argv[1], "r" )) == NULL )
    {
        printf("Error: Can not open the system definition file.\n");
        return EXIT_FAILURE;
    }

    // Get the size.
    printf("Reading file\n");
    fscanf( file_a, "%d", &size_a );

    printf("Found size %i\n", size_a);

    // Allocate the arrays.
    Matrix matrix_a(size_a,
           std::vector<double>(size_a));

    printf("Reading matrix\n");

    // Get coefficients.
    for( size_t i = 0; i < size_a; ++i )
    {
      for( size_t j = 0; j < size_a; ++j )
      {
        double tmp;
        fscanf( file_a, "%lf", &tmp);
        matrix_a[i][j] = tmp;
      }
    }
    printf("closing file A\n");
    fclose( file_a );

    if( (file_b = fopen( argv[2], "r" )) == NULL )
    {
        printf("Error: Can not open the system definition file.\n");
        return EXIT_FAILURE;
    }

    // Get the size.
    printf("Reading file\n");
    fscanf( file_b, "%d", &size_b );

    printf("Found size %i\n", size_b);

    if(size_a != size_b)
    {
      printf("Matrix sizes do not match\n");
      return EXIT_FAILURE;
    }

    // Allocate the arrays.
    Matrix matrix_b(size_b,
           std::vector<double>(size_b));

    printf("Reading matrix\n");

    // Get coefficients.
    for( size_t i = 0; i < size_b; ++i )
    {
      for( size_t j = 0; j < size_b; ++j )
      {
        double tmp;
        fscanf( file_b, "%lf", &tmp);
        matrix_b[i][j] = tmp;
      }
    }
    fclose( file_b );

    printf("closing file\n");

    auto start = chr::steady_clock::now();

    Matrix output;

    try
    {
      output = Matrix_multiply::Multiply_matricies(matrix_a, matrix_b);
    }
    catch(const std::exception& e)
    {
      printf("Error while running Matrix Multiply: %s\n",
             e.what());
    }
    
    auto end = chr::steady_clock::now();

    if(output.size() != 0) // We calculated something
    {
      chr::duration<double, std::milli> dur = end - start;
      //std::cout << dur.count();
      printf("\nExecution time = %f milliseconds\n", dur.count());

      for(size_t i = 0; i < size_a; i++)
      {
        for(size_t j = 0; j< size_a; j++)
        {
          printf("%f ", output.at(i).at(j));
        }
        printf("\n");
      }
    }

    // TODO: Write to a file?

    return EXIT_SUCCESS;
}
