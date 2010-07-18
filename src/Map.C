/* Map.C
 *
 * Author: Patrick MacArthur
 *
 * This file is part of the CS 516 Final Project
 */

#include "Map.h"

#include <cstdlib>

#include "Adjacency.h"
#include "Carryable.h"
#include "Container.h"
#include "DirectionList.h"
#include "Feature.h"
#include "ItemFactory.h"
#include "StartRoom.h"

/*
 * The Map class contains the map of the cave that the user is
 * currently in.
 *
 * The map is read in from (and saved to) data files in the
 * following format:
 *  # Comment; ignored
 *  directions num string string ...
 *  consumable id shortName |long descr| healthValue weight size
 *  key id shortName |long descr|
 *  treasure id shortName |long descr| points weight size
 *  pack id shortName |long descr| weight capacity
 *  container box id shortName |long descr| state itemList
 *  container chestid shortName |long descr| state itemList keyId
 *  feature room id shortName |long descr| itemList
 *  feature passage id shortName |long descr| itemList
 *  feature lockableDoorway id shortName |long descr| state keyId
 *  feature doorway id shortName |long descr| state
 *  adj id numAdj dir id dir id ...
 *  start id
 * Items MUST be specified before features.  Directions and
 * features MUST be specified before adjacencies.  itemList is
 * specified as follows:
 *  numItems id ...
 * state may be one of the following: locked (for chests and
 * lockable doors only), closed, or open.
 *
 * Any map that does not conform to the above specifications will
 * be rejected, and the program will terminate with a suitable
 * error message.
 */

//-------------------------------------------------------------
/*
 * Constructs a map.  Expects an ItemFactory that has already
 * been laoded with all appropriate items.  The map will take
 * ownership of the ItemFactory.
 */
Map::Map( ItemFactory * factory )
{
    m_dirList = 0;
    m_startRoom = 0;
    m_itemFactory = factory;
}

//-------------------------------------------------------------
/*
 * destructor
 */
Map::~Map()
{
    clear();
}

//--------------------------------------------------------------
/*
 * Removes all items from the map.
 */
void Map::clear()
{
    delete m_dirList;
    m_dirList = 0;
    delete m_startRoom;
    m_startRoom = 0;

    std::map<ID, Feature *>::iterator iter1;
    for ( iter1 = m_features.begin(); iter1 != m_features.end();
            ++iter1 )
    {
        delete iter1->second;
    }
    m_features.clear();

    std::map<ID, Carryable *>::iterator iter2;
    for ( iter2 = m_carryables.begin(); iter2 != m_carryables.end();
            ++iter2 )
    {
        delete iter2->second;
    }
    m_carryables.clear();

    std::map<ID, Container *>::iterator iter3;
    for ( iter3 = m_containers.begin(); iter3 != m_containers.end();
            ++iter3 )
    {
        delete iter3->second;
    }
    m_containers.clear();
}

//-------------------------------------------------------------
/*
 * Gets the list of directions associated with this cave.
 */
const DirectionList & Map::getDirections() const
{
    return *m_dirList;
}

//-------------------------------------------------------------
/*
 * Gets the feature with the given id.  Returns 0 if
 * there is no feature with that id.
 */
Feature * Map::getFeature( const ID & id )
{
    std::map<ID, Feature *>::iterator iter;
    iter = m_features.find( id );

    if ( iter == m_features.end() )
    {
        return 0;
    }
    else
    {
        return iter->second;
    }
}

//-------------------------------------------------------------
/*
 * Gets the carryable item with the given id.  Returns 0 if there
 * is no item with that id, or it is not carryable.
 */
Carryable * Map::getCarryableItem( const ID & id )
{
    std::map<ID, Carryable *>::iterator iter;
    iter = m_carryables.find( id );

    if ( iter == m_carryables.end() )
    {
        return 0;
    }
    else
    {
        return iter->second;
    }
}

//-------------------------------------------------------------
/*
 * Gets the container with the given id.  Returns 0 if there
 * is no item with that id, or it is not a container.
 */
Container * Map::getContainer( const ID & id )
{
    std::map<ID, Container *>::iterator iter;
    iter = m_containers.find( id );

    if ( iter == m_containers.end() )
    {
        return 0;
    }
    else
    {
        return iter->second;
    }
}

//-------------------------------------------------------------
/*
 * Gets the id of the item with the given name in the
 * given room.  Returns 0 if there is no item with that
 * id.
 */
const ID * Map::getItemId( const Feature & feature, const Name & name ) const
{
    std::map<ID, Carryable *>::const_iterator iter;
    for ( iter = m_carryables.begin();
            iter != m_carryables.end(); ++iter )
    {
        if ( iter->second->getName() == name )
        {
            if ( feature.hasItem( iter->second ) )
            {
                return &iter->first;
            }
        }
    }

    std::map<ID, Container *>::const_iterator iter2;
    for ( iter2 = m_containers.begin();
            iter2 != m_containers.end(); ++iter2 )
    {
        if ( iter2->second->getName() == name )
        {
            if ( feature.hasItem( iter2->second ) )
            {
                return &iter2->first;
            }
        }
    }

    return 0;
}

//-------------------------------------------------------------
/*
 * Returns list of all items, ordered by name.
 */
