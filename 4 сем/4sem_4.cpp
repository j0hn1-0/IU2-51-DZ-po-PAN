#include <iostream>

class Gyroscope {
    double speed;
    bool needsCalib;
    
public:
    Gyroscope(double s, bool c) : speed(s), needsCalib(c) {}
    
    void calibrate() { needsCalib = false; }
    
    void print() const {
        std::cout << "Speed=" << speed 
                  << " Calib=" << (needsCalib ? "NEEDED" : "OK") << "\n";
    }
};

int main() {
    Gyroscope g(120.5, true);
    g.print();
    
    g.calibrate();
    g.print();
    
    return 0;
}