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

#include "Game.h"

#include "Adventurer.h"
#include "Inventory.h"
#include "Feature.h"
#include "ItemFactory.h"
#include "GameCommand.h"
#include "GameCommandProcessor.h"
#include "Map.h"

#include "Item.h"
#include "DirectionList.h"
#include "Carryable.h"
#include "Adjacency.h"
#include "StartRoom.h"
#include "Container.h"

char Game::myDefaultCaveFile[] = "cave.dat";
int Game::myDefaultAdventurerHealth = 5;
int Game::myDefaultAdventurerMoves = 20;
int Game::myDefaultAdventurerNumberItems = 0;
int Game::myDefaultAdventurerWeightItems = 0;

// ---------------------------------------------------------
// deallocate everything
Game::~Game()
{
    delete myCommandProcessor;
    delete myAdventurer;
    delete myItemFactory;
    delete myMap;
}

// ---------------------------------------------------------
// constructor with testing mode flag
Game::Game( bool test )
{
    string restore = "";
    
    do
    {
        cout << "(n)ew game or (r)estore? ";
        cin >> restore;
    }
    while ( !( restore == "n" || restore == "r" ) && cin );
    
    if ( !cin )
    {
        cout << "\n";
        exit( 0 );
    }
    
    
    myItemFactory = new ItemFactory();
    addItems();
    
    myMap = new Map( myItemFactory );
    
    myAdventurer = new Adventurer( myMap );
    
    myCommandProcessor = new GameCommandProcessor();
    addCommands( test );
    
    ifstream caveFile;
    
    if ( restore == "n" )
    {
        caveFile.open( myDefaultCaveFile );
        
        if ( !caveFile )
        {
            cerr << "could not find cave.dat!\n";
            caveFile.close();
            delete myAdventurer;
            delete myItemFactory;
            delete myMap;
            delete myCommandProcessor;
            exit( 0 );
        }
        
        myMap->input( caveFile );
        caveFile.close();
        if ( ! myMap->getStartRoom() )
        {
            cerr << "Error: No start room defined.\n";
            delete myAdventurer;
            delete myItemFactory;
            delete myMap;
            delete myCommandProcessor;
            exit( 0 );
        }
        
        myAdventurer->setHealth( myDefaultAdventurerHealth );
        myAdventurer->setMovesLeft( 0 );
        myAdventurer->setInventory( new HandStrategy() );
        myAdventurer->setCurrentFeature( myMap->getStartRoom() );
        
        cout << "Welcome to the cave.\n" << myMap->getDirections();
        cout << "I am in ";
        myAdventurer->getCurrentFeature()->printName( cout );
        cout << ".\n\n";
    }
    else if ( restore == "r" )
    {
        if ( !myCommandProcessor->execute( "restore" ) )
        {
            delete myAdventurer;
            delete myItemFactory;
            delete myMap;
            delete myCommandProcessor;
            exit( 0 );
        }
    }
}

// ---------------------------------------------------------
// run the game
void Game::run()
{
    bool done = false;
    string cmd;
    cout << "? ";
    cin >> cmd;

    while ( cin && !done )
    {
        myCommandProcessor->execute( cmd );

        if ( cmd != myQuitCommand && myAdventurer->isAlive() &&
                myMap->getStartRoom()->getPoints() != myMap->getPoints() )
        {
            cout << "? ";
            cin >> cmd;
        }
        else
            done = true;
    }

    if ( ! myAdventurer->isAlive() )
    {
        cout << "I am dead.\n\n"
             << "You scored "
             << myMap->getStartRoom()->getPoints() << " of "
             << myMap->getPoints() << " possible points.\n\n";
    }
    else if ( myMap->getStartRoom()->getPoints() == myMap->getPoints() )
    {
        cout << "You have won.\n\n"
             << "You scored "
             << myMap->getStartRoom()->getPoints() << " of "
             << myMap->getPoints() << " possible points.\n\n";
    }
}

