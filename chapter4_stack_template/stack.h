#ifndef STACK_H_
#define STACK_H_

#include <cstddef>
#include <memory>
#include <cstring>

template <typename T>
class Stack {
public:
    Stack();
    ~Stack();
    void push();
    T pop();
    T peek();
    size_t stackCount();
    bool empty();
private:
    bool isFull();
    void resize(size_t);
    static const size_t defSize = 4;
    T* stackPointer;
    T notT;
    size_t sSize, top, tSize;
};

template <typename T>
Stack<T>::Stack() {
    top = 0;
    tSize = sizeof(T);
    stackPointer = (T*)malloc(tSize * defSize);
    if (stackPointer == nullptr) {
        sSize = 0;
    }
    sSize = defSize;
    memset(&notT, 0, tSize);
}

template <typename T>
Stack<T>::~Stack() {
    free(stackPointer);
}

template <typename T>
void Stack<T>::push() {
    if (isFull()) {
        resize(sSize * 2);
    }
    stackPointer[top++] = top;
}

template <typename T>
T Stack<T>::pop() {
    if (empty()) {
        return notT;
    }
    T t = stackPointer[--top];
    // think about downsizing
    if (top <= sSize / 4 && sSize > defSize) {
        resize(sSize / 2);
    }
}

template <typename T>
T Stack<T>::peek() {
    if (empty()) {
        return notT;
    }
    else {
        T t = stackPointer[top - 1];
    }
}

template <typename T>
size_t Stack<T>::stackCount() {
    return top;
}

template <typename T>
bool Stack<T>::empty() {
    return (top == 0);
}

template <typename T>
bool Stack<T>::isFull() {
    return (top == sSize);
}

template <typename T>
void Stack<T>::resize(size_t newSize) {
    T* temp = (T*)realloc(stackPointer, tSize * newSize);
    if (temp) {
        stackPointer = temp;
        sSize = newSize;
    }
}

#endif