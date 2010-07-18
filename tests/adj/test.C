/* adj/test.C
 *
 * Author: Patrick MacArthur
 *
 * This file is a test for the CS516 Final Project
 */

#include <iostream>

#include "Adjacency.h"
#include "Feature.h"
#include "Map.h"

//--------------------------------------------------------------
//         Mock classes for unit testing purposes
//--------------------------------------------------------------
class MockFeature : public Feature
{
    public:
        explicit MockFeature( const ID & id ) : m_id( id ) {}
          // Constructor

        const ID & getID() const { return m_id; }
          // Returns ID

    private:
        ID m_id;
};

//--------------------------------------------------------------
//         Testing main
//--------------------------------------------------------------
void printExit( Adjacency & adj, const Direction & dir );

int main()
{
    Adjacency v;
    ID id;
    Map map(0);
    cin >> id;
    Feature * r1 = new MockFeature( id );
    r1->addToMap( &map );
    cin >> id;
    Feature * r2 = new MockFeature( id );
    r2->addToMap( &map );
    cin >> id;
    Feature * r3 = new MockFeature( id );
    r3->addToMap( &map );

    std::cout << "******* ADJACENCY TESTS ***********\n";
    std::cout << "Input and save test. Expected output same as last "
              << "line of input plus tag\n";
    v.input( std::cin, &map );
    v.save( std::cout );
    std::cout << '\n';

    std::cout << "\nPretty-printed output (should list only exits "
              << "that are valid above)\n";
    v.printDescription( std::cout );

    std::cout << "\nDirection checks: Should be similar to above\n";
    printExit( v, Direction("north") );
    printExit( v, Direction("east") );
    printExit( v, Direction("south") );
    printExit( v, Direction("west") );
    return 0;
}

void printExit( Adjacency & adj, const Direction & dir )
{
    std::cout << dir << " exit:\t";
    Feature * f = adj.getExit( dir );
    if ( f == 0 )
    {
        std::cout << "(none)\n";
    }
    else
    {
        std::cout << f->getID() << '\n';
    }
}

