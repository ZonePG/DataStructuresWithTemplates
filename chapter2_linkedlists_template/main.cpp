#include "LinkedList.h"
#include <iostream>

struct MyData {
    int valueC;
    int valueD;
};

int compMyData(MyData* a, MyData* b) {
    if (a->valueC < b->valueC) { return -1; }
    if (b->valueC < a->valueC) { return 1; }
    if (a->valueD < b->valueD) { return -1; }
    if (b->valueD < a->valueD) { return 1; }
    return 0;
}

int compMyDataRev(MyData *a, MyData *b) {
    if (a->valueC < b->valueC) { return 1; }
    if (b->valueC < a->valueC) { return -1; }
    if (a->valueD < b->valueD) { return 1; }
    if (b->valueD < a->valueD) { return -1; }
    return 0;
}

int compMyDataD(MyData *a, MyData *b) {
    if (a->valueD < b->valueD) { return -1; }
    if (b->valueD < a->valueD) { return 1; }
    if (a->valueC < b->valueC) { return -1; }
    if (b->valueC < a->valueC) { return 1; }
    return 0;
}


int main() {
    int vals[] = { 23, 54, 98, 1, 3, 99, 67, 83, 27, 16, 9 };
    LinkedList<int> newList;
    for (int i = 0; i < 11; i++) {
        newList.push_front(&vals[i]);
    }
    int newVal = 5;
    LinkedList<int>::iterator it = newList.begin();
    // the order of the tests for the while is important
    while (it != newList.end() && *it <= newVal) {
        it++;
    }
    newList.insert(it, &newVal);
    std::cout << "After insert of 5" << std::endl;
    for (LinkedList<int>::iterator it = newList.begin(); it != newList.end(); it++) {
        std::cout << *it << std::endl;
    }

    *newList.front() = 3;
    std::cout << "First: " << *newList.front() << " Last: " << *newList.back() << std::endl;

    std::cout << "sort(): " << std::endl;
    newList.sort();
    for (LinkedList<int>::iterator it = newList.begin(); it != newList.end(); it++) {
        std::cout << *it << std::endl;
    }
    newList.clear();


    LinkedList<MyData> newList2;
    MyData myData;
    for (int i = 0; i < 20; i++) {
        myData.valueC = rand() % 49;
        myData.valueD = rand() % 11;
        newList2.push_back(&myData);
    }
    newList2.sort(compMyDataRev);
    for (LinkedList<MyData>::iterator it = newList2.begin(); it != newList2.end(); it++) {
        std::cout << "Value C: " << (*it).valueC << " Value D: " << (*it).valueD << std::endl;
    }
    newList2.clear();

    return 0;
}