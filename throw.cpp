#include "throw.h"
#include "thing.h"
#include <iostream>
#include <sstream>

void Throw::fire(Cave& c, string userCommand) {
    // Check if the userCommand starts with "throw" as the trigger word
    if (userCommand.find("throw") != 0) {
        std::cerr << "Invalid syntax. Usage: throw [object] [direction]" << std::endl;
        return;
    }

    // Remove "throw" from the userCommand
    userCommand = userCommand.substr(5); // Assuming "throw" is followed by a space

    // Parse the object and direction from the arguments
    std::istringstream iss(userCommand);
    std::string object;
    std::string direction;

    iss >> object;

    // Check if the object is "coin" or "mushroom"
    if (object != "coin" && object != "mushroom") {
        std::cerr << "Invalid object. Tom can't throw " << object << "." << std::endl;
        return;
    }

    iss >> direction;

    // Check if the direction is valid
    if (iss.fail() || (direction != "north" && direction != "south" && direction != "east" && direction != "west")) {
        std::cerr << "Invalid syntax. Usage: throw [coin|mushroom] [north|south|east|west]" << std::endl;
        return;
    }

    // Get Tom's current location
    int tomX = c.getTom()->getX();
    int tomY = c.getTom()->getY();

    // Calculate the new location based on the direction
    if (direction == "north") {
        tomY--;
    } else if (direction == "south") {
        tomY++;
    } else if (direction == "east") {
        tomX++;
    } else if (direction == "west") {
        tomX--;
    }

    // Check if the new location is within the cave's boundaries
    if (tomX >= 0 && tomX < c.getWidth() && tomY >= 0 && tomY < c.getHeight()) {
        Location* loc = c.getMap()[tomX][tomY];

        if (object == "coin") {
            loc->add(new Coin());
        } else if (object == "mushroom") {
            loc->add(new Mushroom());
        }

        std::cout << "Tom threw a " << object << " to the " << direction << "." << std::endl;
    } else {
        std::cerr << "Invalid direction. Tom can't throw the object that way." << std::endl;
    }
}
