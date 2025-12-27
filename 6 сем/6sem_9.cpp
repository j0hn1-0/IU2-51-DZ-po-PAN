#include <map>
#include <vector>
#include <string>

class Plane {
    std::map<std::string, double> specs;
    
public:
    bool load(const std::string& file) {
        std::ifstream in(file);
        if (!in) return false;
        
        std::string line;
        while (std::getline(in, line)) {
            size_t pos = line.find('=');
            if (pos != std::string::npos) {
                std::string key = line.substr(0, pos);
                double val = std::stod(line.substr(pos+1));
                specs[key] = val;
            }
        }
        return true;
    }
    
    double get(const std::string& key) {
        return specs.count(key) ? specs[key] : 0.0;
    }
};

class Atmosphere {
    struct Layer { double alt, dens, press; };
    std::vector<Layer> layers;
    
public:
    bool load(const std::string& file) {
        std::ifstream in(file);
        if (!in) return false;
        
        std::string header;
        std::getline(in, header);
        
        Layer l;
        char c;
        while (in >> l.alt >> c >> l.dens >> c >> l.press) {
            layers.push_back(l);
        }
        return true;
    }
    
    double density(double alt) {
        for (auto& l : layers) {
            if (l.alt >= alt) return l.dens;
        }
        return 1.225;
    }
};