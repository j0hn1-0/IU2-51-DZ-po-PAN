#include <iostream>

class Engine {
    double thrust, flow;
    
public:
    Engine(double t, double f) : thrust(t), flow(f) {}
    
    double getImpulse() const {
        return (flow == 0) ? 0 : thrust / (flow * 9.81);
    }
    
    void print() const {
        std::cout << "Thrust=" << thrust 
                  << " Flow=" << flow
                  << " Isp=" << getImpulse() << "\n";
    }
};

int main() {
    Engine e(5000, 2.5);
    e.print();
    
    return 0;
}