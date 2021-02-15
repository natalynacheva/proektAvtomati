
#ifndef AUTOMATON_AUTOMATONBASE_H
#define AUTOMATON_AUTOMATONBASE_H

#include "State.h"

template<typename T>
class AutomatonBase {
public:
    virtual int setNumberOfStates() = 0;
    virtual void setStates() = 0;
    virtual int checkStateIndex(State state) = 0;
    virtual int checkAlphabetIndex(T member) = 0;
    virtual State validStateInput() = 0;
    virtual void setStatesCharacteristics() = 0;
    virtual void setAlphabet() = 0;
    virtual void setTransitionTable() = 0;
    virtual State startState() = 0;
    virtual int startStateIndex() = 0;
    virtual int finalStatesNumber() = 0;
    virtual int read(T* word, int lengthWord) = 0;
    virtual void trace(T* word, int lengthWord) = 0;
    virtual State* getStates() = 0;
    virtual int* getStatesCharacteristics() = 0;
    virtual int getNumberOfStates() = 0;
    virtual int getNumberOfAlphabet() = 0;
    virtual T* getElementsOfAlphabet() = 0;
    virtual State** getTransitionTable() = 0;
    virtual void menu() = 0;
    virtual void start() = 0;
    virtual void load() = 0;
    virtual void save() = 0;
    virtual void changeStartState() = 0;
    virtual void addFinalState() = 0;
    virtual void deleteFinalState() = 0;
};

#endif //AUTOMATON_AUTOMATONBASE_H
