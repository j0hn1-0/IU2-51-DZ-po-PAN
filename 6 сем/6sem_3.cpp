#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>

struct SimpleTelemetry {
    double t, h, v, heading, fuel;
};

class CompactTelemetryLogger {
    std::vector<SimpleTelemetry> buffer;
    std::string baseName;
    size_t maxBuffer;
    int fileNum;
    
public:
    CompactTelemetryLogger(size_t maxBuf = 1000) 
        : maxBuffer(maxBuf), fileNum(1) {
        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);
        baseName = "tel_" + std::to_string(time) + "_";
    }
    
    void log(double time, double alt, double speed, 
             double head, double fuel) {
        buffer.push_back({time, alt, speed, head, fuel});
        
        if (buffer.size() >= maxBuffer) {
            saveToFile();
        }
    }
    
    void saveToFile() {
        if (buffer.empty()) return;
        
        std::string filename = baseName + std::to_string(fileNum++) + ".dat";
        std::ofstream out(filename, std::ios::binary);
        
        out.write((char*)buffer.data(), buffer.size() * sizeof(SimpleTelemetry));
        buffer.clear();
        
        std::cout << "Сохранено в " << filename << "\n";
    }
    
    void printStats() {
        if (buffer.empty()) {
            std::cout << "Нет данных\n";
            return;
        }
        
        double avgH = 0, avgV = 0;
        for (const auto& d : buffer) {
            avgH += d.h;
            avgV += d.v;
        }
        
        std::cout << "Записей: " << buffer.size() << "\n";
        std::cout << "Ср. высота: " << avgH/buffer.size() << "\n";
        std::cout << "Ср. скорость: " << avgV/buffer.size() << "\n";
    }
};

int main() {
    CompactTelemetryLogger logger(500);
    
    for (int i = 0; i < 600; i++) {
        logger.log(i*0.1, 1000+i, 200+i*0.1, i%360, 1000-i);
    }
    
    logger.printStats();
    
    return 0;
}