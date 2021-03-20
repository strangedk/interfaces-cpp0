#pragma once

#include<map>

#include "ICoffeeMachine.h"
#include "Recipe.h"
#include "Ingredients.h"

using namespace std;

class CoffeeMachine : public ICoffeeMachine {
public:
    CoffeeMachine(Ingredients ingredients);
    ~CoffeeMachine() { }
public:
    // Inherited via ICoffeeMachine
    virtual void SelectRecipe(string name);
    virtual void Make();
public:    
    const Recipe& NewRecipe();
    CoffeeMachine* AskRecipeByName();
    CoffeeMachine* AddRecipe(const Recipe& recipe);
    const Recipe& GetRecipe(string name);

    void PrintRecipe(const Recipe& recipe) const;
    CoffeeMachine* PrintRecipes();
private:
    bool isCanMake() const;
    void PrintContainer() const;
    void PrintError() const;

private:    
    map <string, Recipe> m_recipesMap;
    Recipe m_selectedRecipe;
    Ingredients m_container;
};
