#ifndef LINKED_LISTS_H_
#define LINKED_LISTS_H_

#include <cstddef>

struct lNode {
    struct lNode *next;
    int data;
};

struct linked_lists {
    lNode *lStart = nullptr;
    lNode *lEnd = nullptr;
};

bool appendToList(int);
lNode *createNode(int);
void deleteList();

bool insertInlist(int data);
bool push_front(int data);

int* readNode(bool = false);

#endif