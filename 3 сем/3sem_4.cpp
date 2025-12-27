#include <iostream>
#include <vector>
#include <numeric>

int main() {
    std::vector<double> v = {10, 20, 30, 25, 15};
    
    if (v.empty()) return 0;
    
    double sum = std::accumulate(v.begin(), v.end(), 0.0);
    double avg = sum / v.size();
    
    std::cout << "Avg speed: " << avg << "\n";
    
    return 0;
}