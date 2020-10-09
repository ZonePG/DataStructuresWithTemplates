#ifndef LIST_H_
#define LIST_H_

#include <cstring>
#include <memory>
#include <cstddef>

template <typename T>
class List {
public:
    List();
    ~List();
    bool push_back(T *);
    void clear();
    bool empty();
    T *front();
    T *back();
    void pop_front();
    size_t size();

private:
    size_t tSize, nSize, lSize;
    struct lNode {
        lNode *next;
        T *data;
    };
    struct {
        lNode *lStart = nullptr;
        lNode *lEnd = nullptr;
    } lList;
    lNode *createNode(const T *);
    void deleteList();
};

// constructor and destructor
template <typename T>
List<T>::List() {
    tSize = sizeof(T);
    nSize = sizeof(lNode);
    lSize = 0;
}

template <typename T>
List<T>::~List() {
    deleteList();
}

template <typename T>
bool List<T>::push_back(T *data) {
    lNode *nNode = createNode(data);
    if (nNode == nullptr) {
        return false;
    }
    if (lList.lStart == nullptr) {
        lList.lStart = lList.lEnd = nNode;
    } else {
        lList.lEnd = lList.lEnd->next = nNode;
    }
    ++lSize;
    return true;
}

template <typename T>
void List<T>::clear() {
    deleteList();
}
template <typename T>
bool List<T>::empty() {
    return (lList.lStart = nullptr);
}
template <typename T>
size_t List<T>::size() {
    return lSize;
}

template <typename T>
T *List<T>::front() {
    if (lList.lStart) {
        return lList.lStart->data;
    }
    return nullptr;
}

template <typename T>
T *List<T>::back() {
    if (lList.lEnd) {
        return lList.lEnd->data;
    }
    return NULL;
}

template <typename T>
void List<T>::pop_front() {
    if (lList.lStart) {
        lNode *d = lList.lStart;
        lList.lStart = d->next;
        free(d->data);
        free(d);
        lSize--;
    }
}

template <typename T>
typename List<T>::lNode *List<T>::createNode(const T *t) {
    lNode *nNode = (lNode *)malloc(nSize);
    if (nNode != nullptr) {
        nNode->data = (T *)malloc(tSize);
        if (nNode->data == nullptr) {
            return nullptr;
        }
        memcpy(nNode->data, t, tSize);
        nNode->next = nullptr;
    }
    return nNode;
}

template <typename T>
void List<T>::deleteList() {
    lNode *dNode = lList.lStart;
    while (dNode != nullptr) {
        lList.lStart = dNode->next;
        free(dNode->data);
        free(dNode);
        dNode = lList.lStart;
        lSize = 0;
    }
    lList.lEnd = lList.lStart = nullptr;
}

#endif