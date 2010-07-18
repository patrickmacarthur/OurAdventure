
/* dir/test.C
 *
 * Author: Patrick MacArthur
 *
 * This file is a test for the CS516 Final Project
 */

#include <iostream>

#include "Direction.h"

std::string boolToString( bool );

int main()
{
    Direction d;
    std::cout << "********** DIRECTION TESTS ************\n";
    std::cout << "Input/output test\n";
    d.input( std::cin );
    d.output( std::cout );
    std::cout << '\n';

    std::cout << "Tests of comparision operators (should alternate T/F)\n";
    Direction d1("1");
    Direction d1b("1");
    Direction d2("2");
    std::cout << "1 == 1\t" << boolToString(d1 == d1b);
    std::cout << "\n1 == 2\t" << boolToString(d1 == d2);
    std::cout << "\n1 != 2\t" << boolToString(d1 != d2);
    std::cout << "\n1 != 1\t" << boolToString(d1 != d1b);
    std::cout << "\n1 < 2\t" << boolToString(d1 < d2);
    std::cout << "\n2 < 1\t" << boolToString(d2 < d1);
    std::cout << "\n1 <= 2\t" << boolToString(d1 <= d2);
    std::cout << "\n2 <= 1\t" << boolToString(d2 <= d1);
    std::cout << "\n2 > 1\t" << boolToString(d2 > d1);
    std::cout << "\n1 > 2\t" << boolToString(d1 > d2);
    std::cout << "\n2 >= 1\t" << boolToString(d2 >= d1);
    std::cout << "\n1 >= 2\t" << boolToString(d1 >= d2);
    std::cout << '\n';
    return 0;
}

std::string boolToString( bool v )
{
    return ( v ) ? "true" : "false";
}

