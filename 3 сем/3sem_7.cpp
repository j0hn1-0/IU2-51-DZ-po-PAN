#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<double> h = {50, 40, 30, 20, 10, 0, -5};
    std::vector<double> t = {0, 1, 2, 3, 4, 5, 6};
    
    auto it = std::find_if(h.begin(), h.end(),
        [](double x) { return x <= 0; });
    
    if (it != h.end()) {
        int idx = std::distance(h.begin(), it);
        std::cout << "Fall at t=" << t[idx] << " h=" << h[idx] << "\n";
    }
    
    return 0;
}