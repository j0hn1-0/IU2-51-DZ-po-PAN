#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

struct Waypoint {
    int id;
    double x, y, z, speed;
    std::string name;
};

class Route {
    std::vector<Waypoint> points;
    size_t current = 0;
    
public:
    void add(int id, double x, double y, double z, double s = 0, std::string n = "") {
        points.push_back({id, x, y, z, s, n});
    }
    
    bool save(const std::string& file = "route.txt") {
        std::ofstream out(file);
        if (!out) return false;
        
        for (const auto& p : points) {
            out << p.id << " " << p.x << " " << p.y << " " 
                << p.z << " " << p.speed << " " << p.name << "\n";
        }
        return true;
    }
    
    bool load(const std::string& file = "route.txt") {
        std::ifstream in(file);
        if (!in) return false;
        
        points.clear();
        Waypoint p;
        while (in >> p.id >> p.x >> p.y >> p.z >> p.speed) {
            std::getline(in, p.name);
            points.push_back(p);
        }
        return !points.empty();
    }
    
    double totalDistance() {
        double sum = 0;
        for (size_t i = 1; i < points.size(); i++) {
            auto& a = points[i-1];
            auto& b = points[i];
            double dx = b.x - a.x;
            double dy = b.y - a.y;
            double dz = b.z - a.z;
            sum += sqrt(dx*dx + dy*dy + dz*dz);
        }
        return sum;
    }
    
    Waypoint* currentPoint() {
        return (current < points.size()) ? &points[current] : nullptr;
    }
    
    bool checkReached(double x, double y, double z, double tol = 10) {
        if (current >= points.size()) return false;
        
        auto& wp = points[current];
        double d = sqrt(pow(x-wp.x,2) + pow(y-wp.y,2) + pow(z-wp.z,2));
        
        if (d < tol) {
            current++;
            return true;
        }
        return false;
    }
    
    void reset() { current = 0; }
    size_t count() const { return points.size(); }
};