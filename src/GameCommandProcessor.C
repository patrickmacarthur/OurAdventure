/*
    Processes all commands that can be issued to the game by
    the user. Commands are keyed to a string.

    Tom Harada
*/

#include "GameCommandProcessor.h"

#include "GameCommand.h"

// ---------------------------------------------------------
// default constructor; new command processor
// has no commands associated with it
GameCommandProcessor::GameCommandProcessor()
{
    myBadCommand = 0;
}

// ---------------------------------------------------------
// destructor deallocates all command objects
// added to the command processor
GameCommandProcessor::~GameCommandProcessor()
{
    map<string, GameCommand*>::iterator iter = myCommands.begin();

    while ( iter != myCommands.end() )
    {
        delete iter->second;
        iter++;
    }

    delete myBadCommand;
}

// ---------------------------------------------------------
// associates the given command with the string;
// replaces any command already keyed to the string
void GameCommandProcessor::addCommand( const string& name, GameCommand * cmd )
{
    if ( myCommands.count( name ) )
        myCommands.erase( name );

    myCommands[ name ] = cmd;
}

// ---------------------------------------------------------
// registers a command to be executed for any
// unrecognized string; optional as the default
// behavior is to simply print an error message
void GameCommandProcessor::addBadCommand( GameCommand * cmd )
{
    if ( myBadCommand )
        delete myBadCommand;

    myBadCommand = cmd;
}

// ---------------------------------------------------------
// triggers the named command
bool GameCommandProcessor::execute( const string& v )
{
    if ( !myCommands.count( v ) )
    {
        if ( !myBadCommand )
        {
            cout << "bad command\n";
            return true;
        }
        else
            return myBadCommand->execute();
    }
    else
        return myCommands[ v ]->execute();
}
