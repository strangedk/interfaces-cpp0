#pragma once
#include <string>

class ICoffeeMachine {
public:
    virtual ~ICoffeeMachine() {};

    virtual void SelectRecipe(std::string name) = 0;
    virtual void Make() = 0;
};