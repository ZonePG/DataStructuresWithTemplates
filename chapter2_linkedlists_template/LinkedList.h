#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include <cstddef>
#include <memory>
#include <cstring>
#include <iostream>

template <typename T>
class LinkedList {
public:
    class iterator;
    LinkedList();
    ~LinkedList();
    T* front();
    T* back();
    bool push_front(T*);
    bool push_back(T*);
    void pop_front();
    void pop_back();
    void clear();
    bool empty();
    iterator begin();
    iterator end();
    iterator rbegin();
    iterator rend();
    size_t size();

    iterator insert(iterator, T*);

    void reverse();
    void sort();

    using Comparator = int(*)(T*, T*);
    void sort(Comparator);

private:
    size_t tSize, nSize, lSize;
    struct lNode {
        lNode* next;
        lNode* back;
        T *data;
    };
    struct {
        lNode *lStart = nullptr;
        lNode *lEnd = nullptr;
    } lList;
    struct lNode* createNode(const T*);
    void deleteList();
};

template <typename T>
class LinkedList<T>::iterator {
public:
    iterator(typename LinkedList<T>::lNode* pos, bool forward) {
        this->pos = pos;
        this->forward = forward;    // store iterator type
    }
    T operator*() const { return *(pos->data); }    // amend T&
    iterator& operator++() {
        if (forward) {
            pos = pos->next;
        } else {
            pos = pos->back;
        }
        return *this;
    }
    iterator& operator++(int) {
        if (forward) {
            pos = pos->next;
        } else {
            pos = pos->back;
        }
        return *this;
    }
    iterator& operator--() {
        if (forward) {
            pos = pos->back;
        } else {
            pos = pos->next;
        }
        return *this;
    }
    iterator& operator--(int) {
        if (forward) {
            pos = pos->back;
        } else {
            pos = pos->next;
        }
        return *this;
    }
    bool operator!=(const iterator a) {
        return (this->pos != (a.pos));
    }

// protected:  // why protected
    typename LinkedList<T>::lNode* pos;
// private:
    bool forward;
};

// constructor
template <typename T>
LinkedList<T>::LinkedList() {
    tSize = sizeof(T);
    nSize = sizeof(lNode);
    lSize = 0;
}

// destructor
template <typename T>
LinkedList<T>::~LinkedList() {
    deleteList();
}

template <typename T>
T* LinkedList<T>::front() {
    if (lList.lStart) {
        return lList.lStart->data;
    }
    return nullptr;
}

template <typename T>
T* LinkedList<T>::back() {
    if (lList.lEnd) {
        return lList.lEnd->data;
    }
    return nullptr;
}

template <typename T>
bool LinkedList<T>::push_front(T *data) {
    lNode *nNode = createNode(data);
    if (nNode == nullptr) {
        return false;
    }
    if (lList.lStart) {
        lList.lStart->back = nNode;
    }
    nNode->next = lList.lStart;
    lList.lStart = nNode;
    if (lList.lEnd == nullptr) {
        lList.lEnd = nNode;
    }
    ++lSize;
    return true;
}

template <typename T>
bool LinkedList<T>::push_back(T *data) {
    lNode *nNode = createNode(data);
    if (nNode == nullptr) {
        return false;
    }
    if (lList.lEnd == nullptr) {
        lList.lStart = lList.lEnd = nNode;
    } else {
        nNode->back = lList.lEnd;
        lList.lEnd = lList.lEnd->next = nNode;
    }
    ++lSize;
    return true;
}

template <typename T>
void LinkedList<T>::pop_front() {
    if (lList.lStart) {
        lNode *d = lList.lStart;
        lList.lStart = d->next;
        if (d->next) {
            d->next->back = nullptr;
        }
        free(d->data);
        free(d);
        --lSize;
    }
}

template <typename T>
void LinkedList<T>::pop_back() {
    if (lList.lEnd) {
        lNode *d = lList.lEnd;
        lList.lEnd = d->back;
        if (d->back) {
            d->back->next = nullptr;
        }
        free(d->data);
        free(d);
        --lSize;
    }
}

template <typename T>
typename LinkedList<T>::lNode *LinkedList<T>::createNode(const T *t) {
    lNode *nNode = (lNode *)malloc(nSize);
    if (nNode != nullptr) {
        nNode->data = (T *)malloc(tSize);
        if (nNode->data == nullptr) {
            return nullptr;
        }
        memcpy(nNode->data, t, tSize);
        nNode->next = nullptr;
        nNode->back = nullptr;
    }
    return nNode;
}

template <typename T>
void LinkedList<T>::deleteList() {
    lNode* dNode = lList.lStart;
    while (dNode != nullptr) {
        lList.lStart = dNode->next;
        free(dNode->data);
        free(dNode);
        dNode = lList.lStart;
    }
    lList.lEnd = lList.lStart = nullptr;
    lSize = 0;
}

