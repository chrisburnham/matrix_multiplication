/*!
 *  \file   main.cpp
 *  \brief  Main program of the matrix multiply creator. Modified from Peter Chapins version
 *          for linear equations
 *  \author (C) Copyright 2011 by Peter C. Chapin <pchapin@vtc.edu>
 *
 * This program creates a random square matrix
 *
 * Build this program using the command:
 *
 *    $ g++ -o create_square_matrix -Wall create_square_matrix.cpp
 *
 * Run the program to create a system of a certain size (say 100x100) using the command:
 *
 *    $ ./create_square_matrix 100 > 100x100.dat
 *
 */

#include <cstdlib>
#include <iomanip>
#include <iostream>

using namespace std;

//! Generate a random double in the range -1.0 < x < 1.0
double generate_value( )
{
    double value = static_cast<double>( rand( ) ) / RAND_MAX;
    return (2.0 * value) - 1.0;
}


int main( int argc, char **argv )
{
    int size;

    // Check command line validity.
    if( argc != 2 ) {
        cerr << "Usage: " << argv[0] << " size\n";
        return EXIT_FAILURE;
    }

    // Convert size argument to an integer.
    size = atoi( argv[1] );

    // Check the sanity of the size argument.
    if( size <= 0 ) {
        cerr << "Invalid system size specified: " << size << "\n";
        return EXIT_FAILURE;
    }

    cout << size << "\n";

    // For each equation...
    for( int i = 1; i <= size; ++i ) {

        // Output a coefficient for each unknown.
        for( int j = 1; j <= size; ++j ) {
            cout << setw( 18 ) << setprecision( 15 ) << fixed << generate_value( ) << "\n";
        }

        // Output the driving vector value for this equation.
        // cout << setw( 18 ) << setprecision( 15 ) << fixed << generate_value( ) << "\n";
    }
    return EXIT_SUCCESS;
}
