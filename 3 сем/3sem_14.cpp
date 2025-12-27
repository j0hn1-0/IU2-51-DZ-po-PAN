#include <iostream>
#include <vector>
#include <numeric>
#include <cmath>

int main() {
    std::vector<double> y = {0, 10, 25, 45, 70, 100};
    
    double path = 0;
    for (size_t i = 1; i < y.size(); i++) {
        path += std::abs(y[i] - y[i-1]);
    }
    
    std::cout << "Total path: " << path << "\n";
    
    return 0;
}