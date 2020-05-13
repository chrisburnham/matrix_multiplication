/*!
 *  \file   main.c
 *  \brief  Multiply two matricies
 */

#include <stdlib.h>
#include <stdio.h>
#include <Timer.h>
#include <vector>

#include "matrix_multiply.h"

int main( int argc, char *argv[] )
{
    FILE *input_file; // TODO: Second file here
    int   size;

    if( argc != 2 ) // TODO: Need to use 3 here
    {
        printf( "Error: Expected the names of two matricies to multiply.\n" );
        return EXIT_FAILURE;
    }

    if( (input_file = fopen( argv[1], "r" )) == NULL ) 
    {
        printf("Error: Can not open the system definition file.\n");
        return EXIT_FAILURE;
    }

    // Get the size.
    printf("Reading file\n");
    fscanf( input_file, "%d", &size );

    printf("Found size %i\n", size);

    // Allocate the arrays.
    std::vector<std::vector<double> > matrix_a(size, 
                                               std::vector<double>(size));
    // TODO: Matrix B

    printf("Reading matrix\n");

    // Get coefficients.
    for( size_t i = 0; i < size; ++i ) 
    {
      for( size_t j = 0; j < size; ++j ) 
      {
        fscanf( input_file, "%lf", matrix_a[i][j]);
      }
    }
    fclose( input_file );

    printf("closing file\n");

    Timer stopwatch;

    Timer_initialize( &stopwatch );
    Timer_start( &stopwatch );
    // TODO: Set up and run multiply here
    //int error = gaussian_solve_threaded(size, a, b, &pool, EType_barrier );
    Timer_stop( &stopwatch );

    int error = 0;

    if( error ) 
    {
      // TODO: Error checking
      //printf( "System is degenerate\n" );
    }
    else {
    	// TODO: Print solution matrix
        //printf( "\nSolution is\n" );
        //for( int i = 0; i < size; ++i ) {
        //    printf( " x(%4d) = %9.5f\n", i, b[i] );
        //}

        printf( "\nExecution time = %ld milliseconds\n", Timer_time( &stopwatch ) );
    }

    // TODO: Write to a file?

    return EXIT_SUCCESS;
}
