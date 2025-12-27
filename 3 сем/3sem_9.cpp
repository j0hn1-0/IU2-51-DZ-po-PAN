#include <iostream>
#include <vector>

int main() {
    std::vector<double> h = {10, 12, 11.5, 13, 12.5, 11, 10.5};
    std::vector<double> smooth(h.size());
    
    for (size_t i = 0; i < h.size(); i++) {
        if (i == 0 || i == h.size()-1) {
            smooth[i] = h[i];
        } else {
            smooth[i] = (h[i-1] + h[i] + h[i+1]) / 3;
        }
    }
    
    std::cout << "Original  Smoothed\n";
    for (size_t i = 0; i < h.size(); i++) {
        printf("%6.1f %9.1f\n", h[i], smooth[i]);
    }
    
    return 0;
}