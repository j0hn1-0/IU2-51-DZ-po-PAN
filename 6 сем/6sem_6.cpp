#include <fstream>
#include <vector>
#include <string>

class DataFilter {
    std::vector<std::vector<std::string>> table;
    
public:
    bool loadCSV(const std::string& file) {
        std::ifstream in(file);
        if (!in) return false;
        
        std::string line;
        while (std::getline(in, line)) {
            std::vector<std::string> row;
            size_t start = 0, end;
            
            while ((end = line.find(',', start)) != std::string::npos) {
                row.push_back(line.substr(start, end - start));
                start = end + 1;
            }
            row.push_back(line.substr(start));
            table.push_back(row);
        }
        return !table.empty();
    }
    
    void filter() {
        if (table.empty()) return;
        
        std::vector<std::vector<std::string>> result;
        result.push_back(table[0]); // header
        
        for (size_t i = 1; i < table.size(); i++) {
            double h = std::stod(table[i][1]);  // altitude
            double v = std::stod(table[i][2]);  // speed
            
            if (h >= 0 && h <= 20000 && v >= 0 && v <= 500) {
                result.push_back(table[i]);
            }
        }
        table = result;
    }
    
    bool saveCSV(const std::string& file) {
        std::ofstream out(file);
        for (auto& row : table) {
            for (size_t i = 0; i < row.size(); i++) {
                out << row[i];
                if (i < row.size() - 1) out << ",";
            }
            out << "\n";
        }
        return true;
    }
    
    int filteredCount() {
        return table.size() - (table.empty() ? 0 : 1);
    }
};