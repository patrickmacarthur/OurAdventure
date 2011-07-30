/*
    Abstract parent class for all game commands. Many commands
    exert the adventure; these should call the adventurer's
    move() method.

    All commands that require arguments use items' short names.
    If the item is a door, its name is simply "door".

    All commands return a boolean success value.

    Tom Harada
*/

#include "GameCommand.h"

#include "Adventurer.h"
#include "Inventory.h"
#include "Map.h"
#include "ID.h"
#include "Feature.h"
#include "Carryable.h"
#include "Container.h"
#include "Direction.h"
#include "DirectionList.h"

/*
    Briefly describes the current feature but not its contents.
*/

// ---------------------------------------------------------
// constructor takes references to adventurer
// and map
LookCommand::LookCommand( Adventurer * adv, Map * map )
{
    myAdventurer = adv;
    myMap = map;
}

// ---------------------------------------------------------
bool LookCommand::execute()
{
    if ( myAdventurer->getStrength() <
        myAdventurer->getInventory()->getWeight() )
        cout << "I am too burdened to look around.\n\n";
    else
    {
        cout << "I am in " << myAdventurer->getCurrentFeature()->getName()
             << ".\n";
        myAdventurer->move();
    }

    return true;
}

/*
    Verbosely describe the current feature, including its
    contents. Short names are used for items.
*/

// ---------------------------------------------------------
// constructor takes references to adventurer
// and map
DetailCommand::DetailCommand( Adventurer * adv, Map * map )
{
    myAdventurer = adv;
    myMap = map;
}

// ---------------------------------------------------------
bool DetailCommand::execute()
{
    if ( myAdventurer->getStrength() <
        myAdventurer->getInventory()->getWeight() )
        cout << "I am too burdened to look around.\n\n";
    else
    {
        myAdventurer->getCurrentFeature()->printDescription( cout );
        myAdventurer->move();
    }

    return true;
}

/*
    Lists the short names of everything the adventurer is
    carrying, including pack contents.
*/

// ---------------------------------------------------------
// constructor takes references to adventurer
// and map
InventoryCommand::InventoryCommand( Adventurer * adv, Map * map )
{
    myAdventurer = adv;
    myMap = map;
}

// ---------------------------------------------------------
bool InventoryCommand::execute()
{
    if ( myAdventurer->getStrength() <
        myAdventurer->getInventory()->getWeight() )
        cout << "I am too burdened to check my inventory.\n\n";
    else
    {
        myAdventurer->getInventory()->list( cout );
        cout << "\n";
        myAdventurer->move();
    }

    return true;
}

/*
    One argument. Gives extended description of item. If item
    is a container, lists the short names of its contents.
    Only open containers may have their contents listed.
*/

// ---------------------------------------------------------
// constructor takes references to adventurer
// and map
ExamineCommand::ExamineCommand( Adventurer * adv, Map * map )
{
    myAdventurer = adv;
    myMap = map;
}

// ---------------------------------------------------------
bool ExamineCommand::execute()
{
    Name name;
    const ID * id;

    cin >> name;
    if ( myAdventurer->getInventory()->hasItem( name ) )
        myAdventurer->getInventory()->getItem( name )->
            printDescription( cout );
    else
    {
        id = myMap->getItemId( *myAdventurer->getCurrentFeature(), name );


        if ( myAdventurer->getCurrentFeature()->getContainer( name ) )
            myAdventurer->getCurrentFeature()->getContainer( name )->printDescription( cout );
        else if ( !id )
            cout << "I see no " << name << " here!\n";
        else if ( myMap->getFeature( *id ) )
            myMap->getFeature( *id )->printDescription( cout );
        else if ( myMap->getCarryableItem( *id ) )
            myMap->getCarryableItem( *id )->printDescription( cout );
        else
            cout << "I see no " << name << " here!\n";
    }

    myAdventurer->move();

    return true;
}

/*
    One argument. Takes an item and puts it into inventory.
    Containers cannot be taken but items from opened containers
    may be taken.
*/

// ---------------------------------------------------------
// constructor takes references to adventurer
// and map
TakeCommand::TakeCommand( Adventurer * adv, Map * map )
{
    myAdventurer = adv;
    myMap = map;
}

