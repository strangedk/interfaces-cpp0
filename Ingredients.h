#pragma once
#include <cstdint>

struct Ingredients {
	Ingredients() {	}
	Ingredients(uint16_t coffee, uint16_t water, uint16_t sugar = 0, uint16_t milk = 0) :
		coffee(coffee), water(water), sugar(sugar), milk(milk) {};

	uint16_t coffee = 0;
	uint16_t water = 0;
	uint16_t sugar = 0;
	uint16_t milk = 0;
	
	bool IsEmpty() {
		return coffee == 0 && water == 0 && sugar == 0 && milk == 0;
	}
};