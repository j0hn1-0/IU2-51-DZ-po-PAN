#include <iostream>

int main() {
    double v0 = 50, g = 9.8, dt = 1;
    
    std::cout << "t(s)  v(m/s)\n";
    for (double t = 0; t <= v0*2/g; t += dt) {
        double v = v0 - g * t;
        printf("%4.1f %6.1f\n", t, v);
    }
    
    return 0;
}