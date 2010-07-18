#ifndef LOCK_H
#define LOCK_H

/* Paul Rioux  4/9/10
 *
 * this class defines a lock.  It will hold a key.
 * It will return the key it needs to be unlocked.
 */

#include <iostream>
#include <string>
using namespace std;
#include "Carryable.h"
#include "ID.h"

class Lock {

    public:

        Lock();
            // creates a lock with an empty key value

        Lock(ID);
            // creates a lock that needs a certain
            // key value

        void setKeyID(ID);
            // sets the key value needed

        ID getKeyID() const;
            // returns the needed key value

    private:

        ID value;

};

#endif
