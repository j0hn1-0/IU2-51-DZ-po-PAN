#include <iostream>

class AutoControl {
    double h, t, target;
    
public:
    AutoControl(double alt, double thr, double tar) 
        : h(alt), t(thr), target(tar) {}
    
    void update() {
        if (h < target) t += 100;
        else t -= 100;
        if (t < 0) t = 0;
    }
    
    void step(double dt) {
        h += (t/500) * dt;
    }
    
    void print() const {
        std::cout << "H=" << h << " T=" << t << "\n";
    }
};

int main() {
    AutoControl ac(0, 2000, 5000);
    for (int i = 0; i < 5; i++) {
        ac.update();
        ac.step(1.0);
        ac.print();
    }
    
    return 0;
}