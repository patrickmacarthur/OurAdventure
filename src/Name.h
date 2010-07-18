#ifndef NAME_H
#define NAME_H

/* Paul Rioux  4/9/10
 *
 * this class defines an item name.  It may be input
 * and output.
 */

#include <iostream>
#include <string>
using namespace std;

class Name {

    public:

        Name();
            // constructor

        Name(string v);
            // sets to string

        void input(istream &s);
            // inputs a transaction description

        void output(ostream &s) const;
            // outputs a transaction description

        bool operator == (const Name &v) const;
        bool operator != (const Name &v) const;
            // equality operators

        bool operator < (const Name &v) const;
            // relational operators

    private:

        string value;

};

istream & operator >> (istream & s, Name & v);
    // inputs using input operation above

ostream & operator << (ostream & s, const Name & v);
    // outputs using output operation above

#endif
