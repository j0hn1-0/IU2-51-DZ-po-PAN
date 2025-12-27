#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <cstdio>

class Motion {
    struct Point { double t, x, v, a; };
    std::vector<Point> data;
    
public:
    bool loadCSV(const std::string& file) {
        std::ifstream in(file);
        if (!in) return false;
        
        std::string header;
        std::getline(in, header);
        
        double t, x;
        char c;
        while (in >> t >> c >> x) {
            data.push_back({t, x, 0, 0});
        }
        
        return !data.empty();
    }
    
    void analyze() {
        // Скорость
        for (size_t i = 0; i < data.size() - 1; i++) {
            double dt = data[i+1].t - data[i].t;
            data[i].v = (dt > 0) ? (data[i+1].x - data[i].x) / dt : 0;
        }
        if (!data.empty()) data.back().v = data[data.size()-2].v;
        
        // Ускорение
        for (size_t i = 0; i < data.size() - 1; i++) {
            double dt = data[i+1].t - data[i].t;
            data[i].a = (dt > 0) ? (data[i+1].v - data[i].v) / dt : 0;
        }
        if (!data.empty()) data.back().a = data[data.size()-2].a;
    }
    
    void save(const std::string& file) {
        std::ofstream out(file);
        out << "t,x,v,a\n";
        for (const auto& p : data) {
            out << p.t << "," << p.x << "," << p.v << "," << p.a << "\n";
        }
    }
    
    void show() {
        std::cout << "Точек: " << data.size() << "\n";
        if (data.size() > 1) {
            std::cout << "Время: " << data.front().t << " - " << data.back().t << "\n";
            std::cout << "Перемещение: " << data.back().x - data.front().x << "\n";
        }
    }
    
    void plot() {
        FILE* gp = popen("gnuplot -persist", "w");
        if (!gp) return;
        
        fprintf(gp, "set multiplot\n");
        fprintf(gp, "plot 'motion_results.csv' u 1:3 w l t 'v(t)'\n");
        fprintf(gp, "plot 'motion_results.csv' u 1:4 w l t 'a(t)'\n");
        pclose(gp);
    }
};

int main() {
    Motion motion;
    
    if (motion.loadCSV("motion.csv")) {
        motion.analyze();
        motion.show();
        motion.save("motion_results.csv");
        motion.plot();
    } else {
        std::cout << "Файл не найден\n";
    }
    
    return 0;
}
}