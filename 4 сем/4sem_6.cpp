#include <iostream>

class Stage {
    double thrust, time, mass;
    
public:
    Stage(double t, double ti, double m) : thrust(t), time(ti), mass(m) {}
    
    double getDeltaV() const {
        return (mass == 0) ? 0 : (thrust * time) / mass;
    }
    
    void print() const {
        std::cout << "T=" << thrust 
                  << " t=" << time 
                  << " m=" << mass 
                  << " dV=" << getDeltaV() << "\n";
    }
};

int main() {
    Stage s1(5000, 10, 1000);
    Stage s2(7000, 8, 900);
    Stage s3(9000, 6, 800);
    
    double total = s1.getDeltaV() + s2.getDeltaV() + s3.getDeltaV();
    std::cout << "Total dV: " << total << "\n";
    
    return 0;
}