#include <stdexcept>
#include <string>
#include <iostream>
#include <vector>

#include "cave.h"
#include "rock.h"
#include "thing.h"
#include "location.h"
#include "move.h"
#include "place.h"
#include "throw.h"

using namespace std;

Cave::Cave(int w, int h) : width(w), height(h) // width and height of the cave
{
    /*
    if (width != 8 || height != 8) // be sure to update Cave::show() if you remove this.
        throw new logic_error("fixme: Cave needs to be fixed for non-standard sizes.");
    */

    if ( width < 5 || height < 5)
        //cerr << "too small" << endl;
        throw new logic_error("cave too small for tom.");

    map = new Location**[width];  // Use 'width' for the number of columns

    for (int x = 0; x < width; x++)
    {
        Location** column = new Location*[height];  // Use 'height' for the number of rows
        map[x] = column;
        for (int y = 0; y < height; y++)
            column[y] = new Location();
    }


    // create some rocks
    for (int x = 0; x < width; x++)
        for (int y = 0; y < height; y++)
            if ( x == 0 || y == 0 || x == (width-1) || y == (height-1) )
                map[x][y] -> add( new Rock() );

    tom = new Tom();
    // add tom to the middle of the map
    tom -> setLocation( this, width/2,height/2);
}


Cave::~Cave()
{
    // delete the allocated memory for Location objects and arrays
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            delete map[x][y];
        }
        delete[] map[x];
    }
    delete[] map;

    // delete the Tom object
    delete tom;
}

void Cave::command (string userCommand)
{
    if (Move().triggersOn(userCommand))
        Move().fire(*this, userCommand);
    else if (Place().triggersOn(userCommand))
        Place().fire(*this, userCommand);
    else if (Throw().triggersOn(userCommand))
        Throw().fire(*this, userCommand);
    else
        cerr << "tom doesn't know how to "+userCommand << endl;;
}

void Cave::show()
{
    vector<Thing*>* thingsWithTom = map[tom -> getX()][tom -> getY()] -> getThings();

    for (int y = 0; y < height; y++)
    { // for all rows
        for (int x = 0; x < width; x++) // for all columns
            cout << map[x][y] -> show(); // output whatever we find there

        cout << "  "; // list the things at this location
        if (y <  (int) thingsWithTom -> size())
            cout << (*thingsWithTom)[y] -> getName();

        cout << endl;
    }

    cout << endl;
}


Cave::Cave(const Cave& other) {

    width = other.width;
    height = other.height;

    map = new Location**[width];
    for (int x = 0; x < width; x++) {
        Location** column = new Location*[height];
        map[x] = column;
        for (int y = 0; y < height; y++) {
            // Deep copy the Location objects
            map[x][y] = new Location(*(other.map[x][y]));
        }
    }

    tom = new Tom(*(other.tom));
}

Cave& Cave::operator=(const Cave& other) {
    if (this == &other) {
        return *this;
    }

    // Clean up the current object
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            delete map[x][y];
        }
        delete[] map[x];
    }
    delete[] map;
    delete tom;

    // copy the new object
    width = other.width;
    height = other.height;

    // allocate memory for the map
    map = new Location**[width];
    for (int x = 0; x < width; x++) {
        Location** column = new Location*[height];
        map[x] = column;
        for (int y = 0; y < height; y++) {
            // Deep copy the Location objects
            map[x][y] = new Location(*(other.map[x][y]));
        }
    }

    // deep copy any other dynamically allocated members like 'tom'
    tom = new Tom(*(other.tom));

    return *this;
}



