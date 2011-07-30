#ifndef GAMECOMMAND_H
#define GAMECOMMAND_H

/*
    Abstract parent class for all game commands. Many commands
    exert the adventure; these should call the adventurer's
    move() method.

    All commands that require arguments use items' short names.
    If the item is a door, its name is simply "door".

    All commands return a boolean success value.

    Tom Harada
*/

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <stdlib.h>
using namespace std;

class Adventurer;
class Map;
class ID;

class GameCommand {
    public:
        virtual bool execute() = 0;
            // Your thing. Do it.

        static map<int, string> getSaveStates();
            // return a map of save state number-description
            // pairs, taken from the save state file
};

/*
    Briefly describes the current feature but not its contents.
*/

class LookCommand: public GameCommand {
    public:
        LookCommand( Adventurer * adv, Map * map );
            // constructor takes references to adventurer
            // and map

        virtual bool execute();

    private:
        Adventurer * myAdventurer;
        Map * myMap;
};

/*
    Verbosely describe the current feature, including its
    contents. Short names are used for items.
*/

class DetailCommand: public GameCommand {
    public:
        DetailCommand( Adventurer * adv, Map * map );
            // constructor takes references to adventurer
            // and map

        virtual bool execute();

    private:
        Adventurer * myAdventurer;
        Map * myMap;
};

/*
    Lists the short names of everything the adventurer is
    carrying, including pack contents.
*/

class InventoryCommand: public GameCommand {
    public:
        InventoryCommand( Adventurer * adv, Map * map );
            // constructor takes references to adventurer
            // and map

        virtual bool execute();

    private:
        Adventurer * myAdventurer;
        Map * myMap;
};

/*
    One argument. Gives extended description of item. If item
    is a container, lists the short names of its contents.
    Only open containers may have their contents listed.
*/

class ExamineCommand: public GameCommand {
    public:
        ExamineCommand( Adventurer * adv, Map * map );
            // constructor takes references to adventurer
            // and map

        virtual bool execute();

    private:
        Adventurer * myAdventurer;
        Map * myMap;
};

/*
    One argument. Takes an item and puts it into inventory.
    Containers cannot be taken but items from opened containers
    may be taken.
*/

class TakeCommand: public GameCommand {
    public:
        TakeCommand( Adventurer * adv, Map * map );
            // constructor takes references to adventurer
            // and map

        virtual bool execute();

    private:
        Adventurer * myAdventurer;
        Map * myMap;
};

/*
    One argument. Drops an item from the inventory. Items
    may only be dropped on the floor of a feature, not in a
    doorway or container. Packs may only be dropped if empty.
*/

class DropCommand: public GameCommand {
    public:
        DropCommand( Adventurer * adv, Map * map );
            // constructor takes references to adventurer
            // and map

        virtual bool execute();

    private:
        Adventurer * myAdventurer;
        Map * myMap;
};

/*
    Two arguments: item and key. Attempts to unlock a door
    or container with a key. To unlock a door, the adventurer
    must be in the entryway. Only the correct key will
    successfully unlock the item.
*/

class UnlockCommand: public GameCommand {
    public:
        UnlockCommand( Adventurer * adv, Map * map );
            // constructor takes references to adventurer
            // and map

        virtual bool execute();

    private:
        Adventurer * myAdventurer;
        Map * myMap;
};

/*
    One argument. Opens a door or container. Locked items
    will not open. Open items will also not open.
*/

class OpenCommand: public GameCommand {
    public:
        OpenCommand( Adventurer * adv, Map * map );
            // constructor takes references to adventurer
            // and map

        virtual bool execute();

    private:
        Adventurer * myAdventurer;
        Map * myMap;
};

/*
    One argument. Eats or drinks an item. This will have an
    effect on the adventurer.
*/

class ConsumeCommand: public GameCommand {
    public:
        ConsumeCommand( Adventurer * adv, Map * map );
            // constructor takes references to adventurer
            // and map

        virtual bool execute();

    private:
        Adventurer * myAdventurer;
        Map * myMap;
};