// ---------------------------------------------------------
bool TakeCommand::execute()
{
    Name name;
    const ID * id;
    Carryable * item;

    cin >> name;
    id = myMap->getItemId( *myAdventurer->getCurrentFeature(), name );

    if ( !id )
        cout << "I see no " << name << " here!\n";
    else
    {
        item = myMap->getCarryableItem( *id );

        if ( !item )
            cout << "I can't take " << name << "!\n";
        else if ( item->getWeight() + myAdventurer->getInventory()->
            getWeight() > myAdventurer->getStrength() )
            cout << name << " is too heavy!\n";
        else
        {
            if ( myAdventurer->getInventory()->addItem( myAdventurer, item ) )
            {
                myAdventurer->getCurrentFeature()->removeItem( item );
                cout << "Got " << name << ".\n";
            }
            else
                cout << "My inventory is too full!\n";
        }
    }

    myAdventurer->move();
    return true;
}

/*
    One argument. Drops an item from the inventory. Items
    may only be dropped on the floor of a feature, not in a
    doorway or container. Packs may only be dropped if empty.
*/

// ---------------------------------------------------------
// constructor takes references to adventurer
// and map
DropCommand::DropCommand( Adventurer * adv, Map * map )
{
    myAdventurer = adv;
    myMap = map;
}

// ---------------------------------------------------------
bool DropCommand::execute()
{
    Name name;
    Carryable * item;

    cin >> name;
    item = myAdventurer->getInventory()->getItem( name );

    if ( ! item )
        cout << "I can't drop " << name << ".\n";
    else
    {
        if ( myAdventurer->getCurrentFeature()->addItem( item ) )
        {
            if ( myAdventurer->getInventory()->
                removeItem( myAdventurer, name ) )
                cout << "Dropped " << name << ".\n";
            else
                myAdventurer->getCurrentFeature()->removeItem( item );
        }
        else
            cout << "I can't drop " << name << " here!\n";
    }
    myAdventurer->move();

    return true;
}


/*
    Two arguments: item and key. Attempts to unlock a door
    or container with a key. To unlock a door, the adventurer
    must be in the entryway. Only the correct key will
    successfully unlock the item.
*/

// ---------------------------------------------------------
// constructor takes references to adventurer
// and map
UnlockCommand::UnlockCommand( Adventurer * adv, Map * map )
{
    myAdventurer = adv;
    myMap = map;
}

// ---------------------------------------------------------
bool UnlockCommand::execute()
{
    /*
    Name item;
    Name key;

    cin >> item >> key;

    myAdventurer->move();
    return true;
    */
    string str;
    Name key;

    cin >> str >> key;

    if ( myAdventurer->getStrength() <
        myAdventurer->getInventory()->getWeight() )
        cout << "I am too burdened to unlock anything.\n\n";
    else
    {
        Key *item = dynamic_cast<Key *>( myAdventurer->getInventory()->getItem( key ) );

        if ( str == "door" )
        {
            if ( item )
                myAdventurer->getCurrentFeature()->unlockDoor( item );
            else
            {
                /*
                const ID * id = myMap->getItemId( *myAdventurer->getCurrentFeature(), key );

                if ( id )
                {
                    item = dynamic_cast<Key *>( myMap->getCarryableItem( *id ) );
                    myAdventurer->getCurrentFeature()->unlockDoor( item );
                }
                */
                cout << "I don't have " << key << ".\n";
            }
        }
        else
        {
            Name name( str );

            if ( item )
            {
                if ( myAdventurer->getCurrentFeature()->getContainer( name ) )
                    myAdventurer->getCurrentFeature()->getContainer( name )->unlock( item );
                else
                    cout << "I can't unlock " << name << "!\n";
            }
            else
            {
                const ID * id = myMap->getItemId( *myAdventurer->getCurrentFeature(), key );

                if ( id )
                {
                    item = dynamic_cast<Key *>( myMap->getCarryableItem( *id ) );

                    if ( myAdventurer->getCurrentFeature()->getContainer( name ) )
                        myAdventurer->getCurrentFeature()->getContainer( name )->unlock( item );
                    else
                        cout << "I can't unlock " << name << "!\n";
                }
                else
                    cout << "I see no " << key << " here!\n";
            }
        }

        myAdventurer->move();
    }

    return true;
}

/*
    One argument. Opens a door or container. Locked items
    will not open. Open items will also not open.
*/

