/*!
 *  \file   main.c
 *  \brief  Multiply two matricies
 */

#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <chrono>
#include <ratio>
# include <cstdlib>
# include <ctime>
# include <iomanip>
# include <iostream>
#include <mpi.h>
#include <omp.h>

#include "matrix_multiply.h"

// Namespace shortcut
namespace chr = std::chrono;

void timestamp()
{
# define TIME_SIZE 40

  static char time_buffer[TIME_SIZE];
  const struct std::tm *tm_ptr;
  std::time_t now;

  now = std::time ( NULL );
  tm_ptr = std::localtime ( &now );

  std::strftime ( time_buffer, TIME_SIZE, "%d %B %Y %I:%M:%S %p", tm_ptr );

  std::cout << time_buffer << "\n";

  return;
# undef TIME_SIZE
}


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

    int id;
    int ierr;
    int p;
    double wtime;
  //
  //  Initialize MPI.
  //
    ierr = MPI_Init ( &argc, &argv );

    if ( ierr != 0 )
    {
      std::cout << "\n";
      std::cout << "HELLO_MPI - Fatal error!\n";
      std::cout << "  MPI_Init returned nonzero ierr.\n";
      exit ( 1 );
    }
  //
  //  Get the number of processes.
  //
    ierr = MPI_Comm_size ( MPI_COMM_WORLD, &p );
  //
  //  Get the individual process ID.
  //
    ierr = MPI_Comm_rank ( MPI_COMM_WORLD, &id );

    if ( id == 0 )
    {
      timestamp ( );
      std::cout << "\n";
      std::cout << "P" << id << ":  HELLO_MPI - Master process:\n";
      std::cout << "P" << id << ":    C++/MPI version\n";
      std::cout << "P" << id << ":    An MPI example program.\n";
      std::cout << "\n";
      std::cout << "P" << id << ":    The number of processes is " << p << "\n";
      std::cout << "\n";
    }
  //
  //  Every process prints a hello.
  //
    if ( id == 0 )
    {
      wtime = MPI_Wtime ( );
    }
    std::cout << "P" << id << ":    'Hello, world!'\n";
  //
  //  Process 0 says goodbye.
  //
    if ( id == 0 )
    {
      wtime = MPI_Wtime ( ) - wtime;
      std::cout << "P" << id << ":    Elapsed wall clock time = " << wtime << " seconds.\n";
    }
  //
  //  Terminate MPI.
  //
    MPI_Finalize ( );
  //
  //  Terminate.
  //
    if ( id == 0 )
    {
      std::cout << "\n";
      std::cout << "P" << id << ":  HELLO_MPI:\n";
      std::cout << "P" << id << ":    Normal end of execution.\n";
      std::cout << "\n";
      timestamp ( );
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

    printf("Running program with %i OMP threads\n",
           omp_get_num_threads());

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

      // Hacky quick check to see if matricies are about the same
      double sum = 0;
      for(size_t i = 0; i < size_a; i++)
      {
        for(size_t j = 0; j< size_a; j++)
        {
          sum += output.at(i).at(j);
        }
      }
      printf("Matrix Sum: %f\n", sum);
    }

    // TODO: Write to a file?

    return EXIT_SUCCESS;
}
