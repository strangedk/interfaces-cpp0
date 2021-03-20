#pragma once

class ICoffeeMachineRecipe {
protected:
    virtual ~ICoffeeMachineRecipe() {};
    virtual void SetAmericanoRecipe() = 0;
    virtual void SetLatteRecipe() = 0;
};
