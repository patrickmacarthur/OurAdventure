
/* start/test.C
 *
 * Author: Patrick MacArthur
 *
 * This file is a test for the CS516 Final Project
 */

#include <iostream>

#include "StartRoom.h"

std::string boolToString( bool );

int main()
{
    StartRoom v;
    std::cout << "********* StartRoom TESTS **************\n";
    std::cout << "Input and save test. Expected output same as input plus tag\n";
    v.input( std::cin, 0 );
    v.save( std::cout );
    std::cout << '\n';

    std::cout << "Contents test.  Expected output same as input without tag\n"
              << v.getLocationID() << '\n';
    return 0;
}

std::string boolToString( bool v )
{
    return ( v ) ? "true" : "false";
}

