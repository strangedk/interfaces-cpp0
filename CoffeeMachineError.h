#pragma once
#include <stdexcept>

class CoffeeMachineError: public std::runtime_error {
public:
	CoffeeMachineError(const char* message, bool isCritical = false)
		: runtime_error(message), m_isCritical(isCritical) { }

	bool IsCritical() {
		return m_isCritical;
	}
private:
	bool m_isCritical;
};