template <typename T>
void LinkedList<T>::clear() {
    deleteList();
}

template <typename T>
bool LinkedList<T>::empty() {
    return (lList.lStart == nullptr);
}

template <typename T>
typename LinkedList<T>::iterator LinkedList<T>::begin() {
    iterator it(lList.lStart, true);
    return it;
}

template <typename T>
typename LinkedList<T>::iterator LinkedList<T>::end() {
    iterator it(nullptr, true);
    return it;
}

template <typename T>
typename LinkedList<T>::iterator LinkedList<T>::rbegin() {
    iterator it(lList.lEnd, false);
    return it;
}

template <typename T>
typename LinkedList<T>::iterator LinkedList<T>::rend() {
    iterator it(nullptr, false);
    return it;
}

template <typename T>
size_t LinkedList<T>::size() {
    return lSize;
}

template <typename T>
typename LinkedList<T>::iterator LinkedList<T>::insert(iterator it, T* data) {
    if (it.pos && it.pos != lList.lStart) {
        // we know there is previous and next node
        lNode *nNode = createNode(data);
        if (nNode != nullptr) {
            nNode->back = it.pos->back;
            nNode->next = it.pos;
            nNode->back->next = it.pos->back = nNode;
            iterator newIt(nNode, it.forward);
            lSize++;    // increment the new size variable
            return newIt;
        }
    } else {
        // empty list or iterator at end() or iterator at start
        if (!it.forward || it.pos == lList.lStart) {
            if (push_front(data)) {
                iterator newIt(lList.lStart, it.forward);
                return newIt;
            }
        } else {
            if (push_back(data)) {
                iterator newIt(lList.lEnd, it.forward);
                return newIt;
            }
        }
    }
    // signal that something went wrong
    // probably allocating memory
    return it.forward ? end() : rend();
}

template <typename T>
void LinkedList<T>::reverse() {
    iterator fw = begin();
    iterator bw = rbegin();
    T* temp;
    for (; fw.pos != bw.pos && fw.pos->back != bw.pos; fw++, bw++) {
        temp = bw.pos->data;
        bw.pos->data = fw.pos->data;
        fw.pos->data = temp;
    }
}

template <typename T>
void LinkedList<T>::sort() {
    lNode *nLoop, *nTest;
    T *temp;
    bool swp;
    if (lList.lStart == lList.lEnd) {
        // empty or just one item so done
        return ;
    }
    nTest = lList.lStart->next;
    while (nTest) {
        if (*nTest->data < *nTest->back->data) {
            // this item is out of order so insert it earlier in list
            swp = true;
            nLoop = lList.lStart;
            while (swp) {
                swp = false;
                for (; nLoop != nTest; nLoop = nLoop->next) {
                    // loop through the previous item in list
                    if (*nTest->data < *nLoop->data) {
                        // if a prior item is smaller then swap
                        temp = nLoop->data;
                        nLoop->data = nTest->data;
                        nTest->data = temp;
                        swp = true;
                        break;
                    }
                }
            }
        }
        nTest = nTest->next;
    }

    // if (lList.lStart == lList.lEnd) {
    //     // empty or just one item so done
    //     return ;
    // }
    // lNode *nLoop, *nTest;
    // T *temp;
    // for (nTest = lList.lStart; nTest != lList.lEnd; nTest = nTest->next) {
    //     for (nLoop = nTest->next; nLoop != nullptr; nLoop = nLoop->next) {
    //         if (*nTest->data > *nLoop->data) {
    //             temp = nLoop->data;
    //             nLoop->data = nTest->data;
    //             nTest->data = temp;
    //         }
    //     }
    // }
}

template <typename T>
void LinkedList<T>::sort(Comparator cmpFunc) {
    lNode *nLoop, *nTest;
    T* temp;
    bool swp;
    if (lList.lStart == lList.lEnd) {
        // empty or just one item so done
        return ;
    }
    nTest = lList.lStart->next; // start at second item in list
    while (nTest) {
        if (cmpFunc(nTest->data, nTest->back->data) < 0) {
            // this item is out of order so insert it earlier in list
            swp = true;
            nLoop = lList.lStart;
            while (swp) {
                swp = false;
                for (; nLoop != nTest; nLoop = nLoop->next) {
                    // loop through the previous items in the list
                    if (cmpFunc(nTest->data, nLoop->data) < 0) {
                        // if a prior item is smaller then swap
                        temp = nLoop->data;
                        nLoop->data = nTest->data;
                        nTest->data = temp;
                        swp = true;
                        break;
                    }
                }
            }
        }
        nTest = nTest->next;
    }
}

#endif