// ---------------------------------------------------------
// constructor takes references to adventurer
// and map
OpenCommand::OpenCommand( Adventurer * adv, Map * map )
{
    myAdventurer = adv;
    myMap = map;
}

// ---------------------------------------------------------
bool OpenCommand::execute()
{
    string str;
    cin >> str;


    if ( myAdventurer->getStrength() <
        myAdventurer->getInventory()->getWeight() )
        cout << "I am too burdened to open anything.\n\n";
    else
    {
        if ( str == "door" )
            myAdventurer->getCurrentFeature()->openDoor();
        else
        {
            Name name( str );

            if ( myAdventurer->getCurrentFeature()->getContainer( name ) )
                myAdventurer->getCurrentFeature()->getContainer( name )->open();
            else
                cout << "I can't open " << name << "!\n";
        }

        myAdventurer->move();
    }

    return true;
}

/*
    One argument. Eats or drinks an item. This will have an
    effect on the adventurer.
*/

// ---------------------------------------------------------
// constructor takes references to adventurer
// and map
ConsumeCommand::ConsumeCommand( Adventurer * adv, Map * map )
{
    myAdventurer = adv;
    myMap = map;
}

// ---------------------------------------------------------
bool ConsumeCommand::execute()
{
    Name name;
    Carryable * item;

    cin >> name;
    item = myAdventurer->getInventory()->getItem( name );
    if ( item )
    {
        if ( item->isEdible() )
        {
            int oldHealth = myAdventurer->getHealth();
            int oldMoves = myAdventurer->getMovesLeft();

            myAdventurer->getInventory()->removeItem( myAdventurer, name );
            myAdventurer->setHealth( myAdventurer->getHealth() +
                item->getHealth() );
            cout << name << " consumed.\n";

            int healthChange = myAdventurer->getHealth() - oldHealth;
            int movesChange = myAdventurer->getMovesLeft() - oldMoves;
            if ( healthChange < 0 )
                cout << "That was not beneficial!\n\n";
            else if ( healthChange > 0 || movesChange > 0 )
                cout << "That was delicious.\n\n";
            else
                cout << "\n";
        }
        else
            cout << name << " looks rather indigestible to me!\n\n";
    }
    else
    {
        Feature * feature = myAdventurer-> getCurrentFeature();
        const ID * id = myMap->getItemId( *feature, name );

        if ( id )
        {
            item = myMap->getCarryableItem( *id );

            if ( item )
            {
                if ( item->isEdible() )
                {
                    int oldHealth = myAdventurer->getHealth();
                    int oldMoves = myAdventurer->getMovesLeft();

                    myAdventurer->getCurrentFeature()->removeItem( item );
                    myAdventurer->setHealth( myAdventurer->getHealth() +
                        item->getHealth() );
                    cout << name << " consumed.\n";

                    int healthChange = myAdventurer->getHealth() - oldHealth;
                    int movesChange = myAdventurer->getMovesLeft() - oldMoves;
                    if ( healthChange < 0 )
                        cout << "That was not beneficial!\n\n";
                    else if ( healthChange > 0 || movesChange > 0 )
                        cout << "That was delicious.\n\n";
                    else
                        cout << "\n";
                }
                else
                    cout << name << " looks rather indigestible to me!\n\n";
            }
            else
            {
                if ( myMap->getContainer( *myMap->getItemId( *myAdventurer->
                    getCurrentFeature(), name ) ) )
                        cout << name << " looks rather indigestible to me!\n\n";
                else if ( myMap->getFeature( *myMap->getItemId( *myAdventurer->
                    getCurrentFeature(), name ) ) )
                        cout << name << " looks rather indigestible to me!\n\n";
                else
                    cout << "I see no " << name << " here.\n\n";
            }
        }
        else
            cout << "I see no " << name << " here.\n\n";
    }

    return true;
}

/*
    One argument. Moves the adventurer one feature in the
    specified direction. May or may not be successful.
*/

// ---------------------------------------------------------
// constructor takes references to adventurer
// and map
GoCommand::GoCommand( Adventurer * adv, Map * map )
{
    myAdventurer = adv;
    myMap = map;
}