// put in all the needed game commands; adds
// testing commands only if instructed
void Game::addCommands( bool testing )
{    
    myCommandProcessor->addCommand( "look",
        new LookCommand( myAdventurer, myMap ) );
    myCommandProcessor->addCommand( "detail",
        new DetailCommand( myAdventurer, myMap ) );
    myCommandProcessor->addCommand( "inventory",
        new InventoryCommand( myAdventurer, myMap ) );
    myCommandProcessor->addCommand( "examine",
        new ExamineCommand( myAdventurer, myMap ) );
    myCommandProcessor->addCommand( "take",
        new TakeCommand( myAdventurer, myMap ) );
    myCommandProcessor->addCommand( "get",
        new TakeCommand( myAdventurer, myMap ) );
    myCommandProcessor->addCommand( "drop",
        new DropCommand( myAdventurer, myMap ) );
    myCommandProcessor->addCommand( "unlock",
        new UnlockCommand( myAdventurer, myMap ) );
    myCommandProcessor->addCommand( "open",
        new OpenCommand( myAdventurer, myMap ) );
    myCommandProcessor->addCommand( "drink",
        new ConsumeCommand( myAdventurer, myMap ) );
    myCommandProcessor->addCommand( "go",
        new GoCommand( myAdventurer, myMap ) );
    myCommandProcessor->addCommand( "in",
        new InCommand( myAdventurer, myMap ) );
    myCommandProcessor->addCommand( "out",
        new InCommand( myAdventurer, myMap ) );
    myCommandProcessor->addCommand( "save",
        new SaveCommand( myAdventurer, myMap ) );
    myCommandProcessor->addCommand( "restore",
        new RestoreCommand( myAdventurer, myMap ) );
    myQuitCommand = "quit";
    myCommandProcessor->addCommand( myQuitCommand,
        new QuitCommand( myAdventurer, myMap ) );
    myCommandProcessor->addBadCommand( new BadCommand );

    if ( testing )
    {
        myCommandProcessor->addCommand( "location",
            new LocationCommand( myAdventurer, myMap ) );
        myCommandProcessor->addCommand( "goto",
            new GotoCommand( myAdventurer, myMap ) );
        myCommandProcessor->addCommand( "health",
            new HealthCommand( myAdventurer, myMap ) );
        myCommandProcessor->addCommand( "eat",
            new EatCommand( myAdventurer, myMap ) );
        myCommandProcessor->addCommand( "move",
            new MoveCommand( myAdventurer, myMap ) );
        myCommandProcessor->addCommand( "echo", new EchoCommand );
    }
    else
    {
        myCommandProcessor->addCommand( "eat",
            new ConsumeCommand( myAdventurer, myMap ) );
    }
}

// fill the item factory with all necessary
// prototypes
void Game::addItems()
{
    myItemFactory->addItem( "directions", new DirectionList() );
    myItemFactory->addItem( "consumable", new Consumable() );
    myItemFactory->addItem( "key", new Key() );
    myItemFactory->addItem( "treasure", new Treasure() );
    myItemFactory->addItem( "pack", new Pack() );
    myItemFactory->addItem( "chest", new Chest() );
    myItemFactory->addItem( "box", new Box() );
    myItemFactory->addItem( "adj", new Adjacency() );
    myItemFactory->addItem( "start", new StartRoom() );
    myItemFactory->addItem( "room", new Room() );
    myItemFactory->addItem( "passage", new Passage() );
    myItemFactory->addItem( "doorway", new Door() );
    myItemFactory->addItem( "lockableDoorway", new LockableDoor() );
}

/*// ---------------------------------------------------------
// sets up the adventurer and the map using the 
// adventurer and cave files corresponding to the
// description
void Game::load( const string& description )
{
}

// ---------------------------------------------------------
// saves the adventurer and the map using the 
// adventurer and cave files corresponding to the
// description
void Game::save( const string& description ) const
{
}*/

// ---------------------------------------------------------
// return a pointer to the map
Map * Game::getMap()
{
    return myMap;
}

// ---------------------------------------------------------
// return a pointer to the adventurer
Adventurer * Game::getAdventurer()
{
    return myAdventurer;
}
