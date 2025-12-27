#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<double> h = {0, 50, 100, 80, 60, 40, 20, 0};
    std::vector<double> t = {0, 1, 2, 3, 4, 5, 6, 7};
    
    auto it = std::max_element(h.begin(), h.end());
    int pos = std::distance(h.begin(), it);
    
    std::cout << "Max h=" << h[pos] << " at t=" << t[pos] << "\n";
    
    return 0;
}