// ---------------------------------------------------------
bool GoCommand::execute()
{
    Direction dir;
    Feature * next;

    cin >> dir;


    if ( myAdventurer->getStrength() <
        myAdventurer->getInventory()->getWeight() )
        cout << "I am too burdened to move.\n\n";
    else
    {
        if ( !myMap->getDirections().isValid( dir ) )
            cout << dir << " is not a direction!\n\n";
        else
        {
            next = myAdventurer->getCurrentFeature()->getExit( dir );

            if ( !next )
                cout << "I can't go that way.\n";
            else
            {
                if ( myAdventurer->getCurrentFeature()->isClosed() &&
                    myAdventurer->getPreviousDirection() == dir )
                    cout << "The door is closed.\n";
                else
                {
                    myAdventurer->setCurrentFeature( next );
                    myAdventurer->setPreviousDirection( dir );
                    cout << "I am now in ";
                    next->printName( cout );
                    cout << ".\n";
                }
            }

            myAdventurer->move();
        }
    }

    return true;
}

/*
    Moves the adventurer from a doorway into the feature
    beyond. A doorway has an entryway followed by a door,
    followed by a feature. The door must be open to allow
    passage and some doors have locks. Thus it takes a
    minimum of two moves to actually traverse a doorway.
*/

// ---------------------------------------------------------
// constructor takes references to adventurer
// and map
InCommand::InCommand( Adventurer * adv, Map * map )
{
    myAdventurer = adv;
    myMap = map;
}

// ---------------------------------------------------------
bool InCommand::execute()
{
    if ( myAdventurer->getStrength() <
        myAdventurer->getInventory()->getWeight() )
        cout << "I am too burdened to move.\n\n";
    else
    {
        Direction dir = myAdventurer->getPreviousDirection();
        Feature * next;

        next = myAdventurer->getCurrentFeature()->getExit( dir );

        if ( !next )
        {
            cout << "I can't go that way.\n";
        }
        else
        {
            if ( myAdventurer->getCurrentFeature()->isClosed() )
            {
                cout << "The door is closed.\n";
            }
            else
            {
                myAdventurer->setCurrentFeature( next );
                myAdventurer->setPreviousDirection( dir );
                cout << "I am now in ";
                next->printName( cout );
                cout << ".\n";
            }
        }

        myAdventurer->move();
    }

    return true;
}

/*
    Save the current game state. The user will be prompted
    for a description and a state number. The current list
    of states and descriptions will be printed. Saving over
    an existing state will destroy its previously saved
    game.
*/

// ---------------------------------------------------------
// constructor takes references to adventurer
// and map
SaveCommand::SaveCommand( Adventurer * adv, Map * map )
{
    myAdventurer = adv;
    myMap = map;
}

// ---------------------------------------------------------
bool SaveCommand::execute()
{
    map<int, string> states;
    ifstream statesListFileIn;
    ofstream statesListFileOut;
    ofstream caveStateFile;
    ofstream advStateFile;
    int state;
    string description;

    const char * caveFile[] = { "cavesave0.dat", "cavesave1.dat",
        "cavesave2.dat", "cavesave3.dat", "cavesave4.dat",
        "cavesave5.dat", "cavesave6.dat", "cavesave7.dat",
        "cavesave8.dat", "cavesave9.dat" };
    const char * advFile[] = { "advsave0.dat", "advsave1.dat",
        "advsave2.dat", "advsave3.dat", "advsave4.dat",
        "advsave5.dat", "advsave6.dat", "advsave7.dat",
        "advsave8.dat", "advsave9.dat" };

    statesListFileIn.open( "save.dat" );

    if ( !statesListFileIn )
    {
        cout << "all slots are empty\n";
        statesListFileIn.close();
    }
    else
    {
        statesListFileIn >> state;
        getline( statesListFileIn, description, '|' );
        getline( statesListFileIn, description, '|' );

        while ( statesListFileIn )
        {
            states[ state ] = description;
            statesListFileIn >> state;
            getline( statesListFileIn, description, '|' );
            getline( statesListFileIn, description, '|' );
        }

        statesListFileIn.close();

        if ( states.empty() )
            cout << "all slots are empty\n";
        else
        {

            cout << "save slots in use:\n";

            for ( int i = 0; i <= 9; i++ )
            {
                if ( states.count( i ) )
                    cout << "  " << i << ": " << states[ i ] << "\n";
            }
        }
    }

    description = "";
    cout << "save in ? ";
    cin >> state;

    while ( ( state < 0 || state > 9 ) && cin )
    {
        cout << "save in ? ";
        cin >> state;
    }

    if ( !cin )
    {
        cin.clear();
        cout << "save aborted\n\n";
        return false;
    }

    cout << "description ? ";
    getline( cin, description );
    getline( cin, description );
    states[ state ] = description;

    statesListFileOut.open( "save.dat" );
    if ( !statesListFileOut )
    {
        cout << "could not write to save list\n";
        statesListFileOut.close();
        return false;
    }

    advStateFile.open( advFile[ state ] );
    if ( !advStateFile )
    {
        cout << "could not write to adventurer file\n";
        advStateFile.close();
        return false;
    }

    caveStateFile.open( caveFile[ state ] );
    if ( !caveStateFile )
    {
        cout << "could not write to adventurer file\n";
        caveStateFile.close();
        return false;
    }

    for ( int i = 0; i <= 9; i++ )
    {
        if ( states.count( i ) )
            statesListFileOut << i << " |" << states[ i ] << "|\n";
    }

    statesListFileOut.close();

    myAdventurer->save( advStateFile );
    advStateFile.close();

    myMap->save( caveStateFile );
    caveStateFile.close();

    cout << "saved to slot " << state << "\n\n";

    return true;
}

