#include <iostream>

class NavSys {
    double x, y, vx, vy;
    bool gps;
    
public:
    NavSys(double px, double py, double vpx, double vpy, bool g) 
        : x(px), y(py), vx(vpx), vy(vpy), gps(g) {}
    
    void move(double dt) {
        x += vx * dt;
        y += vy * dt;
    }
    
    void correct(double gx, double gy) {
        if (gps) {
            x = (x + gx) / 2;
            y = (y + gy) / 2;
        }
    }
    
    void print() const {
        std::cout << "Pos(" << x << "," << y << ")\n";
    }
};

int main() {
    NavSys ns(0, 0, 100, 50, true);
    ns.move(1.0);
    ns.correct(10, 60);
    ns.print();
    
    return 0;
}