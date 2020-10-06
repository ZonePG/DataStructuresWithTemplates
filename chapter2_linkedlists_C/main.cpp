#include "linked_lists.h"
#include <iostream>

linked_lists lList;

int main() {
    push_front(99);
    for (int i = 0; i < 14; i++) {
        // bool added = appendToList((rand()) % 23);
        bool added = insertInlist((int)rand() % 23);
        // bool added = insertInlist((int)rand()); // if rNode->next != nullptr is missed, then segment error occurs
    }
    lNode *i = lList.lStart;
    while (i != nullptr) {
        std::cout << i->data << std::endl;
        i = i->next;
    }
    int *ip = readNode(true);
    while (ip) {
        std::cout << *ip << std::endl;
        ip = readNode();
    }

    deleteList();
    // std::cin.get();
    return 0;
}