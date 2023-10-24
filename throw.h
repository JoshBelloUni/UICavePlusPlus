#ifndef THROW_H
#define THROW_H

#include "command.h"
#include "coin.h"
#include "mushroom.h"
#include "rock.h"
#include <iostream>

class Throw : public Command
{
public:
    Throw() : Command("throw") {}
    void fire(Cave& c, string userCommand);
};

#endif // THROW_H


