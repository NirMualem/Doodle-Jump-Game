#pragma once

#include "GameObjects/ObjectAbstract.h"

#include <iostream>
#include <typeinfo>

// Sample struct for exception throwing
struct UnknownCollision : public std::runtime_error
{
    UnknownCollision(ObjectAbstract& a, ObjectAbstract& b)
        : std::runtime_error(std::string("Unknown collision of ") + typeid(a).name() + " and " + typeid(b).name())
    {
    }
};

void processCollision(ObjectAbstract& object1, ObjectAbstract& object2);
