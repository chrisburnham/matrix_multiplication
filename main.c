/*!
 *  \file   main.c
 *  \brief  Multiply two matricies
 */

#include <stdlib.h>
#include <stdio.h>
#include <Timer.h>

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
    fscanf( input_file, "%d", &size );

    // Allocate the arrays.
    floating_type *a = MATRIX_MAKE( size );

    // Get coefficients.
    for( size_t i = 0; i < size; ++i ) 
    {
      for( size_t j = 0; j < size; ++j ) 
      {
        fscanf( input_file, "%lf", MATRIX_GET_REF( a, size, i, j ) );
      }
    }
    fclose( input_file );

    Timer stopwatch;

    Timer_initialize( &stopwatch );
    Timer_start( &stopwatch );
    // TODO: Set up and run multiply here
    //int error = gaussian_solve_threaded(size, a, b, &pool, EType_barrier );
    Timer_stop( &stopwatch );

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

    // Clean up the dynamically allocated space.
    MATRIX_DESTROY( a );
    return EXIT_SUCCESS;
}
