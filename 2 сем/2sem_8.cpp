#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <limits>

struct Aircraft {
    double mass;           // кг
    double thrust;         // Н
    double liftCoefficient;
    double dragCoefficient;
    
    // Добавляем ID для идентификации
    int id;
};

struct AircraftPerformance {
    Aircraft plane;
    double climbTime;      // с
};

namespace Constants {
    const double AIR_DENSITY = 1.225;    // кг/м³
    const double WING_AREA = 50.0;       // м²
    const double GRAVITY = 9.81;         // м/с²
    const double SPEED = 250.0;          // м/с
    const double TARGET_ALTITUDE = 1000.0; // м
}

double calculateLiftForce(const Aircraft& plane) {
    double dynamicPressure = 0.5 * Constants::AIR_DENSITY * 
                            Constants::SPEED * Constants::SPEED;
    return dynamicPressure * Constants::WING_AREA * plane.liftCoefficient;
}

double calculateDragForce(const Aircraft& plane) {
    double dynamicPressure = 0.5 * Constants::AIR_DENSITY * 
                            Constants::SPEED * Constants::SPEED;
    return dynamicPressure * Constants::WING_AREA * plane.dragCoefficient;
}

double calculateClimbTime(const Aircraft& plane) {
    double lift = calculateLiftForce(plane);
    double verticalAcceleration = (lift - plane.mass * Constants::GRAVITY) / plane.mass;
    
    if (verticalAcceleration <= 0) {
        return std::numeric_limits<double>::infinity();
    }
    
    return std::sqrt(2.0 * Constants::TARGET_ALTITUDE / verticalAcceleration);
}

bool compareByClimbTime(const AircraftPerformance& a, const AircraftPerformance& b) {
    return a.climbTime < b.climbTime;
}

int main() {
    std::vector<Aircraft> fleet = {
        {10000, 30000, 0.3, 0.02, 1},
        {12000, 35000, 0.35, 0.025, 2},
        {9000, 28000, 0.32, 0.018, 3},
        {11000, 32000, 0.33, 0.022, 4}
    };
    
    std::vector<AircraftPerformance> performances;
    
    std::cout << "Расчет времени набора высоты 1000 м:\n";
    std::cout << "====================================\n";
    
    for (const auto& plane : fleet) {
        double time = calculateClimbTime(plane);
        
        AircraftPerformance perf = {plane, time};
        performances.push_back(perf);
        
        std::cout << "Самолет #" << plane.id << ": ";
        if (std::isinf(time)) {
            std::cout << "не набирает высоту";
        } else {
            std::cout << time << " с";
        }
        std::cout << std::endl;
    }
    
    // Сортировка по времени набора высоты
    std::sort(performances.begin(), performances.end(), compareByClimbTime);
    
    std::cout << "\nРейтинг самолетов (от быстрого к медленному):\n";
    std::cout << "============================================\n";
    
    int rank = 1;
    for (const auto& perf : performances) {
        std::cout << rank++ << ". Самолет #" << perf.plane.id;
        if (std::isinf(perf.climbTime)) {
            std::cout << " - НЕ СПОСОБЕН К НАБОРУ ВЫСОТЫ";
        } else {
            std::cout << " - " << perf.climbTime << " с";
        }
        std::cout << std::endl;
    }
    
    return 0;
}
}