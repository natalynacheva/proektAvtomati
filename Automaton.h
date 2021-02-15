

#ifndef AUTOMATON_AUTOMATON_H
#define AUTOMATON_AUTOMATON_H

#include <iostream>
#include <fstream>
#include <string>
#include "State.h"
#include "Alphabet.h"
#include "AutomatonBase.h"


template<typename T>
class Automaton : public AutomatonBase<T> {
private:
    State* states = nullptr;
    int* statesCharacteristics;
    int numberOfStates;
    Alphabet<T>* alphabet;
    State** transitionTable;
public:
    Automaton<T>() {}

    friend std::ostream& operator<<(std::ostream& out, const State& state);

    int setNumberOfStates() override {
        int states_number = 0;
        while (states_number < 1) {
            std::cout << "Enter how many states: ";
            std::cin >> states_number;
            if (states_number < 1)
                std::cout << "Must be at least 1\n";
        }
        this->numberOfStates = states_number;
        return states_number;
    }

    void setStates() override {
        if (states != nullptr) {
            delete[] states;
            delete[] statesCharacteristics;
        }
        statesCharacteristics = new int[numberOfStates];
        states = new State[numberOfStates];
        int exists = 0;
        for (int i = 0; i < numberOfStates;) {
            exists = 0;
            std::cout << "State[" << i + 1 << "] --> ";
            std::cin >> this->states[i];
            for (int j = 0; j < i; j++) {
                if (states[i] == states[j]) {
                    exists = 1;
                    std::cout << "There is already a state with this name\n";
                }
            }
            if (exists == 0)
                i++;
        }
    }

    int checkStateIndex(State state) override {
        int stateIndex = -1;
        for (int i = 0; i < numberOfStates; i++) {
            if (state == states[i]) {
                stateIndex = i;
                break;
            }
        }
        return stateIndex;
    }

    int checkAlphabetIndex(T member) override {
        int memberIndex = -1;
        for (int i = 0; i < alphabet->getNumberOfMembers(); i++) {
            if (alphabet->getElements()[i] == member) {
                memberIndex = i;
                break;
            }
        }
        return memberIndex;
    }

    State validStateInput() override {
        State state;
        int isValid = -1;
        do {
            std::cin >> state;
            isValid = checkStateIndex(state);
        } while (isValid == -1);

        return state;
    }

    void setStatesCharacteristics() override {
        State state;
        int numberOfFinalStates, stateIndex = -1;
        do {
            std::cout << "Enter start state ==>";
            std::cin >> state;
            stateIndex = checkStateIndex(state);
            if (stateIndex == -1)
                std::cout << "There is no such state\n";
        } while (stateIndex == -1);
        statesCharacteristics[stateIndex] = 1;
        std::cout << "Enter how many final States: ";
        std::cin >> numberOfFinalStates;
        //ïğîâåğêà çà ÷èñëîòî äàëè å >0 è <numberOfStates
        for (int i = 0; i < numberOfFinalStates; i++) {
            do {
                std::cout << "Enter final state [" << i + 1 << "] ==> ";
                std::cin >> state;
                stateIndex = checkStateIndex(state);
                if (stateIndex == -1)
                    std::cout << "There is no such state\n";
            } while (stateIndex == -1);
            statesCharacteristics[stateIndex] += 2;
        }

    }

    void setAlphabet() override {
        int membersOfAlphabet = 0;
        while (membersOfAlphabet <= 0) {
            std::cout << "Enter how much elements do you want ==> ";
            std::cin >> membersOfAlphabet;
        }

        alphabet = new Alphabet<T>(membersOfAlphabet);
        alphabet->setElements();
    }

    void setTransitionTable() override {
        transitionTable = new State * [numberOfStates];

        for (int i = 0; i < numberOfStates; ++i)
            transitionTable[i] = new State[alphabet->getNumberOfMembers()];

        for (int i = 0; i < numberOfStates; i++)
            for (int j = 0; j < alphabet->getNumberOfMembers(); j++) {
                std::cout << "(" << states[i] << "," << alphabet->getElement(j) << ") ==>  ";
                transitionTable[i][j] = validStateInput();
            }
    }

    State startState() override {
        int i = 0;
        while (i < numberOfStates) {
            if ((statesCharacteristics[i] + 1) % 2 == 0)
                break;
            i++;
        }
        return states[i];
    }

    int startStateIndex() override {
        int i = 0;
        while (i < numberOfStates) {
            if ((statesCharacteristics[i] + 1) % 2 == 0)
                break;
            i++;
        }
        return i;
    }

