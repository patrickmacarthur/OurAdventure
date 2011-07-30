#ifndef ADVENTURER_H
#define ADVENTURER_H

/*
    A class representing the adventurer. The adventurer's vital
    statistics are to be read from and written to files in
    the following format:

        healthLevel movesAtCurrentLevel numberItems weightItems
        itemId itemId ...
        currentFeatureId

    If one or more of the items is a pack, all of the
    adventurer's other items will be inside the largest pack.

    The adventurer has a set maximum health. Every 20 actions,
    his health level decreases by one and the amount of weight
    he may carry is decreased by 20% of a set maximum. If the
    adventurer is carrying more than currently allowed, he must
    drop items before he can interact with the environment. At
    health level 0, the game is over.

    Tom Harada
*/

#include <iostream>
#include <string>
#include <map>
using namespace std;

class Inventory;
class Feature;
class Map;
class Weight;

#include "Direction.h"

class Adventurer {
    public:
        Adventurer( Map * map );
            // constructor takes pointer to map

        ~Adventurer();
            // destructor

        void clear();
            // purges the inventory

        void input( istream& s );
            // reads adventurer's stats from stream

        void save( ostream& s ) const;
            // writes adventurer's stats in game-readable form

        void setHealth( const int v );
            // sets adventurer's health (up to the maximum)

        int getHealth() const;
            // returns adventurer's health

        int getMovesLeft() const;
            // returns moves left until health drop

        void setMovesLeft( int v );
            // sets moves left until health drop

        int move();
            // registers one move or action; adventurer's
            // health will decrease every 20 actions; returns
            // health

        Weight getStrength() const;
            // returns the amount of weight the adventurer
            // is currently able to carry, which varies
            // depending on health and determines whether
            // items must be dropped before adventurer can
            // do anything else

        bool isAlive() const;
            // Returns true if the adventurer is alive.

        Inventory * getInventory();
            // returns a pointer to the inventory

        void setInventory( Inventory * inv );
            // sets the inventory. Used to change between
            // hands and pack.

        Feature * getCurrentFeature() const;
            // returns pointer to current feature

        void setCurrentFeature( Feature * feat );
            // moves to specified feature

        Direction getPreviousDirection() const;
            // returns the previous direction

        void setPreviousDirection( const Direction& dir );
            // sets the previous direction

        enum { dyingHealth = 1, poorHealth = 2, averageHealth = 3,
            goodHealth = 4, highHealth = 5 };
            // health states

    private:
        Adventurer( const Adventurer& );
        Adventurer& operator = ( const Adventurer& );
            // copy and assignment not implemented

        Inventory * myInventory;
        int myHealth;
        int myMovesUntilHealthDrop;

        Map * myMap;
        Feature * myCurrentFeature;
        Direction myPreviousDirection;

        static int myMaxHealth;
        static int myMaxWeight;
        static int myMaxMovesUntilHealthDrop;
};

#endif
