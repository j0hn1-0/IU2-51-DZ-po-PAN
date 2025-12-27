#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<double> h1 = {0, 20, 40, 60, 40, 20, 0};
    std::vector<double> h2 = {0, 30, 50, 70, 50, 30, 10};
    std::vector<double> t = {0, 1, 2, 3, 4, 5, 6};
    
    auto m1 = *std::max_element(h1.begin(), h1.end());
    auto m2 = *std::max_element(h2.begin(), h2.end());
    
    std::cout << "Rocket1 max: " << m1 << "\n";
    std::cout << "Rocket2 max: " << m2 << "\n";
    
    if (m1 > m2) std::cout << "Rocket1 higher\n";
    else if (m2 > m1) std::cout << "Rocket2 higher\n";
    else std::cout << "Equal\n";
    
    return 0;
}