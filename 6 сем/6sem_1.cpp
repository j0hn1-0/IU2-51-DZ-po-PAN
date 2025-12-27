#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <string>

struct TrajectoryPoint {
    double t, x, y, z, v;
};

class PathRecorder {
    std::vector<TrajectoryPoint> path;
    std::string file;
    
public:
    PathRecorder(const std::string& filename = "path.csv") : file(filename) {}
    
    void add(double time, double x, double y, double z, double speed) {
        path.push_back({time, x, y, z, speed});
    }
    
    bool save() {
        std::ofstream out(file);
        if (!out) return false;
        
        out << "t,x,y,z,v\n";
        for (const auto& p : path) {
            out << p.t << "," << p.x << "," << p.y << "," << p.z << "," << p.v << "\n";
        }
        return true;
    }
    
    bool load() {
        std::ifstream in(file);
        if (!in) return false;
        
        path.clear();
        std::string header;
        std::getline(in, header);
        
        double t, x, y, z, v;
        char c;
        while (in >> t >> c >> x >> c >> y >> c >> z >> c >> v) {
            path.push_back({t, x, y, z, v});
        }
        return true;
    }
    
    double totalDistance() {
        double sum = 0;
        for (size_t i = 1; i < path.size(); i++) {
            double dx = path[i].x - path[i-1].x;
            double dy = path[i].y - path[i-1].y;
            double dz = path[i].z - path[i-1].z;
            sum += std::sqrt(dx*dx + dy*dy + dz*dz);
        }
        return sum;
    }
    
    double maxSpeed() {
        double max = 0;
        for (const auto& p : path) {
            if (p.v > max) max = p.v;
        }
        return max;
    }
    
    void info() {
        std::cout << "Points: " << path.size() << "\n";
        std::cout << "Distance: " << totalDistance() << "\n";
        std::cout << "Max speed: " << maxSpeed() << "\n";
    }
};

int main() {
    PathRecorder recorder("test.csv");
    
    // Пример использования
    for (int i = 0; i < 10; i++) {
        recorder.add(i*0.5, i*10.0, i*5.0, i*2.0, i*3.0);
    }
    
    recorder.save();
    recorder.info();
    
    return 0;
}