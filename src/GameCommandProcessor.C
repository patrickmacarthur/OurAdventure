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
// triggers the named command
bool GameCommandProcessor::execute( const string& v )
{
    if ( !myCommands.count( v ) )
    {
        std::map<std::string, GameCommand *>::iterator iter;

        cout << "I only understand the following:\n";
        for ( iter = myCommands.begin(); iter != myCommands.end(); ++iter ) {
            cout << iter->first << ": "
                 << iter->second->briefDescription() << "\n";
        }
        cout << "\n";
        return false;
    } else {
        return myCommands[ v ]->execute();
    }
}
