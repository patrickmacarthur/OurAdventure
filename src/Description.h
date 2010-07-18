#ifndef DESCRIPTION_H
#define DESCRIPTION_H

/* Paul Rioux  4/9/10
 *
 * this class defines an item description.  It may be input
 * and output.
 */

#include <iostream>
#include <string>
using namespace std;

class Description {

    public:

        void input(istream &s);
            // inputs an item description

        void output(ostream &s) const;
            // outputs an item description

        void save(ostream &s) const;
            // outputs the description in the same
            // format as the input

    private:

        string value;

};

istream & operator >> (istream & s, Description & v);
    // inputs using input operation above

ostream & operator << (ostream & s, const Description & v);
    // outputs using output operation above

#endif
