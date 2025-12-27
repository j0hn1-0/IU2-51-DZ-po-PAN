#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<double> temp = {50, -150, 100, 250, 30, 300, -50, 80};
    
    temp.erase(std::remove_if(temp.begin(), temp.end(),
        [](double t) { return t < -100 || t > 200; }), temp.end());
    
    for (auto t : temp) std::cout << t << " ";
    
    return 0;
}