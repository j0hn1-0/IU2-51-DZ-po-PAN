#include <iostream>
#include <cmath>
#include <limits>

struct Aircraft {
    double mass;        // масса, кг
    double wingArea;    // площадь крыла, м²
    double thrust;      // тяга, Н
    double liftCoeff;   // коэффициент подъемной силы
    double dragCoeff;   // коэффициент сопротивления
};

namespace Constants {
    const double AIR_DENSITY = 1.225;    // кг/м³
    const double GRAVITY = 9.81;         // м/с²
    const double SPEED = 250.0;          // м/с
    const double TARGET_ALTITUDE = 1000.0; // м
    const int NUM_AIRCRAFT = 3;
}

double calculateLiftForce(const Aircraft& plane) {
    double dynamicPressure = 0.5 * Constants::AIR_DENSITY * 
                            Constants::SPEED * Constants::SPEED;
    return dynamicPressure * plane.wingArea * plane.liftCoeff;
}

double calculateDragForce(const Aircraft& plane) {
    double dynamicPressure = 0.5 * Constants::AIR_DENSITY * 
                            Constants::SPEED * Constants::SPEED;
    return dynamicPressure * plane.wingArea * plane.dragCoeff;
}

double calculateVerticalAcceleration(const Aircraft& plane, double liftForce) {
    return (liftForce - plane.mass * Constants::GRAVITY) / plane.mass;
}

double calculateClimbTime(double verticalAcceleration) {
    return std::sqrt(2.0 * Constants::TARGET_ALTITUDE / verticalAcceleration);
}

int main() {
    Aircraft fleet[Constants::NUM_AIRCRAFT] = {
        {10000, 50, 30000, 0.3, 0.02},
        {12000, 60, 35000, 0.35, 0.025},
        {9000, 45, 28000, 0.32, 0.018}
    };
    
    double minClimbTime = std::numeric_limits<double>::infinity();
    int fastestAircraftIndex = -1;
    
    std::cout << "=== Сравнение времени набора высоты для разных самолетов ===\n";
    
    for (int i = 0; i < Constants::NUM_AIRCRAFT; ++i) {
        double lift = calculateLiftForce(fleet[i]);
        double verticalAccel = calculateVerticalAcceleration(fleet[i], lift);
        
        if (verticalAccel <= 0) {
            std::cout << "Самолет #" << (i + 1) 
                      << " не способен к набору высоты.\n";
            continue;
        }
        
        double climbTime = calculateClimbTime(verticalAccel);
        
        std::cout << "Самолет #" << (i + 1) 
                  << ": время набора " << Constants::TARGET_ALTITUDE 
                  << " м = " << climbTime << " с\n";
        
        if (climbTime < minClimbTime) {
            minClimbTime = climbTime;
            fastestAircraftIndex = i;
        }
    }
    
    if (fastestAircraftIndex != -1) {
        std::cout << "\nСамолет #" << (fastestAircraftIndex + 1)
                  << " демонстрирует наилучшее время набора высоты: "
                  << minClimbTime << " с\n";
    } else {
        std::cout << "\nНи один из самолетов не способен набирать высоту.\n";
    }
    
    return 0;
}