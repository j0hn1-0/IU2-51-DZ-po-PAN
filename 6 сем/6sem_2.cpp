#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

struct MilitaryTarget {
    int id;
    std::string name;
    double x, y, z;
    double priority;    // 1-10
    double range;       // дистанция
};

class TargetTracker {
    std::vector<MilitaryTarget> targets;
    std::string dbFile;
    
public:
    TargetTracker(const std::string& file = "targets.csv") : dbFile(file) {}
    
    void add(int id, const std::string& name, double x, double y, double z, 
             double priority, double range) {
        targets.push_back({id, name, x, y, z, priority, range});
    }
    
    bool remove(int targetId) {
        size_t before = targets.size();
        targets.erase(
            std::remove_if(targets.begin(), targets.end(),
                [targetId](const MilitaryTarget& t) { return t.id == targetId; }),
            targets.end()
        );
        return targets.size() < before;
    }
    
    void save() {
        std::ofstream out(dbFile);
        out << "ID,Name,X,Y,Z,Priority,Range\n";
        for (const auto& t : targets) {
            out << t.id << "," << t.name << "," << t.x << "," 
                << t.y << "," << t.z << "," << t.priority << "," 
                << t.range << "\n";
        }
    }
    
    void load() {
        std::ifstream in(dbFile);
        if (!in) return;
        
        targets.clear();
        std::string header;
        std::getline(in, header);
        
        int id;
        std::string name;
        double x, y, z, p, r;
        char c;
        
        while (in >> id >> c && std::getline(in, name, ',') &&
               in >> x >> c >> y >> c >> z >> c >> p >> c >> r) {
            targets.push_back({id, name, x, y, z, p, r});
        }
    }
    
    std::vector<MilitaryTarget> getImportant(double minPriority) {
        std::vector<MilitaryTarget> result;
        for (const auto& t : targets) {
            if (t.priority >= minPriority) {
                result.push_back(t);
            }
        }
        return result;
    }
    
    void sortByRange() {
        std::sort(targets.begin(), targets.end(),
            [](const MilitaryTarget& a, const MilitaryTarget& b) {
                return a.range < b.range;
            });
    }
    
    void showAll() {
        std::cout << "Цели: " << targets.size() << "\n";
        for (const auto& t : targets) {
            std::cout << t.id << ": " << t.name << " @ " 
                      << t.range << "m\n";
        }
    }
};

int main() {
    TargetTracker tracker;
    tracker.add(1, "Target A", 100, 200, 10, 8.5, 1500);
    tracker.add(2, "Target B", 200, 300, 20, 7.0, 1200);
    tracker.save();
    tracker.showAll();
    
    return 0;
}