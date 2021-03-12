#include <iostream>

using namespace std;

class ICofeeMachine {
public:
    virtual ~ICofeeMachine() {};
    virtual bool MakeAmericano() = 0;
    virtual bool MakeLatte() = 0;
};

class ICoffeeMachineRecipe {
protected:
    virtual ~ICoffeeMachineRecipe() {};
    virtual void SetAmericanoRecipe() = 0;
    virtual void SetLatteRecipe() = 0;
};

class CoffeeMachine : public ICofeeMachine, public ICoffeeMachineRecipe {
public:
    static const char DEFAULT_LOAD = 10;

    CoffeeMachine(char water = DEFAULT_LOAD, char sugar = DEFAULT_LOAD, char milk = DEFAULT_LOAD) :
        m_totalWater(water),
        m_totalSugar(sugar),
        m_totalMilk(milk),

        m_shotWater(1),
        m_shotSugar(1),
        m_shotMilk(0) {
    }

    // Inherited via ICofeeMachine
    virtual bool MakeAmericano() override {
        cout << "Americano selected\n";
        SetAmericanoRecipe();        
        return Make();

    }
    virtual bool MakeLatte() override {
        cout << "Latte selected\n";
        SetLatteRecipe();
        return Make();
    }

protected:
    // Inherited via ICoffeeMachineRecipe
    virtual void SetAmericanoRecipe() override {
        m_shotWater = 2;
        m_shotSugar = 1;
        m_shotMilk = 0;
    }
    virtual void SetLatteRecipe() override{
        m_shotWater = 1;
        m_shotSugar = 2;
        m_shotMilk = 1;
    }

private:
    bool isCanMake() {
        return
            m_totalWater >= m_shotWater &&
            m_totalSugar >= m_shotSugar &&
            m_totalMilk >= m_shotMilk;
    }

    bool Make() {
        if (isCanMake()) {
            m_totalWater -= m_shotWater;
            m_totalSugar -= m_shotSugar;
            m_totalMilk -= m_shotMilk;

            PrintRecipy();
            PrintCapacity();

            return true;
        }

        return false;
    }

    void PrintRecipy() {
        cout << "One cup\t: [\twater:" << m_shotWater << ", \tsugar:" << m_shotSugar << ", \tmilk:" << m_shotMilk << endl;        
    }

    void PrintCapacity() {
        cout << "Capacity\t: [\twater:" << m_totalWater << ", \tsugar:" << m_totalSugar << ", \tmilk:" << m_totalMilk << endl;
    }

    void PrintError() {
        cout << "Not enough amount to make:\n";
        PrintRecipy();
        PrintCapacity();
    }

private:
    char m_totalWater;
    char m_totalSugar;
    char m_totalMilk;

    char m_shotWater;
    char m_shotSugar;
    char m_shotMilk;
};

int main() {
    CoffeeMachine machine;

    machine.MakeAmericano();
    machine.MakeLatte();
}