    int finalStatesNumber() override {
        int numberOfFinalStates = 0;
        for (int i = 0; i < numberOfStates; i++)
            if (statesCharacteristics[i] > 1)
                numberOfFinalStates++;

        return numberOfFinalStates;
    }

    /*
    ×ÅÒÅ ÄÓÌÀ,
    ÀÊÎ ÄÓÌÀÒÀ Å ÂÀËÈÄÍÀ È Å ÑÒÈÃÍÀË ÄÎ ÊĞÀÉÍÎ ÑÚÑÒÎßÍÈÅ ÂĞÚÙÀ 1
    ÀÊÎ ÄÓÌÀÒÀ Å ÂÀËÈÄÍÀ È ÍÅ Å ÑÒÈÃÍÀË ÄÎ ÊĞÀÉÍÎ ÑÚÑÒÎßÍÈÅ ÂĞÚÙÀ 0
    ÀÊÎ ÄÓÌÀÒÀ Å ÍÅÂÀËÈÄÍÀ(ÍßÊÎÉ ÎÒ ÑÈÌÂÎËÈÒÅ ÍÅ ÏĞÈÍÀÄËÅÆÈ ÍÀ ÀÇÁÓÊÀÒÀ) ÂĞÚØÀ -1
    */
    int read(T* word, int lengthWord) override {
        State currentState = startState();
        int indexCurrentState = checkStateIndex(currentState);
        int indexAlphabet;

        for (int i = 0; i < lengthWord; i++) {
            indexAlphabet = checkAlphabetIndex(word[i]);

            if (indexAlphabet == -1)
                return -1;
            currentState = transitionTable[indexCurrentState][indexAlphabet];
            indexCurrentState = checkStateIndex(currentState);
        }
        if (statesCharacteristics[indexCurrentState] > 1)
            return 1;
        return 0;
    }

    /*ÏÅ×ÀÒÀ ÏÚÒß, ÈÇ×ÈÒÀÉÊÈ ÄÓÌÀÒÀ*/
    void trace(T* word, int lengthWord) override {
        State currentState = startState();
        int indexCurrentState = checkStateIndex(currentState);
        int indexAlphabet;

        std::cout << currentState;
        for (int i = 0; i < lengthWord; i++) {
            indexAlphabet = checkAlphabetIndex(word[i]);

            if (indexAlphabet == -1) {
                std::cout << "Not recognizble member\n";
                return;
            }
            currentState = transitionTable[indexCurrentState][indexAlphabet];
            std::cout << " ---> " << currentState;

            indexCurrentState = checkStateIndex(currentState);
        }
        std::cout << "\n";
    }

    State* getStates() override {
        return this->states;
    }

    int* getStatesCharacteristics() override {
        return this->statesCharacteristics;
    }

    int getNumberOfStates() override {
        return numberOfStates;
    }

    int getNumberOfAlphabet() override {
        return alphabet->getNumberOfMembers();
    }

    T* getElementsOfAlphabet() override {
        return alphabet->getElements();
    }

    State** getTransitionTable() override {
        return this->transitionTable;
    }

    void menu() override {
        std::cout << "\n[1] --> LOAD FROM FILE\n";
        std::cout << "[2] --> ENTER CUSTOM AUTOMATON\n";
        std::cout << "[3] --> ENTER A WORD = TRACE\n";
        std::cout << "[4] --> CHANGE START STATE\n";
        std::cout << "[5] --> ADD FINAL STATE\n";
        std::cout << "[6] --> DELETE FINAL STATE\n";
        std::cout << "[7] --> PRINT\n";
        std::cout << "[8] --> SAVE AS\n";
        std::cout << "[9] --> EXIT\n\n===>";
    }

    void start() override {
        char word[100];
        int choice = 0;
        while (choice != 9) {
            this->menu();
            std::cin >> choice;
            switch (choice) {
            case 1:
                this->load();
                break;

            case 2: {
                this->setNumberOfStates();
                this->setStates();
                this->setAlphabet();
                this->setStatesCharacteristics();
                this->setTransitionTable();
            };
                  break;
            case 3: {
                std::cin >> word;
                int lenght = 0;
                while (word[lenght])
                    lenght++;
                std::cout << this->read(word, lenght);
                this->trace(word, lenght);
            }
                  break;
            case 4:
                this->changeStartState();
                break;

            case 5:
                this->addFinalState();
                break;
            case 6:
                this->deleteFinalState();
                break;
            case 7:
                std::cout << *this;
                break;
            case 8:
                this->save();
                break;
            case 9:
                std::cout << "Exiting\n";
                break;
            }
        }


    }

