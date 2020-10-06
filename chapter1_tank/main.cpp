#include "tank.h"
#include <iostream>

int main() {
    Tank tank1(23.4, 67, 12);
    Tank tank2;
    Tank *p = new Tank(3, 5, 8);
    double d1 = tank1.maxVolume();
    double d2 = tank2.maxVolume();
    double d3 = p->maxVolume();
    std::cout << d1 << std::endl;
    std::cout << d2 << std::endl;
    std::cout << d3 << std::endl;
}