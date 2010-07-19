#ifndef GAME_H
#define GAME_H

/*
    Main class for the adventure game.
    
    Loading and saving the game is done by referring to a
    save state description, which corresponds in a save state
    list file to an adventurer/cave file pair. The program
    will ask whether to restore a state or start a new game.
    If the user chooses to start a new game, the default cave
    file and a default adventurer state defined here will be
    used. Up to 10 save states may be created.
    
    Starting the game in testing mode will enable extra game
    commands.
    
    Tom Harada
*/

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
using namespace std;

class Adventurer;
class Feature;
class ItemFactory;
class GameCommand;
class GameCommandProcessor;
class Map;

class Game {
    public:
        Game( bool test, string filename = myDefaultCaveFile );
            // constructor with testing mode flag
            
        ~Game();
            // deallocate everything
            
        void run();
            // run the game
            
/*        void load( const string& description );
            // sets up the adventurer and the map using the 
            // adventurer and cave files corresponding to the
            // description
            
        void save( const string& description ) const;
            // saves the adventurer and the map using the 
            // adventurer and cave files corresponding to the
            // description
*/            
        Map * getMap();
            // return a pointer to the map
            
        Adventurer * getAdventurer();
            // return a pointer to the adventurer
            
    private:            
        Game( const Game& );
        Game& operator =( const Game& );
            // copy and assignment not implemented
            
        void addCommands( bool testing );
            // put in all the needed game commands; adds
            // testing commands only if instructed
            
        void addItems();
            // fill the item factory with all necessary
            // prototypes
            
        static char myDefaultCaveFile[];
        static int myDefaultAdventurerHealth;
        static int myDefaultAdventurerMoves;
        static int myDefaultAdventurerNumberItems;
        static int myDefaultAdventurerWeightItems;
        
        string myQuitCommand;
        
        GameCommandProcessor * myCommandProcessor;
        ItemFactory * myItemFactory;
        Adventurer * myAdventurer;
        Map * myMap;
};

#endif
