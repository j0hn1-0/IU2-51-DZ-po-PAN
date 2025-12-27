#include <vector>
#include <string>

struct FlightPoint {
    double t, v, h, d, f;
};

class FlightLogger {
    std::vector<FlightPoint> data;
    
public:
    void add(double time, double vel, double alt, double dist, double fuel) {
        data.push_back({time, vel, alt, dist, fuel});
    }
    
    bool saveCSV(const std::string& file) {
        std::ofstream out(file);
        if (!out) return false;
        
        out << "t,v,h,d,f\n";
        for (auto& p : data) {
            out << p.t << "," << p.v << "," << p.h << "," 
                << p.d << "," << p.f << "\n";
        }
        return true;
    }
    
    void makePlot() {
        std::ofstream script("plot.gnu");
        script << "plot 'data.csv' u 1:3 w l t 'Altitude'\n";
    }
    
    void makeReport(const std::string& file) {
        std::ofstream out(file);
        if (data.empty()) return;
        
        double totalT = data.back().t;
        double totalF = data.back().f;
        double avgV = 0;
        
        for (auto& p : data) avgV += p.v;
        avgV /= data.size();
        
        out << "Time: " << totalT << "s\n";
        out << "Fuel: " << totalF << "kg\n";
        out << "Avg V: " << avgV << "m/s\n";
    }
};