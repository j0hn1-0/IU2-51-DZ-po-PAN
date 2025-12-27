#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<double> x = {30, 10, 20, 10, 30, 40, 20};
    
    std::sort(x.begin(), x.end());
    x.erase(std::unique(x.begin(), x.end()), x.end());
    
    for (auto v : x) std::cout << v << " ";
    
    return 0;
}