/*
    Loads a saved state onto the game. List of save states
    and descriptions is printed and user picks one by
    number. If this operation does not complete satisfactorily,
    the game is terminated.
*/

// ---------------------------------------------------------
// constructor takes references to adventurer and map
RestoreCommand::RestoreCommand( Adventurer * adv, Map * map )
{
    myAdventurer = adv;
    myMap = map;
}

// ---------------------------------------------------------
bool RestoreCommand::execute()
{
    map<int, string> states;
    ifstream statesListFile;
    ifstream advStateFile;
    ifstream caveStateFile;
    int state;
    string description;

    const char * caveFile[] = { "cavesave0.dat", "cavesave1.dat",
        "cavesave2.dat", "cavesave3.dat", "cavesave4.dat",
        "cavesave5.dat", "cavesave6.dat", "cavesave7.dat",
        "cavesave8.dat", "cavesave9.dat" };
    const char * advFile[] = { "advsave0.dat", "advsave1.dat",
        "advsave2.dat", "advsave3.dat", "advsave4.dat",
        "advsave5.dat", "advsave6.dat", "advsave7.dat",
        "advsave8.dat", "advsave9.dat" };

    statesListFile.open( "save.dat" );

    if ( !statesListFile )
    {
        cout << "no saved games available!\n";
        return false;
    }

    statesListFile >> state;
    getline( statesListFile, description, '|' );
    getline( statesListFile, description, '|' );

    while ( statesListFile )
    {
        states[ state ] = description;
        statesListFile >> state;
        getline( statesListFile, description, '|' );
        getline( statesListFile, description, '|' );
    }

    statesListFile.close();

    if ( states.empty() )
    {
        cout << "no saved games available!\n\n";
        return false;
    }

    cout << "save slots in use:\n";

    for ( int i = 0; i <= 9; i++ )
    {
        if ( states.count( i ) )
            cout << "  " << i << ": " << states[ i ] << "\n";
    }

    cout << "restore from ? ";
    cin >> state;

    while ( ( state < 0 || state > 9 ) && cin )
    {
        cout << "restore from ? ";
        cin >> state;
    }

    if ( !cin )
    {
        cin.clear();
        cout << "restore aborted\n\n";
        return false;
    }

    advStateFile.open( advFile[ state ] );

    if ( !advStateFile )
    {
        cout << "missing adventurer save file!\n\n";
        advStateFile.close();
        return false;
    }

    caveStateFile.open( caveFile[ state ] );

    if ( !caveStateFile )
    {
        cout << "missing cave save file!\n\n";
        caveStateFile.close();
        return false;
    }

    myMap->clear();
    myMap->input( caveStateFile );
    caveStateFile.close();

    cout << "Welcome back to the cave.\n";
    cout << myMap->getDirections();

    //myAdventurer->clear();
    myAdventurer->input( advStateFile );
    advStateFile.close();

    return true;
}

/*
    Quits the game. Prints out a score and whatnot.
*/

// constructor takes references to adventurer
// and map
QuitCommand::QuitCommand( Adventurer * adv, Map * map )
{
    myAdventurer = adv;
    myMap = map;
}

