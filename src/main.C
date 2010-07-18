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

int main( int argc, char *argv[] )
{
    bool testMode = false;

    if ( argc == 1 )
    {
        testMode = false;
    }
    else if ( argc == 2 )
    {
        if ( strcmp(argv[1], "-t") == 0 )
        {
            testMode = true;
        }
        else
        {
            std::cerr << "Usage: " << argv[0] << " [-t]\n";
            exit(1);
        }
    }
    else if ( argc > 2 )
    {
        std::cerr << "Usage: " << argv[0] << " [-t]\n";
        exit(1);
    }


    Game g( testMode );
    g.run();

    return 0;
}

/* vim: set et sw=4 tw=65: */
