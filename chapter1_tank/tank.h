#ifndef TANK_H_
#define TANK_H_

class Tank {
public:
    Tank(double, double, double);
    Tank();
    ~Tank();
    void setDimensions(double, double, double);
    double maxVolume();
private:
    double length;
    double breadth;
    double height;
};

#endif