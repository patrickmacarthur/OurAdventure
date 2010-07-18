
/* feature/test.C
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
    using std::pair;
    using std::string;
    std::map<ID, Feature *> features;
    std::map<ID, Feature *>::iterator rIter;
    Feature * feature;
    ItemFactory * factory = new ItemFactory;
    Map * map = new Map( factory );
    Adjacency * adj;
    StartRoom * start;
    StartRoom * end;
    Direction dir;
    string tag;

    std::cout << "******* DOOR TESTS ***********\n";
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
            feature = new Room;
            feature->input( std::cin, map );
            features.insert( pair<ID, Feature *>(feature->getID(), feature) );
            feature->addToMap( map );
        }
        else if ( tag == "doorway" )
        {
            feature = new Door;
            feature->input( std::cin, map );
            feature->addToMap( map );
            features.insert( pair<ID, Feature *>(feature->getID(), feature) );
        }
        else if ( tag == "adj" )
        {
            adj = new Adjacency;
            adj->input( std::cin, map );
            adj->addToMap( map );
        }
        else if ( tag == "start" )
        {
            start = new StartRoom;
            start->input( std::cin, 0 );
            start->addToMap( map );
        }
        else if ( tag == "end" )
        {
            end = new StartRoom;
            end->input( std::cin, 0 );
        }
    }

    // Save loop
    for ( rIter = features.begin(); rIter != features.end(); ++rIter )
    {
        rIter->second->save( std::cout );
        std::cout << '\n';
    }
    for ( rIter = features.begin(); rIter != features.end(); ++rIter )
    {
        rIter->second->saveExits( std::cout );
        std::cout << '\n';
    }
    start->save( std::cout );
    std::cout << '\n';

    std::cout << "\nNavigation tests:\n"
              << "The adventurer should be able to go through the open door\n"
              << "but should have to open the closed door before going through\n";
    rIter = features.find( start->getLocationID() );
    if ( rIter == features.end() )
    {
        std::cerr << "Start feature not defined; exiting...\n";
        std::exit( 1 );
    }
    feature = rIter->second;

    rIter = features.find( end->getLocationID() );
    if ( rIter == features.end() )
    {
        std::cerr << "Goal feature not defined; exiting...\n";
        std::exit( 1 );
    }
    Feature * goal = rIter->second;

    std::cout << "From feature: " << feature->getName() << '\n';
    std::cout << "Goal: " << goal->getName() << "\n\n";

    while ( feature->getID() != goal->getID() )
    {
        std::cout << "? detail\n";
        feature->printDescription( std::cout );
        std::cout << '\n';

        std::cout << "? go south\n";
        if ( feature->isOpen() )
        {
            Feature * next = getExit( features, feature, Direction( "south" ) );
            if ( ! next )
            {
                std::cout << "ERROR: No feature in that direction.\n";
                std::exit(1);
            }
            else
            {
                feature = next;
            }
        }
        else
        {
            std::cout << "The doorway is closed\n? open door\n";
            feature->openDoor();
        }
    }
    feature->printDescription( std::cout );
    std::cout << "\nReached goal.\n";

    delete factory;
    delete map;
    return 0;
}

Feature * getExit( map<ID, Feature*> features, Feature * r1, const Direction & dir )
{
    std::cout << "Room " << dir << " of " << r1->getName() << ": ";

    Feature * f = r1->getExit( dir );
    if ( ! f )
    {
        std::cout << "(none)\n";
        return 0;
    }
    else
    {
        std::cout << f->getName() << '\n';
        return f;
    }
}
