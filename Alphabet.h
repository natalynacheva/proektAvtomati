#ifndef ALPHABET_H
#define ALPHABET_H
#include <iostream>
#include <fstream>
template <typename T>
class Alphabet
{
private:
    int numberOfMembers;
    T* elements;
public:
    Alphabet(int numberOfMembers) {
        this->numberOfMembers = numberOfMembers;
        this->elements = new T[numberOfMembers];
    }

    void setElements() {
        int isThere;
        for (int i = 0; i < numberOfMembers;) {
            isThere = 0;
            std::cout << "Element[" << i + 1 << "] ==> ";
            std::cin >> elements[i];
            for (int j = 0; j < i; j++)
                if (elements[j] == elements[i]) {
                    isThere = 1;
                    std::cout << "All elements must be unique!\n";
                }
            if (isThere == 0)
                i++;
        }
    }

    void setElement(int index, T element) {
        elements[index] = element;
    }
    T getElement(int i) {
        return elements[i];
    }

    T* getElements() {
        return this->elements;
    }

    int getNumberOfMembers() {
        return numberOfMembers;
    }
};

#endif // ALPHABET_H