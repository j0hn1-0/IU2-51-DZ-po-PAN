#include <iostream>
#include <vector>
#include <cmath>

class DronePath {
    std::vector<std::pair<double, double>> points;
    double dist;
    
public:
    DronePath() : dist(0) {
        points.push_back({0,0});
    }
    
    void add(double x, double y) {
        auto& last = points.back();
        double dx = x - last.first;
        double dy = y - last.second;
        dist += sqrt(dx*dx + dy*dy);
        points.push_back({x,y});
    }
    
    double total() const { return dist; }
    
    void print() {
        for (auto& p : points) {
            std::cout << "(" << p.first << "," << p.second << ")\n";
        }
    }
};

int main() {
    DronePath d;
    d.add(0,0);
    d.add(3,4);
    d.add(6,8);
    
    d.print();
    std::cout << "Distance: " << d.total() << "\n";
    
    return 0;
}