
/* dirlist/test.C
 *
 * Author: Patrick MacArthur
 *
 * This file is a test for the CS516 Final Project
 */

#include <iostream>
#include <string>

#include "Direction.h"
#include "DirectionList.h"

std::string boolToString( bool );

int main()
{
    DirectionList list;
    std::cout << "********** DIRECTIONLIST TESTS ************\n";
    std::cout << "Input/output test.\n";
    list.input( std::cin, 0 );
    std::cout << "save(): ";
    list.save( std::cout );
    std::cout << "printDescription(): ";
    list.printDescription( std::cout );
    std::cout << '\n';

    std::cout << "Validity tests.";
    std::cout << "\nisValid( \"north\" )\t"
              << boolToString(list.isValid(Direction("north")));
    std::cout << "\nisValid( \"south\" )\t"
              << boolToString(list.isValid(Direction("south")));
    std::cout << "\nisValid( \"east\" )\t"
              << boolToString(list.isValid(Direction("east")));
    std::cout << "\nisValid( \"west\" )\t"
              << boolToString(list.isValid(Direction("west")));
    std::cout << "\nisValid( \"up\" )\t"
              << boolToString(list.isValid(Direction("up")));
    std::cout << '\n';
    return 0;
}

std::string boolToString( bool v )
{
    return ( v ) ? "true" : "false";
}