/*
    One argument. Moves the adventurer one feature in the
    specified direction. May or may not be successful.
*/

class GoCommand: public GameCommand {
    public:
        GoCommand( Adventurer * adv, Map * map );
            // constructor takes references to adventurer
            // and map

        virtual bool execute();

    private:
        Adventurer * myAdventurer;
        Map * myMap;
};

/*
    Moves the adventurer from a doorway into the feature
    beyond. A doorway has an entryway followed by a door,
    followed by a feature. The door must be open to allow
    passage and some doors have locks. Thus it takes a
    minimum of two moves to actually traverse a doorway.
*/

class InCommand: public GameCommand {
    public:
        InCommand( Adventurer * adv, Map * map );
            // constructor takes references to adventurer
            // and map

        virtual bool execute();

    private:
        Adventurer * myAdventurer;
        Map * myMap;
};

/*
    Save the current game state. The user will be prompted
    for a description and a state number. The current list
    of states and descriptions will be printed. Saving over
    an existing state will destroy its previously saved
    game.
*/

class SaveCommand: public GameCommand {
    public:
        SaveCommand( Adventurer * adv, Map * map );
            // constructor takes references to adventurer
            // and map

        virtual bool execute();

    private:
        Adventurer * myAdventurer;
        Map * myMap;
};

/*
    Loads a saved state onto the game. List of save states
    and descriptions is printed and user picks one by
    number. If this operation does not complete satisfactorily,
    the game is terminated.
*/

class RestoreCommand: public GameCommand {
    public:
        RestoreCommand( Adventurer * adv, Map * map );
            // constructor takes references to adventurer and
            // map

        virtual bool execute();

    private:
        Adventurer * myAdventurer;
        Map * myMap;
};

/*
    Quits the game. Prints out a score and whatnot.
*/

class QuitCommand: public GameCommand {
    public:
        QuitCommand( Adventurer * adv, Map * map );
            // constructor takes references to adventurer
            // and map

        virtual bool execute();

    private:
        Adventurer * myAdventurer;
        Map * myMap;
};

/*
    Testing command. Prints a lexically ordered list of all
    items and what feature each is in.
*/

class LocationCommand: public GameCommand {
    public:
        LocationCommand( Adventurer * adv, Map * map );
            // constructor takes references to adventurer
            // and map

        virtual bool execute();

    private:
        Adventurer * myAdventurer;
        Map * myMap;
};

/*
    Testing command. One argument. Moves adventurer directly
    to the specified feature.
*/

class GotoCommand: public GameCommand {
    public:
        GotoCommand( Adventurer * adv, Map * map );
            // constructor takes references to adventurer
            // and map

        virtual bool execute();

    private:
        Adventurer * myAdventurer;
        Map * myMap;
};

/*
    Testing command. Prints adventurer's current health
    level and the number of moves remaining at the current
    health state.
*/

class HealthCommand: public GameCommand {
    public:
        HealthCommand( Adventurer * adv, Map * map );
            // constructor takes references to adventurer
            // and map

        virtual bool execute();

    private:
        Adventurer * myAdventurer;
        Map * myMap;
};

/*
    Testing command. One argument. Modifies the adventurer's
    health by the given delta.
*/

class EatCommand: public GameCommand {
    public:
        EatCommand( Adventurer * adv, Map * map );
            // constructor takes references to adventurer
            // and map

        virtual bool execute();

    private:
        Adventurer * myAdventurer;
        Map * myMap;
};

/*
    Testing command. One argument. Simulates the given number
    of movements while actually doing nothing.
*/

class MoveCommand: public GameCommand {
    public:
        MoveCommand( Adventurer * adv, Map * map );
            // constructor takes references to adventurer
            // and map

        virtual bool execute();

    private:
        Adventurer * myAdventurer;
        Map * myMap;
};

/*
    Testing command. Argument is rest of line. Simply echoes
    whatever follows the command.
*/

class EchoCommand: public GameCommand {
    public:
        virtual bool execute();
};

#endif
