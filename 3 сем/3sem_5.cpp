#include <iostream>

struct Pos { double x, y, z; };

int main() {
    double vx = 30, vy = 20, vz = 40, dt = 0.1, T = 10;
    Pos p = {0, 0, 0};
    
    std::cout << "t     x     y     z\n";
    for (double t = 0; t <= T; t += dt) {
        p.x += vx * dt;
        p.y += vy * dt;
        p.z += vz * dt;
        printf("%4.1f %5.1f %5.1f %5.1f\n", t, p.x, p.y, p.z);
    }
    
    return 0;
}