#ifndef ITEMFACTORY_H
#define ITEMFACTORY_H

/*
    A factory for producing (cloning) items. The items to be
    cloned should be added to its registry by the game.

    Tom Harada
*/

#include <iostream>
#include <string>
#include <map>
using namespace std;

class Item;

class ItemFactory {
    public:
        ~ItemFactory();
            // cleans up the prototype map

        void addItem( string key, Item * item );
            // keys the given item pointer to the specified
            // string in the prototype map

        Item * generate( const string& type );
            // returns a pointer to a fresh item of the
            // specified type

        void save( ostream& s ) const;
            // writes the prototype list to the stream

        void input( istream& s );
            // reads the prototype list from stream

    private:
        map<string, Item *> myPrototypes;
};

ostream& operator << ( ostream& s, const ItemFactory &fac );
    // outputs using save operation

istream& operator >> ( istream& s, ItemFactory fac );
    // inputs using named input operation

#endif
