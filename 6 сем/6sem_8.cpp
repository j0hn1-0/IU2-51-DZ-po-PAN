#include <vector>
#include <numeric>
#include <algorithm>

class FuelMonitor {
    std::vector<double> time, fuel, rpm;
    
public:
    bool load(const std::string& file) {
        std::ifstream in(file);
        if (!in) return false;
        
        std::string header;
        std::getline(in, header);
        
        double t, f, r;
        char c;
        while (in >> t >> c >> f >> c >> r) {
            time.push_back(t);
            fuel.push_back(f);
            rpm.push_back(r);
        }
        return !fuel.empty();
    }
    
    double avgConsumption() {
        if (fuel.empty()) return 0;
        double sum = std::accumulate(fuel.begin(), fuel.end(), 0.0);
        return sum / fuel.size();
    }
    
    void findAnomalies(double threshold = 1.5) {
        double avg = avgConsumption();
        for (size_t i = 0; i < fuel.size(); i++) {
            if (fuel[i] > avg * threshold) {
                std::cout << "Anomaly @ t=" << time[i] 
                          << ": fuel=" << fuel[i] 
                          << " rpm=" << rpm[i] << "\n";
            }
        }
    }
    
    void saveReport(const std::string& file) {
        std::ofstream out(file);
        out << "Avg fuel: " << avgConsumption() << "\n";
        out << "Samples: " << fuel.size() << "\n";
    }
};