#include "linked_lists.h"
#include <iostream>
#include <memory>

extern linked_lists lList;

bool appendToList(int data) {
    lNode *nNode = createNode(data);
    if (nNode == nullptr) {
        return false;
    }
    if (lList.lStart == nullptr) {
        lList.lStart = nNode;
        lList.lEnd = nNode;
    } else {
        lList.lEnd = lList.lEnd->next = nNode;
    }
    return true;
}

lNode *createNode(int data) {
    lNode *rNode = (lNode *)malloc(sizeof(lNode));
    if (rNode != nullptr) {
        rNode->data = data;
        rNode->next = nullptr;
    }
    return rNode;
}

void deleteList() {
    lNode *rNode = lList.lStart;
    while (rNode != nullptr) {
        lList.lStart = rNode->next;
        free(rNode);
        rNode = lList.lStart;
    }
    lList.lEnd = lList.lStart = nullptr;
}

bool insertInlist(int data) {
    lNode* nNode = createNode(data);
    if (nNode == nullptr) {
        return false;
    }
    if (lList.lStart == nullptr) {
        lList.lStart = nNode;
        lList.lEnd = nNode;
    }
    else {
        // we need to look for the correct slot
        if (data <= lList.lStart->data) {
            // New value is <= first value in list
            nNode->next = lList.lStart;
            lList.lStart = nNode;
        }
        else {
            lNode* rNode = lList.lStart;
            while (rNode) {
                if (rNode->next != nullptr && data <= rNode->next->data) {
                    // rNode->next != nullptr is important!!!!
                    // found the insertion point
                    nNode->next = rNode->next;
                    rNode->next = nNode;
                    break;
                }
                rNode = rNode->next;
                if (!rNode) {
                    lList.lEnd = lList.lEnd->next = nNode;
                }

                // if (rNode->next == nullptr) {
                //     lList.lEnd = lList.lEnd->next = nNode;
                //     break;   // important!!!!or else twice free
                // }
                // if (data <= rNode->next->data) {
                //     // found the insertion point
                //     nNode->next = rNode->next;
                //     rNode->next = nNode;
                //     break;
                // }
                // rNode = rNode->next;
            }
        }
    }
    return true;
}

bool push_front(int data) {
    lNode* nNode = createNode(data);
    if (nNode == nullptr) {
        return false;
    }
    nNode->next = lList.lStart;
    lList.lStart = nNode;
    if (lList.lEnd == nullptr) {
        lList.lEnd = nNode;
    }

    return true;
}

int* readNode(bool start) {
    static lNode* last;
    if (start) {
        last = lList.lStart;
    }
    else {
        if (last) {
            last = last->next;
        }
    }
    if (last) {
        return &(last->data);
    }
    return nullptr;
}