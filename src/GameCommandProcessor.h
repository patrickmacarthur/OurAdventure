#ifndef GAMECOMMANDPROCESSOR_H
#define GAMECOMMANDPROCESSOR_H

/*
    Processes all commands that can be issued to the game by
    the user. Commands are keyed to a string.

    Tom Harada
*/

#include <string>
#include <map>
using namespace std;

class GameCommand;

class GameCommandProcessor {
    public:
        GameCommandProcessor();
            // default constructor; new command processor
            // has no commands associated with it

        ~GameCommandProcessor();
            // destructor deallocates all command objects
            // added to the command processor

        void addCommand( const string& name, GameCommand * cmd );
            // associates the given command with the string;
            // replaces any command already keyed to the string

        void addBadCommand( GameCommand * cmd );
            // registers a command to be executed for any
            // unrecognized string; optional as the default
            // behavior is to simply print an error message

        bool execute( const string& v );
            // triggers the named command

    private:
        GameCommandProcessor( const GameCommandProcessor& );
        GameCommandProcessor& operator =( const GameCommandProcessor& );
            // copy and assignment not implemented

        map<string, GameCommand*> myCommands;
        GameCommand * myBadCommand;
};

#endif
