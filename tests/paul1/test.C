/* Paul Rioux  4/23/10
 *
 * this is a test class to test all of the
 * classes
 */

#include <string>
#include <iostream>
using namespace std;
#include "Carryable.h"
#include "Container.h"
#include "Description.h"
#include "Gold.h"
#include "ID.h"
#include "Item.h"
#include "Lock.h"
#include "LockState.h"
#include "Name.h"
#include "Size.h"
#include "Weight.h"
#include "Map.h"

int main()
{
    Gold g1;
    Gold g2;
    Consumable * consum1 = new Consumable;
    Key * k1 = new Key;
    Key * k2 = new Key;
    Treasure * t1 = new Treasure;
    Pack * p1 = new Pack;
    Chest * c1 = new Chest;
    Box * b1 = new Box;
    string temp;
    Map * m = new Map(0);

    cout << "\n\nDirection, DirectionList, Feature, ItemFactory, Map,"
    << " and StartRoom are not being tested as I did not do those."
    << "\n------------------------------------------------------\n";

    cout << "this is going to test that point values"
    << " are entered correctly and output correctly.  The output"
    << " should be \"65 32\":\n";
    cin >> g1 >> g2;
    cout << g1 << ' ' << g2 << "\n\nThis tests if addition works."
    << " The answer should be 97:\n" << g1 + g2
    << "\n\nThis tests if points subtract correctly. The answer "
    << "should be 33:\n" << g1 - g2 << "\n\n"
    << "------------------------------------------------------\nThis"
    << " next series of tests will check if carryable items are "
    << "input correctly. This also tests the outputs of the name, "
    << "id, description, the size, weigth, and points."
    << " Consumable is first. The output should be \"consumable "
    << "food1 apple |rotting apple| -1 2 5\":\n";
    cin >> temp;
    consum1->input(cin, m);
    consum1->save( cout );
    consum1->addToMap( m );
    cout << "\n\nNext is Key.  It should appear as \"key k1 "
    << "goldkey |key with a glint|\":\n";
    cin >> temp;
    k1->input(cin, m);
    k1->save( cout );
    k1->addToMap( m );
    cout << "\n\nNext is Treasure.  It should appear as \"treasure"
    << " t1 diamond |large cut diamond| 500 2 1\":\n";
    cin >> temp;
    t1->input(cin, m);
    t1->save( cout );
    t1->addToMap( m );
    cout << "\n\nNext is Pack.  It should appear as \"pack"
    << " p1 pack |leather bag| 2 10\":\n";
    cin >> temp;
    p1->input(cin, m);
    p1->save( cout );
    p1->addToMap( m );
    cout << "\n\nThis next series of tests will check if containers "
    << "are input correctly. Chest is first.  The output should appear"
    << " as \"container chest c1 trunk |large trunk| locked 2 t1 p1 k1\":\n";
    cin >> temp >> temp;
    c1->input(cin, m);
    c1->save( cout );
    c1->addToMap( m );
    cout << "\n\nBox is next.  The output should appear as \"container box"
    << " c2 crate |splintered crate| open 2 t1 p1\":\n";
    cin >> temp >> temp;
    b1->input(cin, m);
    b1->save( cout );
    b1->addToMap( m );

    cout << "\n\n------------------------------------------------------\n";
    cout << "\nThis next test tries to unlock a box. It should say it's not locked:\n";
    b1->unlock(k1);
    cout << "\n\nThis test tries to unlock a chest with a wrong key. It "
    << "should say wrong key:\n";
    c1->unlock(k2);
    cout << "\n\nThis test tries to unlock a chest with the right key. The "
    << "output should appear as \"container chest c1 trunk |large trunk| "
    << "closed 2 t1 p1 k1\":\n";
    c1->unlock(k1);
    c1->save( cout );
    cout << "\n\nThis test tries to open a closed chest. The "
    << "output should appear as \"container chest c1 trunk |large trunk| "
    << "open 2 t1 p1 k1\":\n";
    c1->open();
    c1->save( cout );

    cout << "\n\n------------------------------------------------------\n"
    << "\nThese next tests test the clone operation.  First up is Comsumable:"
    << "\nThe output should be \"consumable food1 apple |rotting apple| -1 2 5\":\n";
    Item * newTempCon = consum1->clone();
    newTempCon->save( cout );
    cout << "\n\nNext is Key.  It should appear as \"key k1 "
    << "goldkey |key with a glint|\":\n";
    Item * newTempKey = k1->clone();
    newTempKey->save( cout );
    cout << "\n\nNext is Treasure.  It should appear as \"treasure"
    << " t1 diamond |large cut diamond| 500 2 1\":\n";
    Item * newTempTre = t1->clone();
    newTempTre->save( cout );
    cout << "\n\nNext is Pack.  It should appear as \"pack"
    << " p1 pack |leather bag| 2 10\":\n";
    Item * newTempPac = p1->clone();
    newTempPac->save( cout );
    cout << "\n\nChest is first.  The output should appear"
    << " as \"container chest c1 trunk |large trunk| open 2 t1 p1 k1\":\n";
    Item * newTempChe = c1->clone();
    newTempChe->save( cout );
    cout << "\n\nBox is next.  The output should appear as \"container box"
    << " c2 crate |splintered crate| open 2 t1 p1\":\n";
    Item * newTempBox = b1->clone();
    newTempBox->save( cout );
    cout << "\n\n------------------------------------------------------\n";

    delete newTempBox;
    delete newTempChe;
    delete newTempCon;
    delete newTempKey;
    delete newTempPac;
    delete newTempTre;
    delete k2;
    delete m;

    return 0;
}
