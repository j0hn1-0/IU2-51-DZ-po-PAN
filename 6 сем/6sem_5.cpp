#include <map>
#include <vector>
#include <string>

class Validator {
    struct Range { double min, max; };
    std::map<std::string, Range> rules;
    std::vector<std::string> errors;
    
public:
    void addRule(const std::string& field, double min, double max) {
        rules[field] = {min, max};
    }
    
    bool check(const std::string& field, double value) {
        if (!rules.count(field)) return true;
        
        auto& r = rules[field];
        if (value < r.min || value > r.max) {
            errors.push_back(field + " = " + std::to_string(value) + 
                           " вне [" + std::to_string(r.min) + 
                           "," + std::to_string(r.max) + "]");
            return false;
        }
        return true;
    }
    
    bool checkXYZ(double x, double y, double z) {
        return check("x", x) && check("y", y) && check("z", z);
    }
    
    bool checkSpeed(double v) { return check("speed", v); }
    bool checkAccel(double a) { return check("accel", a); }
    
    void saveReport(const std::string& file = "valid.txt") {
        std::ofstream out(file);
        out << "Errors: " << errors.size() << "\n";
        for (auto& e : errors) out << e << "\n";
    }
    
    void clear() { errors.clear(); }
    int errorCount() const { return errors.size(); }
};
};