    void load() override {
        int x;
        T y;
        std::ifstream input_data;
        std::string fileName;
        std::cout << "Enter file name to load Automaton: ";
        std::cin >> fileName;
        input_data.open(fileName);

        if (!input_data) {
            std::cout << "There is not such file as " << fileName << " !\n\n";
            return;
        }
        input_data >> x;
        input_data >> numberOfStates;
        states = nullptr;
        states = new State[numberOfStates];
        for (int i = 0; i < numberOfStates; i++)
            input_data >> states[i];

        input_data >> x;
        alphabet = nullptr;
        alphabet = new Alphabet<T>(x);
        for (int i = 0; i < x; i++) {
            input_data >> y;
            alphabet->setElement(i, y);
        }
        transitionTable = nullptr;
        transitionTable = new State * [numberOfStates];

        for (int i = 0; i < numberOfStates; ++i)
            transitionTable[i] = new State[alphabet->getNumberOfMembers()];

        for (int i = 0; i < numberOfStates; i++)
            for (int j = 0; j < alphabet->getNumberOfMembers(); j++) {
                input_data >> transitionTable[i][j];
            }
        statesCharacteristics = nullptr;
        statesCharacteristics = new int[numberOfStates];
        //
        State state;
        input_data >> state;
        statesCharacteristics[checkStateIndex(state)] = 1;
        input_data >> x;
        for (int i = 0; i < x; i++) {
            input_data >> state;
            statesCharacteristics[checkStateIndex(state)] += 2;
        }

    }

    void save() override {
        std::string fileName;
        std::cout << "Enter file name to save current Automaton: ";
        std::cin >> fileName;
        fileName += ".txt";
        std::ofstream output_data;
        output_data.open(fileName);
        output_data.ate;
        output_data << *this;
        output_data.close();
        std::cout << "File has been saved to:" << fileName << "\n";
    }

    void changeStartState() override {
        State newStartState = validStateInput();
        statesCharacteristics[startStateIndex()]--;
        statesCharacteristics[checkStateIndex(newStartState)]++;
    }

    void addFinalState() override {
        State addFinal = validStateInput();
        if (statesCharacteristics[checkStateIndex(addFinal)] > 1) {
            std::cout << "Already final\n";
            return;
        }
        else
            statesCharacteristics[checkStateIndex(addFinal)] += 2;
    }

    void deleteFinalState() override {
        State deleteFinal = validStateInput();
        if (statesCharacteristics[checkStateIndex(deleteFinal)] < 2) {
            std::cout << "Not final\n";
            return;
        }
        else
            statesCharacteristics[checkStateIndex(deleteFinal)] -= 2;

    }
};

//Çà äà ïğîâåğèì äàëè Àâòîìàòúò å îò òèï int èëè char
template<class T>
struct TypeIsInt {
    static const bool value = false;
};

template<>
struct TypeIsInt<int> {
    static const bool value = true;
};

template<typename T>
std::ostream& operator<<(std::ostream& out, Automaton<T>& automaton) {
    int numberOfStates = automaton.getNumberOfStates();
    int numberOfElementOfAlphabet = automaton.getNumberOfAlphabet();
    State** transitionTable = automaton.getTransitionTable();
    int* statesCharacteristics = automaton.getStatesCharacteristics();
    State* states = automaton.getStates();
    if (TypeIsInt<T>::value)
        out << 1 << "\n";
    else
        out << 2 << "\n";
    out << numberOfStates << " ";
    for (int i = 0; i < numberOfStates; i++)
        out << states[i].getStateName() << " ";
    out << "\n" << numberOfElementOfAlphabet << " ";
    for (int i = 0; i < numberOfElementOfAlphabet; i++)
        out << automaton.getElementsOfAlphabet()[i] << " ";
    out << "\n";
    for (int i = 0; i < numberOfStates; i++) {
        for (int j = 0; j < numberOfElementOfAlphabet; j++) {
            out << transitionTable[i][j].getStateName() << " ";
        }
        out << "\n";
    }
    out << automaton.startState().getStateName() << "\n";
    out << automaton.finalStatesNumber() << " ";
    for (int i = 0; i < numberOfStates; i++)
        if (statesCharacteristics[i] > 1)
            out << states[i].getStateName() << " ";
    out << "\n";
    return out;
}

#endif //AUTOMATON_AUTOMATON_H