std::map<Name, const Item *> Map::getItemLocations()
{
    // FIXME: This method is very inefficient, and returns by
    // value, which requires that the entire map be copied.  But
    // it's really the best way we have of doing this right now.
    // Maybe when C++0x is standardized this function can return
    // by move reference and this won't be an issue.
    std::map<Name, const Item *> map;

    {
        // Add all carryable items to the map
        std::map<ID, Carryable *>::iterator mIter;
        for ( mIter = m_carryables.begin();
                mIter != m_carryables.end();
                ++mIter )
        {
            map[ mIter->second->getName() ] = 0;
        }
    }

    {
        // Add all containers to the map
        std::map<ID, Container *>::iterator mIter;
        for ( mIter = m_containers.begin();
                mIter != m_containers.end();
                ++mIter )
        {
            map[ mIter->second->getName() ] = 0;
        }
    }

    {
        // Loop through features; setting the location of all
        // items that are in features
        std::map<ID, Feature *>::iterator mIter;
        for ( mIter = m_features.begin();
                mIter != m_features.end();
                ++mIter )
        {
            list<Item *> list = mIter->second->getItems();
            std::list<Item *>::iterator lIter;
            for ( lIter = list.begin();
                    lIter != list.end(); ++lIter )
            {
                map[ (*lIter)->getName() ] = mIter->second;
            }
        }
    }

    {
        // Add all containers to the map
        std::map<ID, Container *>::iterator mIter;
        for ( mIter = m_containers.begin();
                mIter != m_containers.end();
                ++mIter )
        {
            if ( mIter->second )
            {
                std::map<ID, Carryable *> contents;
                contents = mIter->second->getCarryables();
                std::map<ID, Carryable *>::iterator cIter;
                for ( cIter = contents.begin();
                        cIter != contents.end();
                        ++cIter )
                {
                    map[ cIter->second->getName() ] = map[ mIter->second->getName() ];
                }
            }

            if ( mIter->second )
            {
                std::map<ID, Container *> contents;
                contents = mIter->second->getContainers();
                std::map<ID, Container *>::iterator cIter;
                for ( cIter = contents.begin();
                        cIter != contents.end();
                        ++cIter )
                {
                    map[ cIter->second->getName() ] = map[ mIter->second->getName() ];
                }
            }
        }
    }
    return map;
}

//--------------------------------------------------------------
/*
 * Returns the total score of all items in the cave.
 */
Gold Map::getPoints() const
{
    Gold score;

    std::map<ID, Carryable *>::const_iterator iter;
    for ( iter = m_carryables.begin();
            iter != m_carryables.end(); ++iter )
    {
        score += iter->second->getPoints();
    }

    return score;
}

//--------------------------------------------------------------
/*
 * Returns a pointer to the start feature.
 */
Feature * Map::getStartRoom()
{
    return getFeature( m_startRoom->getLocationID() );
}

//-------------------------------------------------------------
/*
 * Inputs the map from disk, in format above
 */
void Map::input( std::istream & s )
{
    std::string tag;
    Item * item;

    while ( s >> tag )
    {
        if ( tag[0] == '#' )
        {
            // Clear rest of line into dummy variable and ignore
            getline( s, tag );
        }
        else if ( tag != "feature" && tag != "container" )
        {
            item = m_itemFactory->generate( tag );
            item->input( s, this );
            item->addToMap( this );
        }
    }
}

//-------------------------------------------------------------
/*
 * Outputs the map in a human-readable format
 */
void Map::output( std::ostream & s )
{
}

//-------------------------------------------------------------
/*
 * Saves the map to disk in same format input
 */
void Map::save( std::ostream & s )
{
    std::map<ID, Carryable *>::iterator cyIter;
    std::map<ID, Container *>::iterator cnIter;
    std::map<ID, Feature *>::iterator fIter;

    m_dirList->save( s );
    s << '\n';

    for ( cyIter = m_carryables.begin(); cyIter != m_carryables.end();
            ++cyIter )
    {
        cyIter->second->save( s );
        s << '\n';
    }

    for ( cnIter = m_containers.begin(); cnIter != m_containers.end();
            ++cnIter )
    {
        cnIter->second->save( s );
        s << '\n';
    }

    for ( fIter = m_features.begin(); fIter != m_features.end();
            ++fIter )
    {
        fIter->second->save( s );
        s << '\n';
    }

    for ( fIter = m_features.begin(); fIter != m_features.end();
            ++fIter )
    {
        fIter->second->saveExits( s );
        s << '\n';
    }

    m_startRoom->save( s );
    s << '\n';
}

//-------------------------------------------------------------
/*
 * Adds an item to the map.  This function is
 * overloaded to handle all different types of items,
 * and is only menat to be called from
 * Item::addToMap().  This function is given the map to
 * insert into; and fakes multiple-dispatch such that
 * the correct add() method here gets called.
 */
void Map::add( Carryable * item )
{
    m_carryables.insert( std::pair<ID, Carryable *>(
                item->getID(), item ) );
}

void Map::add( Container * item )
{
    m_containers.insert( std::pair<ID, Container *>(
                item->getID(), item ) );
}

void Map::add( DirectionList * item )
{
    m_dirList = item;
}

void Map::add( Feature * item )
{
    ID id = item->getID();
    m_features.insert( std::pair<ID, Feature *>(
                item->getID(), item ) );
}

void Map::add( Adjacency * item )
{
    ID id = item->getFeatureID();

    std::map<ID, Feature *>::iterator iter;
    iter = m_features.find( id );

    if ( iter == m_features.end() )
    {
        std::cerr << "ERROR: Nonexistent feature " << id
                  << " when inputting adjacencies\n";
    }
    else
    {
        iter->second->setExits( item );
    }
}

void Map::add( StartRoom * item )
{
    m_startRoom = item;
}

/* vim: set et sw=4 tw=65: */
