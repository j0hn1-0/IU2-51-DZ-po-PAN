#include <iostream>

class Sensor {
    double signal;
    bool active;
    
public:
    Sensor(double s) : signal(s > 0 ? s : 0), active(true) {}
    
    void on() { active = true; }
    void off() { active = false; }
    
    void setSignal(double s) { 
        signal = s > 0 ? s : 0; 
    }
    
    double getSignal() const { return signal; }
    
    void print() const {
        std::cout << (active ? "ON" : "OFF") 
                  << " signal=" << signal << "dB\n";
    }
};

int main() {
    Sensor s(45.5);
    s.print();
    
    s.setSignal(-10);
    s.print();
    
    s.off();
    s.print();
    
    return 0;
}