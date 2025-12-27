#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

class PointSorter {
    struct Point { 
        int id; 
        double x, y, z; 
        std::string tag; 
        double dist; 
    };
    std::vector<Point> points;
    
public:
    bool load(const std::string& file) {
        std::ifstream in(file);
        if (!in) return false;
        
        Point p;
        char c;
        while (in >> p.id >> c >> p.x >> c >> p.y >> c >> p.z >> c) {
            std::getline(in, p.tag);
            points.push_back(p);
        }
        return !points.empty();
    }
    
    void calcDist(double cx, double cy, double cz) {
        for (auto& p : points) {
            double dx = p.x - cx;
            double dy = p.y - cy;
            double dz = p.z - cz;
            p.dist = std::sqrt(dx*dx + dy*dy + dz*dz);
        }
    }
    
    void sortByDist() {
        std::sort(points.begin(), points.end(),
            [](const Point& a, const Point& b) { 
                return a.dist < b.dist; 
            });
    }
    
    bool save(const std::string& file) {
        std::ofstream out(file);
        for (auto& p : points) {
            out << p.id << "," << p.x << "," << p.y << "," 
                << p.z << "," << p.tag << "," << p.dist << "\n";
        }
        return true;
    }
    
    const Point* nearest() {
        return points.empty() ? nullptr : &points[0];
    }
};