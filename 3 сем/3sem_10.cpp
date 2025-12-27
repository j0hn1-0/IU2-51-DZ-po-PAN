#include <iostream>
#include <vector>

struct Rocket {
    double x, y, z, vx, vy, vz;
    
    void move(double dt) {
        x += vx * dt;
        y += vy * dt;
        z += vz * dt;
    }
    
    void print() {
        printf("(%.1f,%.1f,%.1f)", x, y, z);
    }
};

int main() {
    std::vector<Rocket> rockets = {
        {0,0,0, 100,10,0},
        {0,0,0, 90,15,-5},
        {0,0,0, 110,5,10}
    };
    
    double dt = 0.1;
    for (double t = 0; t <= 10; t += dt) {
        for (auto& r : rockets) r.move(dt);
    }
    
    for (size_t i = 0; i < rockets.size(); i++) {
        std::cout << "Rocket" << i+1 << " ";
        rockets[i].print();
        std::cout << "\n";
    }
    
    return 0;
}