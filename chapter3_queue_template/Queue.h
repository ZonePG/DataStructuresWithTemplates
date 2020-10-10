#include "List.h"

template <typename T>
class Queue : public List<T> {
public:
    bool push(T*);
    void pop();

    T front2();

    T deQueue();
};

template <typename T>
bool Queue<T>::push(T* t) {
    return (this->push_back(t));
}

template <typename T>
void Queue<T>::pop() {
    this->pop_front();
}

template <typename T>
T Queue<T>::front2() {
    T* t = this->front();
    return *t;
}

template <typename T>
T Queue<T>::deQueue() {
    T* t = this->front();
    T tt = *t;

    std::cout << "change " << std::endl;
    this->pop_front();
    return tt;
}