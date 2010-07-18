
/* room/test.C
 *
 * Author: Patrick MacArthur
 *
 * This file is a test for the CS516 Final Project
 */

#include <cstdlib>
#include <iostream>

#include "Adjacency.h"
#include "Carryable.h"
#include "Feature.h"
#include "ItemFactory.h"
#include "Map.h"
#include "StartRoom.h"

//--------------------------------------------------------------
//         Mock classes for unit testing purposes
//--------------------------------------------------------------
class MockCarryable : public Carryable
{
    public:
        const ID & getID() const { return m_id; }
          // Returns ID

        const Name & getName() const { return m_name; }
          // Returns name

        void input( istream & s, Map * map );
          // Inputs the item
    private:
        ID m_id;
        Name m_name;
};

void MockCarryable::input( istream & s, Map * m )
{
    s >> m_id >> m_name;
}

//--------------------------------------------------------------
//         Testing main
//--------------------------------------------------------------
Feature * getExit( map<ID, Feature *>, Feature * r1, const Direction & dir );

int main()
{
    using std::map;
    using std::pair;
    using std::string;
    ItemFactory f;
    Map * m = new Map(&f);
    ID toMove;
    map<ID, Feature *> rooms;
    map<ID, Feature *>::iterator rIter;
    Feature * room;
    Adjacency * adj;
    StartRoom * start;
    Direction dir;
    string tag;

    std::cout << "******* ROOM TESTS ***********\n";
    std::cout << "Input and save test. Expected output same as input\n";
    // Input loop
    while ( cin >> tag )
    {
        if ( tag == "feature" )
        {
            continue;
        }
        if ( tag == "item" )
        {
            Carryable * c = new MockCarryable;
            c->input( std::cin, m );
            c->addToMap( m );
        }
        if ( tag == "toMove" )
        {
            toMove.input( std::cin );
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
        std::cout << "--\n";
    }

    rIter = rooms.find( start->getLocationID() );
    if ( rIter == rooms.end() )
    {
        std::cerr << "Start room not defined; exiting...\n";
        std::exit( 1 );
    }
    else
    {
        std::cout << "\nGet/drop test: should move item1 from r1 to r2\n";
        room = rIter->second;

        std::cout << "? take item1\n";
        Carryable * i1 = m->getCarryableItem( toMove );
        if ( room->removeItem( i1 ) )
        {
            std::cout << "Got " << i1->getName() << "\n";
        }
        else
        {
            std::cout << "ERROR: Could not get item\n";
            std::exit( 1 );
        }

        std::cout << "? go south\n";
        room = getExit( rooms, room, Direction( "north" ) );

        std::cout << "? drop item1\n";
        if ( room->addItem( i1 ) )
        {
            std::cout << "Dropped " << i1->getName() << "\n";
        }
        else
        {
            std::cout << "ERROR: Could not drop item\n";
            std::exit( 1 );
        }
    }


    // Save loop
    std::cout << "Saving rooms.  Should be same as rooms above with i1 in r2\n";
    for ( rIter = rooms.begin(); rIter != rooms.end(); ++rIter )
    {
        rIter->second->save( std::cout );
        std::cout << '\n';
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
