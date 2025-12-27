#include <iostream>
#include <cmath>
#include <limits>

namespace Constants {
    const double AIR_DENSITY = 1.225;    // кг/м³
    const double GRAVITY = 9.81;         // м/с²
}

struct AircraftParameters {
    double mass;           // кг
    double wingArea;       // м²
    double liftCoefficient;
    double dragCoefficient;
    double targetAltitude; // м
    double speed;          // м/с
};

double calculateLiftForce(const AircraftParameters& params) {
    double dynamicPressure = 0.5 * Constants::AIR_DENSITY * 
                            params.speed * params.speed;
    return dynamicPressure * params.wingArea * params.liftCoefficient;
}

double calculateDragForce(const AircraftParameters& params) {
    double dynamicPressure = 0.5 * Constants::AIR_DENSITY * 
                            params.speed * params.speed;
    return dynamicPressure * params.wingArea * params.dragCoefficient;
}

double calculateClimbTime(double liftForce, const AircraftParameters& params) {
    double verticalAcceleration = (liftForce - params.mass * Constants::GRAVITY) / params.mass;
    
    if (verticalAcceleration <= 0) {
        return std::numeric_limits<double>::infinity();
    }
    
    return std::sqrt(2.0 * params.targetAltitude / verticalAcceleration);
}

void findOptimalThrust(double minThrust, double maxThrust, double thrustStep,
                       const AircraftParameters& params) {
    double bestThrust = minThrust;
    double bestTime = std::numeric_limits<double>::infinity();
    int iterationCount = 0;
    
    std::cout << "\nАнализ различных значений тяги:\n";
    std::cout << "================================\n";
    
    for (double thrust = minThrust; thrust <= maxThrust; thrust += thrustStep) {
        double liftForce = calculateLiftForce(params);
        double climbTime = calculateClimbTime(liftForce, params);
        
        std::cout << "Тяга: " << thrust << " Н → ";
        
        if (std::isinf(climbTime)) {
            std::cout << "набор высоты невозможен\n";
        } else {
            std::cout << "время: " << climbTime << " с\n";
            
            if (climbTime < bestTime) {
                bestTime = climbTime;
                bestThrust = thrust;
            }
        }
        
        iterationCount++;
    }
    
    std::cout << "\nРезультаты оптимизации:\n";
    std::cout << "=======================\n";
    
    if (iterationCount == 0) {
        std::cout << "Некорректные диапазоны параметров.\n";
    } else if (std::isinf(bestTime)) {
        std::cout << "В заданном диапазоне тяги набор высоты " 
                  << params.targetAltitude << " м невозможен.\n";
    } else {
        std::cout << "Оптимальное значение тяги: " << bestThrust << " Н\n";
        std::cout << "Минимальное время набора " << params.targetAltitude 
                  << " м: " << bestTime << " секунд\n";
        std::cout << "Проанализировано " << iterationCount 
                  << " значений тяги\n";
    }
}

int main() {
    double minThrust, maxThrust, thrustStep;
    AircraftParameters aircraft;
    
    std::cout << "=== ОПТИМИЗАЦИЯ ТЯГИ ДЛЯ НАБОРА ВЫСОТЫ ===\n\n";
    
    std::cout << "Диапазон тяги двигателя:\n";
    std::cout << "Минимальная тяга (Н): ";
    std::cin >> minThrust;
    
    std::cout << "Максимальная тяга (Н): ";
    std::cin >> maxThrust;
    
    std::cout << "Шаг изменения тяги (Н): ";
    std::cin >> thrustStep;
    
    std::cout << "\nПараметры воздушного судна:\n";
    std::cout << "Масса (кг): ";
    std::cin >> aircraft.mass;
    
    std::cout << "Коэффициент подъемной силы C_L: ";
    std::cin >> aircraft.liftCoefficient;
    
    std::cout << "Коэффициент сопротивления C_D: ";
    std::cin >> aircraft.dragCoefficient;
    
    std::cout << "Площадь крыла (м²): ";
    std::cin >> aircraft.wingArea;
    
    std::cout << "\nУсловия полета:\n";
    std::cout << "Высота набора (м): ";
    std::cin >> aircraft.targetAltitude;
    
    std::cout << "Скорость полета (м/с): ";
    std::cin >> aircraft.speed;
    
    if (minThrust > maxThrust || thrustStep <= 0) {
        std::cout << "Ошибка: некорректные параметры диапазона тяги.\n";
        return 1;
    }
    
    findOptimalThrust(minThrust, maxThrust, thrustStep, aircraft);
    
    return 0;
}