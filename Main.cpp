#include <iostream>

#include "CoffeeMachine.h"
#include "ICoffeeMachine.h"
#include "CoffeeMachineError.h"

using namespace std;

int main() {
	CoffeeMachine* machine = nullptr;

	try {
		machine = new CoffeeMachine({ 1000, 1000, 1000, 1000 });
		machine
			->AddRecipe(Recipe("Americano", Ingredients(10, 100, 20)))
			->AddRecipe(Recipe("Latte", Ingredients(20, 100, 50, 80)))
			->AddRecipe(machine->NewRecipe());

			while (true) {
				machine
					->PrintRecipes()
					->AskRecipeByName()
					->Make();
			}
	} catch (CoffeeMachineError error) {
		cout << (error.IsCritical() ? "Critical! " : "Not critical. ") << error.what() << endl;
		if (error.IsCritical()) {
			delete machine;
			return 1;
		}
		// ...
	}
	return 0;
}