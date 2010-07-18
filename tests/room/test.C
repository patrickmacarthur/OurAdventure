
/* room/test.C
 *
 * Author: Patrick MacArthur
 *
 * This file is a test for the CS516 Final Project
 */

#include <cstdlib>
#include <iostream>

#include "Adjacency.h"
#include "Feature.h"
#include "ItemFactory.h"
#include "Map.h"
#include "StartRoom.h"

Feature * getExit( map<ID, Feature *>, Feature * r1, const Direction & dir );

int main()
{
    using std::map;
    using std::pair;
    using std::string;
    ItemFactory f;
    Map * m = new Map(&f);
    map<ID, Feature *> rooms;
    map<ID, Feature *>::iterator rIter;
    Feature * room;
    Adjacency * adj;
    StartRoom * start;
    Direction dir;
    string tag;

    std::cout << "******* ROOM TESTS ***********\n";
    std::cout << "Input and save test. Expected output same as input plus tag\n";
    // Input loop
    while ( cin >> tag )
    {
        if ( tag == "feature" )
        {
            continue;
        }
        else if ( tag == "room" )
        {
            room = new Room;
            room->input( std::cin, m );
            rooms.insert( pair<ID, Feature *>(room->getID(), room) );
            m->add( room );
        }
        else if ( tag == "adj" )
        {
            adj = new Adjacency;
            adj->input( std::cin, m );
            rIter = rooms.find( adj->getFeatureID() );
            if ( rIter == rooms.end() )
            {
                std::cerr << "Unexpected input; exiting...\n";
                std::exit( 1 );
            }
            else
            {
                rIter->second->setExits( adj );
            }
            m->add( adj );
        }
        else if ( tag == "start" )
        {
            start = new StartRoom;
            start->input( std::cin, m );
            m->add( start );
        }
    }

    // Save loop
    for ( rIter = rooms.begin(); rIter != rooms.end(); ++rIter )
    {
        rIter->second->save( std::cout );
        std::cout << '\n';
    }
    for ( rIter = rooms.begin(); rIter != rooms.end(); ++rIter )
    {
        rIter->second->saveExits( std::cout );
        std::cout << '\n';
    }
    start->save( std::cout );
    std::cout << '\n';

    std::cout << "Pretty-printed output (for each room)\n";
    for ( rIter = rooms.begin(); rIter != rooms.end(); ++rIter )
    {
        rIter->second->printDescription( std::cout );
        std::cout << '\n';
    }

    rIter = rooms.find( start->getLocationID() );
    if ( rIter == rooms.end() )
    {
        std::cerr << "Start room not defined; exiting...\n";
        std::exit( 1 );
    }
    else
    {
        std::cout << "\nNavigation tests (compare with list above)\n";
        room = rIter->second;
        std::cout << "From room: " << room->getName() << '\n';

        Feature * room2 = getExit( rooms, room, Direction( "north" ) );
        getExit( rooms, room, Direction( "south" ) );

        std::cout << "From room: " << room2->getName() << '\n';

        getExit( rooms, room2, Direction( "north" ) );
        Feature * room3 = getExit( rooms, room2, Direction( "south" ) );
        std::cout << "Should be same: " << room->getName()
                  << " " << room3->getName();
    }
    std::cout << '\n';
    delete m;
    return 0;
}

Feature * getExit( map<ID, Feature*> rooms, Feature * r1, const Direction & dir )
{
    std::cout << "Room " << dir << " of " << r1->getName() << ": ";

    Feature * other = r1->getExit( dir );
    if ( ! other )
    {
        std::cout << "(none)\n";
        return 0;
    }
    else
    {
        std::cout << other->getName() << '\n';
        return other;
    }
}
