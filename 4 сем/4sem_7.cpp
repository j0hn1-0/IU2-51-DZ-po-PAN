#include <iostream>

class FlightComp {
    double h, v, f, t;
    
public:
    FlightComp(double a, double s, double fl, double th) 
        : h(a), v(s), f(fl), t(th) {}
    
    void step(double dt) {
        if (f <= 0) return;
        v += (t/1000 - 9.8) * dt;
        h += v * dt;
        f -= dt * 2;
        if (f < 0) f = 0;
    }
    
    void print() const {
        std::cout << "H=" << h 
                  << " V=" << v 
                  << " F=" << f << "\n";
    }
};

int main() {
    FlightComp fc(0, 0, 100, 12000);
    for (int i = 0; i < 5; i++) {
        fc.step(0.5);
        fc.print();
    }
    
    return 0;
}