#pragma once
#include <cstdint>
#include <string>
#include "Ingredients.h"

struct Recipe {
	Recipe() {
	}

	Recipe(std::string name, Ingredients ingredients):
		name(name), ingredients(ingredients) {
	};

	std::string name = "";
	Ingredients ingredients;
};