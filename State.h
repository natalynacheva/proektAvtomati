#ifndef STATE_H
#define STATE_H
#include <string>
#include <iostream>

class State
{
private:
    std::string stateName;

public:
    friend std::ostream& operator << (std::ostream& out, const State& state);
    friend std::istream& operator >> (std::istream& in, State& state);
    friend bool operator==(const State& left, const State& right);

    State() { this->stateName = "EmptyState"; }
    State(std::string stateName) { this->stateName = stateName; }
    std::string getStateName() { return this->stateName; }
    void setStateName(std::string stateName) { this->stateName = stateName; }

};

std::istream& operator >> (std::istream& in, State& state) {
    in >> state.stateName;
    return in;
}

std::ostream& operator << (std::ostream& out, const State& state) {
    std::cout << state.stateName;
    return out;
}

bool operator==(const State& left, const State& right) {
    if (left.stateName == right.stateName)
        return true;
    else
        return false;
}

#endif // STATE_H