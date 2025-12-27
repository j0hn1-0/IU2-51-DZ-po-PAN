#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <cstdio>

class MotionTracker {
    struct Point { double t, x, y, v; };
    std::vector<Point> path;
    
public:
    bool load(const std::string& filename) {
        std::ifstream in(filename);
        if (!in) return false;
        
        std::string header;
        std::getline(in, header);
        
        double t, x, y;
        char c;
        while (in >> t >> c >> x >> c >> y) {
            path.push_back({t, x, y, 0.0});
        }
        
        return !path.empty();
    }
    
    void calculateSpeed() {
        if (path.size() < 2) return;
        
        // Вычисление скорости для внутренних точек
        for (size_t i = 0; i < path.size() - 1; i++) {
            double dt = path[i+1].t - path[i].t;
            double dx = path[i+1].x - path[i].x;
            double dy = path[i+1].y - path[i].y;
            
            path[i].v = (dt > 0) ? std::hypot(dx, dy) / dt : 0;
        }
        
        // Последняя точка
        path.back().v = path[path.size()-2].v;
    }
    
    void saveResults() {
        std::ofstream out("speed_profile.csv");
        out << "t,x,y,v\n";
        for (const auto& p : path) {
            out << p.t << "," << p.x << "," << p.y << "," << p.v << "\n";
        }
        
        std::cout << "Результаты в speed_profile.csv\n";
    }
    
    void plot() {
        FILE* gp = popen("gnuplot -persist", "w");
        if (!gp) {
            std::cout << "Установите gnuplot\n";
            return;
        }
        
        fprintf(gp, "set multiplot\n");
        fprintf(gp, "set size 0.5,0.5\n");
        
        fprintf(gp, "set origin 0,0.5\n");
        fprintf(gp, "set title 'Траектория'\n");
        fprintf(gp, "plot 'speed_profile.csv' u 2:3 w l\n");
        
        fprintf(gp, "set origin 0.5,0.5\n");
        fprintf(gp, "set title 'Скорость'\n");
        fprintf(gp, "plot 'speed_profile.csv' u 1:4 w l\n");
        
        fprintf(gp, "unset multiplot\n");
        pclose(gp);
    }
};

int main() {
    MotionTracker tracker;
    
    if (tracker.load("navigation.csv")) {
        tracker.calculateSpeed();
        tracker.saveResults();
        tracker.plot();
    } else {
        std::cout << "Ошибка загрузки\n";
    }
    
    return 0;
}
}