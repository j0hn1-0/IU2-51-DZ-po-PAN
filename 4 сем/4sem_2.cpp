#include <iostream>

class Trajectory {
    double x, y, angle;
    
public:
    Trajectory() : x(0), y(0), angle(0) {}
    Trajectory(double px, double py, double a) : x(px), y(py), angle(a) {}
    
    void print() const {
        std::cout << "Start(" << x << "," << y << ") angle=" << angle << "\n";
    }
};

int main() {
    Trajectory t1;
    Trajectory t2(100, 200, 45);
    
    t1.print();
    t2.print();
    
    return 0;
}