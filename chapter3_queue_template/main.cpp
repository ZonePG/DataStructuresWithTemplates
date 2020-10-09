#include "Queue.h"
#include <iostream>
#include <cstdlib>

int main() {
    Queue<int> queue;
    for (int i = 0; i < 10; i++) {
        int l = rand() % 23;
        queue.push(&l);
    }
    std::cout << "Front: " << queue.front2() << " Back: " << *queue.back() << std::endl;
    queue.pop();
    std::cout << "After pop Front: " << queue.front2() << " Back: " << *queue.back() << " Size: " << queue.size() << std::endl;

    std::cout << "Testing deQueue:" << queue.deQueue() << std::endl;
}