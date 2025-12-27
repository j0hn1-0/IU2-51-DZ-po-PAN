#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdio>

using DataPoint = std::pair<double, double>;

class AltitudeFilter {
    std::vector<DataPoint> allData;
    std::vector<DataPoint> filteredData;
    
public:
    bool load(const std::string& filename) {
        std::ifstream in(filename);
        if (!in) return false;
        
        std::string header;
        std::getline(in, header);
        
        double t, h;
        char c;
        while (in >> t >> c >> h) {
            allData.emplace_back(t, h);
        }
        
        return !allData.empty();
    }
    
    void filter(double minH, double maxH) {
        std::copy_if(allData.begin(), allData.end(),
                    std::back_inserter(filteredData),
                    [minH, maxH](const DataPoint& p) {
                        return p.second > minH && p.second < maxH;
                    });
        
        std::cout << "Отфильтровано: " << filteredData.size() 
                  << " из " << allData.size() << " точек\n";
    }
    
    void save(const std::string& filename) {
        std::ofstream out(filename);
        out << "t,H\n";
        for (const auto& [t, h] : filteredData) {
            out << t << "," << h << "\n";
        }
    }
    
    void plot() {
        FILE* gp = popen("gnuplot -persist", "w");
        if (!gp) {
            std::cout << "Установите gnuplot для графиков\n";
            return;
        }
        
        fprintf(gp, "set grid\n");
        fprintf(gp, "set title 'Фильтрация по высоте'\n");
        fprintf(gp, "plot 'altitude.csv' u 1:2 w p pt 6 t 'Все данные', ");
        fprintf(gp, "'filtered.csv' u 1:2 w l lw 2 t '900<H<1100'\n");
        pclose(gp);
    }
};

int main() {
    AltitudeFilter filter;
    
    if (filter.load("altitude.csv")) {
        filter.filter(900, 1100);
        filter.save("filtered.csv");
        filter.plot();
    } else {
        std::cout << "Ошибка загрузки файла\n";
    }
    
    return 0;
}