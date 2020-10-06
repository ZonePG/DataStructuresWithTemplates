#include "tank.h"

Tank::Tank(double length, double breadth, double height) {
    this->length = length;
    this->breadth = breadth;
    this->height = height;
}

Tank::Tank() {
    length = breadth = height = 0;
}

Tank::~Tank() {
    /* a simple class like this
     * does not need a destructor as
     * there is noting to clean up
     */
}

void Tank::setDimensions(double length, double breadth, double height) {
    this->length = length;
    this->breadth = breadth;
    this->height = height;
}

double Tank::maxVolume() {
    return length * breadth * height;
}