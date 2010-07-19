/* main.C
 *
 * Author: Patrick MacArthur
 *
 * This file is part of the CS 516 Final Project
 */

#include <cstdlib>
#include <cstring>
#include <iostream>

#include "Game.h"

// Prints usage information
void usage( int argc, char *argv[] );

int main( int argc, char *argv[] )
{
    bool testMode = false;
    char * caveFile = 0;

    if ( argc == 1 )
    {
        testMode = false;
    }
    else
    {
        for ( int i = 1; i < argc; ++i )
        {
            if ( strcmp( argv[i], "-t" ) == 0 )
            {
                testMode = true;
            }
            else if ( strcmp( argv[i], "-c" ) == 0 )
            {
                if ( i + 1 < argc )
                {
                    caveFile = argv[i+1];
                    i++;
                }
                else
                {
                    usage( argc, argv );
                    exit(1);
                }
            }
            else
            {
                usage( argc, argv );
                exit(1);
            }
        }
    }

    if ( caveFile == 0 )
    {
        Game g( testMode );
        g.run();
    }
    else
    {
        Game g( testMode, caveFile );
        g.run();
    }

    return 0;
}

void usage( int argc, char *argv[] )
{
    std::cerr << "Usage: " << argv[0] << " [-t] [-c cavefile]\n";
}

/* vim: set et sw=4 tw=65: */
