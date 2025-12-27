#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<double> data = {0.1, 0.0, 2.3, 0.0, 4.5, 0.0, 6.7};
    
    int zeros = std::count(data.begin(), data.end(), 0.0);
    
    std::cout << "Zero readings: " << zeros << "\n";
    
    return 0;
}