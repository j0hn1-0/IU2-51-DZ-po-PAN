#include <iostream>
#include <vector>
#include <cmath>

int main() {
    double v = 50.0, g = 9.8, dt = 1.0;
    std::vector<std::pair<double, double>> data;
    
    for (double t = 0; ; t += dt) {
        double h = v * t - 0.5 * g * t * t;
        if (h < 0) break;
        data.push_back({t, h});
    }
    
    std::cout << "t(s)  h(m)\n";
    for (auto& p : data) {
        printf("%4.1f %6.1f\n", p.first, p.second);
    }
    
    return 0;
}