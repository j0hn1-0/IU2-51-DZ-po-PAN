#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<double> h = {15, 5, 20, 8, 30, 3};
    
    h.erase(std::remove_if(h.begin(), h.end(),
        [](double x) { return x < 10; }), h.end());
    
    for (auto x : h) std::cout << x << " ";
    
    return 0;
}