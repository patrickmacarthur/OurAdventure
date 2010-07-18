
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
#include "StartRoom.h"

Feature * getExit( map<ID, Feature *>, Feature * r1, const Direction & dir );

int main()
{
    using std::map;
    using std::pair;
    using std::string;
    map<ID, Feature *> features;
    map<ID, Feature *>::iterator rIter;
    Feature * feature;
    Adjacency * adj;
    StartRoom * start;
    Direction dir;
    string tag;

    std::cout << "******* PASSAGE TESTS ***********\n";
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
            feature->input( std::cin, 0 );
            features.insert( pair<ID, Feature *>(feature->getID(), feature) );
        }
        else if ( tag == "passage" )
        {
            feature = new Passage;
            feature->input( std::cin, 0 );
            features.insert( pair<ID, Feature *>(feature->getID(), feature) );
        }
        else if ( tag == "adj" )
        {
            adj = new Adjacency;
            adj->input( std::cin, 0 );
            rIter = features.find( adj->getFeatureID() );
            if ( rIter == features.end() )
            {
                std::cerr << "Unexpected input; exiting...\n";
                std::exit( 1 );
            }
            else
            {
                rIter->second->setExits( adj );
            }
        }
        else if ( tag == "start" )
        {
            start = new StartRoom;
            start->input( std::cin, 0 );
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

    std::cout << "Pretty-printed output (for each feature)\n";
    for ( rIter = features.begin(); rIter != features.end(); ++rIter )
    {
        rIter->second->printDescription( std::cout );
        std::cout << '\n';
    }

    rIter = features.find( start->getLocationID() );
    if ( rIter == features.end() )
    {
        std::cerr << "Start feature not defined; exiting...\n";
        std::exit( 1 );
    }
    else
    {
        std::cout << "\nNavigation tests: should be able to go back and forth through passage\n";
        feature = rIter->second;
        std::cout << "From feature: " << feature->getName() << '\n';

        Feature * passage = getExit( features, feature, Direction( "south" ) );
        Feature * feature2 = getExit( features, passage, Direction( "west" ) );
        feature2 = getExit( features, feature2, Direction( "east" ) );
        feature2 = getExit( features, feature2, Direction( "north" ) );

        std::cout << "Should be same: " << feature->getName()
                  << " " << feature2->getName();

        std::cout << "\n\nReentering passage and checking other directions (should be nothing).\n";
        getExit( features, passage, Direction( "east" ) );
        getExit( features, passage, Direction( "south" ) );
    }
    std::cout << '\n';
    return 0;
}

Feature * getExit( map<ID, Feature*> features, Feature * r1, const Direction & dir )
{
    std::cout << "Room " << dir << " of " << r1->getName() << ": ";

    ID * id = r1->getExitID( dir );
    if ( ! id )
    {
        std::cout << "(none)\n";
        return 0;
    }

    map<ID, Feature *>::iterator rIter;
    rIter = features.find( *id );
    if ( rIter == features.end() )
    {
        std::cerr << "Room not defined; exiting...\n";
        std::exit( 1 );
    }
    else
    {
        std::cout << rIter->second->getName() << '\n';
        return rIter->second;
    }
}