bool QuitCommand::execute()
{
    cout << "I scored ";
    cout << myMap->getStartRoom()->getPoints() << " of ";
    cout << myMap->getPoints() << " possible points.\n\n";

    return true;
}


/*
    Prints out an appropriately snarky message when a bad
    command is entered.
*/

// ---------------------------------------------------------
bool BadCommand::execute()
{
    cout << "I don't know how to do that!\n\n";

    string line;
    getline( cin, line );

    return true;
}

/*
    Testing command. Prints a lexically ordered list of all
    items and what feature each is in.
*/

// ---------------------------------------------------------
// constructor takes references to adventurer
// and map
LocationCommand::LocationCommand( Adventurer * adv, Map * map )
{
    myAdventurer = adv;
    myMap = map;
}

// ---------------------------------------------------------
bool LocationCommand::execute()
{
    map<Name, const Item *> itemTable = myMap->getItemLocations();

    map<Name, const Item *>::iterator iter;
    for ( iter = itemTable.begin(); iter != itemTable.end(); ++iter )
    {
        cout << iter->first << '\t';
        if ( iter->second == 0 )
        {
            Inventory * inv = myAdventurer->getInventory();
            if ( inv->hasItem( iter->first ) )
            {
                cout << "(inventory)" << '\n';
            }
            else
            {
                cout << "(unknown)" << '\n';
            }
        }
        else
        {
            cout << iter->second->getID() << '\n';
        }
    }

    cout << endl;
    return true;
}

/*
    Testing command. One argument. Moves adventurer directly
    to the specified feature.
*/

// ---------------------------------------------------------
// constructor takes references to adventurer
// and map
GotoCommand::GotoCommand( Adventurer * adv, Map * map )
{
    myAdventurer = adv;
    myMap = map;
}

// ---------------------------------------------------------
bool GotoCommand::execute()
{
    ID feature;
    cin >> feature;

    Feature * f = myMap->getFeature( feature );

    if ( f )
    {
        myAdventurer->setCurrentFeature( myMap->getFeature( feature ) );
        cout << "moved to " << feature << "\n\n";
    }
    else
        cout << "no such feature!\n\n";

    return true;
}

/*
    Testing command. Prints adventurer's current health
    level and the number of moves remaining at the current
    health state.
*/

// ---------------------------------------------------------
// constructor takes references to adventurer
// and map
HealthCommand::HealthCommand( Adventurer * adv, Map * map )
{
    myAdventurer = adv;
    myMap = map;
}

// ---------------------------------------------------------
bool HealthCommand::execute()
{
    cout << "health: " << myAdventurer->getHealth() << " ";
    switch ( myAdventurer->getHealth() )
    {
        case 5:
            cout << "(high)";
            break;
        case 4:
            cout << "(good)";
            break;
        case 3:
            cout << "(average)";
            break;
        case 2:
            cout << "(poor)";
            break;
        case 1:
            cout << "(dying)";
            break;
        case 0:
            cout << "(dead)";
            break;
        default:
            cout << "(invalid)";
    }
    cout << "\nmoves remaining: " << myAdventurer->getMovesLeft() << "\n\n";

    return true;
}

/*
    Testing command. One argument. Modifies the adventurer's
    health by the given delta.
*/

// ---------------------------------------------------------
// constructor takes references to adventurer
// and map
EatCommand::EatCommand( Adventurer * adv, Map * map )
{
    myAdventurer = adv;
    myMap = map;
}

// ---------------------------------------------------------
bool EatCommand::execute()
{
    int delta;
    cin >> delta;

    myAdventurer->setHealth( myAdventurer->getHealth() + delta );

    cout << "\n";
    return true;
}

/*
    Testing command. One argument. Simulates the given number
    of movements while actually doing nothing.
*/

// ---------------------------------------------------------
// constructor takes references to adventurer
// and map
MoveCommand::MoveCommand( Adventurer * adv, Map * map )
{
    myAdventurer = adv;
    myMap = map;
}

// ---------------------------------------------------------
bool MoveCommand::execute()
{
    int moves;
    cin >> moves;

    for ( int i = 0; i < moves; i++ )
        myAdventurer->move();

    return true;
}

/*
    Testing command. Argument is rest of line. Simply echoes
    whatever follows the command.
*/

// ---------------------------------------------------------
bool EchoCommand::execute()
{
    string echo;
    getline( cin, echo );
    cout << echo << "\n\n";
    return true;
}
