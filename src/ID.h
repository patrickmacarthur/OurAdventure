#ifndef ID_H
#define ID_H

/* Paul Rioux  4/9/10
 *
 * this class defines an item id.  It may be input
 * and output.
 */

#include <iostream>
#include <string>
using namespace std;

class ID {

    public:

        ID();
            // constructor

        void input(istream &s);
            // inputs an id

        void output(ostream &s) const;
            // outputs an id

        bool operator == (const ID &v) const;
        bool operator != (const ID &v) const;
            // equality operators

        bool operator < (const ID &v) const;
            // relational operators

        string getID() const;
            // returns id for a customer

        void setID(string);
            // sets the id for a customer

    private:

        string value;

};

istream & operator >> (istream & s, ID & v);
    // inputs using input operation above

ostream & operator << (ostream & s, const ID & v);
    // outputs using output operation above

#endif
