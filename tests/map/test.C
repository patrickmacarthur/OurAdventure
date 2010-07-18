
/* map/test.C
 *
 * Author: Patrick MacArthur
 *
 * This file is a test for the CS516 Final Project
 */

#include <cstdlib>
#include <iostream>

#include "Adjacency.h"
#include "Carryable.h"
#include "Container.h"
#include "DirectionList.h"
#include "Feature.h"
#include "ItemFactory.h"
#include "Map.h"
#include "StartRoom.h"

// Get rid of this hack ASAP

/*class MockChest : public Chest
{
    public:
        virtual Item * clone() const;
        virtual void input( istream & s, Map * m );
        virtual void save( ostream & s ) const;
};

Item * MockChest::clone() const
{
    return new MockChest(*this);
}

void MockChest::input( istream & s, Map * m )
{
    std::cerr << "In MockChest::input()\n";
    Item::input(s, m);

    std::string dummy;
    getline( s, dummy );
}

void MockChest::save( ostream & s ) const
{
}*/

Feature * getExit( map<ID, Feature *>, Feature * r1, const Direction & dir );

int main()
{
    ItemFactory factory;
    factory.addItem( "directions", new DirectionList );
    factory.addItem( "consumable", new Consumable );
    factory.addItem( "key", new Key );
    factory.addItem( "treasure", new Treasure );
    factory.addItem( "pack", new Pack );
    factory.addItem( "box", new Box );
    factory.addItem( "chest", new Chest );
    factory.addItem( "room", new Room );
    factory.addItem( "passage", new Passage );
    factory.addItem( "doorway", new Door );
    factory.addItem( "lockableDoorway", new LockableDoor );
    factory.addItem( "adj", new Adjacency );
    factory.addItem( "start", new StartRoom );


    Map map( &factory );

    std::cout << "******* MAP TESTS ***********\n";
    std::cout << "Input and save test. Expected output same as input\n";
    // Input loop
    map.input( std::cin );

    // Save loop
    map.save( std::cout );

    /*std::cout << "Pretty-printed output (for each room)\n";
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
    std::cout << '\n';*/
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
