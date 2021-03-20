#include<iostream>
#include "CoffeeMachine.h"
#include "CoffeeMachineError.h"

CoffeeMachine::CoffeeMachine(Ingredients ingredients) : m_container(ingredients) {
	if (m_container.IsEmpty()) {
		bool isCritical = true;
		throw CoffeeMachineError("Coffee machine container is empty", isCritical);
	}
}

const Recipe& CoffeeMachine::NewRecipe() {
	string recipeName;
	Ingredients ingredients;

	cout << "Enter the custom recipe name: ";
	cin >> recipeName;
	cout << "Enter coffe quantity: ";
	cin >> ingredients.coffee;
	cout << "Enter water quantity: ";
	cin >> ingredients.water;
	cout << "Enter sugar quantity: ";
	cin >> ingredients.sugar;
	cout << "Enter milk quantity: ";
	cin >> ingredients.milk;

	if (recipeName == "" || ingredients.IsEmpty()) {
		bool isCritical = false;
		throw CoffeeMachineError("Wrong recipe. Rejected.", isCritical);
	}

	const Recipe* recipe = new Recipe(recipeName, ingredients);

	return *recipe;
}

CoffeeMachine* CoffeeMachine::AddRecipe(const Recipe& recipe) {
	try {
		pair<string, const Recipe&> mapItem(recipe.name, recipe);
		m_recipesMap.insert(mapItem);
	} catch (CoffeeMachineError error) {
		if (error.IsCritical()) {
			cout << "Recipe Isn't added. Application will be unstable and should to shutdown.\n";
			throw;
		}
		else {
			cout << "Recipe Isn't added.\n";
		}
	}

	return this;
}

const Recipe& CoffeeMachine::GetRecipe(string name) {
	string tmp = string(name);

	try {
		return m_recipesMap.at(tmp.c_str());
	}
	catch (out_of_range error) {
		throw;
	}
}

CoffeeMachine* CoffeeMachine::AskRecipeByName() {
	string recipeName;
	cout << "Select recipe by name: ";
	cin >> recipeName;

	SelectRecipe(recipeName);

	return this;
}

void CoffeeMachine::SelectRecipe(string name) {
	m_selectedRecipe = GetRecipe(name);

	cout << "Recipe selected: " << name << endl;
	PrintRecipe(m_selectedRecipe);
}

void CoffeeMachine::Make() {
	const bool isCan = isCanMake();
	if (isCan) {
		m_container.coffee -= m_selectedRecipe.ingredients.coffee;
		m_container.water -= m_selectedRecipe.ingredients.water;
		m_container.sugar -= m_selectedRecipe.ingredients.sugar;
		m_container.milk -= m_selectedRecipe.ingredients.milk;
		PrintContainer();
	} else {
		bool isCritical = false;
		PrintContainer();
		throw CoffeeMachineError("Machine container haven't enough ingredients", isCritical);
	}
}

bool CoffeeMachine::isCanMake() const {
	return
		m_container.coffee >= m_selectedRecipe.ingredients.coffee &&
		m_container.water >= m_selectedRecipe.ingredients.water &&
		m_container.sugar >= m_selectedRecipe.ingredients.sugar &&
		m_container.milk >= m_selectedRecipe.ingredients.milk;
}

void CoffeeMachine::PrintRecipe(const Recipe& recipe) const {
	try {
		std::cout
			<< "One cup of "
			<< recipe.name
			<< " needs coffee:"
			<< recipe.ingredients.coffee
			<< ", water:"
			<< recipe.ingredients.water
			<< ", sugar:"
			<< recipe.ingredients.sugar
			<< ", milk:"
			<< recipe.ingredients.milk
			<< std::endl;
	} catch (runtime_error error) {
		CoffeeMachineError coffeeError(error.what());
		throw coffeeError;
	}
}

CoffeeMachine* CoffeeMachine::PrintRecipes() {
	for (auto const& it : m_recipesMap) {
		PrintRecipe(it.second);
	}

	return this;
}

void CoffeeMachine::PrintContainer() const {
	std::cout
		<< "Machine container ingredients is coffee:"
		<< m_container.coffee
		<< ", water:"
		<< m_container.water
		<< ", sugar:"
		<< m_container.sugar
		<< ", milk:"
		<< m_container.milk
		<< std::endl;
}

void CoffeeMachine::PrintError() const {
	std::cout << "Not enough amount to make:\n";
	PrintRecipe(m_selectedRecipe);
	PrintContainer();
}