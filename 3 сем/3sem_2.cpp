#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<double> h = {10, 30, 50, 40, 20};
    std::vector<double> t = {1, 2, 3, 4, 5};
    
    if (h.empty()) return 0;
    
    auto it = std::max_element(h.begin(), h.end());
    int pos = std::distance(h.begin(), it);
    
    std::cout << "Max height: " << h[pos] << " at t=" << t[pos] << "\n";
    
    return 0;
}