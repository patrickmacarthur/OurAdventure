/* Paul Rioux  4/9/10
 *
 * this class defines a lock.  It will hold a key.
 * It will return the key it needs to be unlocked.
 */

#include <iostream>
#include <string>
using namespace std;
#include "Lock.h"
#include "Carryable.h"

//-------------------------------------------------------------
/*
 * creates a lock that needs a certain
 * key value
 */
Lock::Lock()
{
    ID temp;

    temp.setID( "" );
    value = temp;
}

//-------------------------------------------------------------
/*
 * creates a lock that needs a certain
 * key value
 */
Lock::Lock(ID v) : value(v)
{
}

//-------------------------------------------------------------
/*
 * sets the key value needed
 */
void Lock::setKeyID(ID v)
{
    value = v;
}

//-------------------------------------------------------------
/*
 * returns the needed key value
 */
ID Lock::getKeyID() const
{
    return value;
}

