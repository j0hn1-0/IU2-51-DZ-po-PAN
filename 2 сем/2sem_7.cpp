#include <iostream>

enum FlightMode {
    CLIMB,
    LEVEL_FLIGHT,
    DESCENT,
    INVALID
};

FlightMode determineFlightMode(double acceleration) {
    if (acceleration > 0.5) {
        return CLIMB;
    } else if (acceleration >= 0.0) {
        return LEVEL_FLIGHT;
    } else if (acceleration < 0.0) {
        return DESCENT;
    } else {
        return INVALID; // Для обработки NaN
    }
}

const char* getModeDescription(FlightMode mode) {
    switch (mode) {
        case CLIMB:         return "набор высоты";
        case LEVEL_FLIGHT:  return "горизонтальный полет";
        case DESCENT:       return "снижение";
        default:            return "неопределенный режим";
    }
}

int main() {
    double verticalAcceleration;
    
    std::cout << "Введите вертикальное ускорение воздушного судна (м/с²): ";
    std::cin >> verticalAcceleration;
    
    FlightMode currentMode = determineFlightMode(verticalAcceleration);
    
    std::cout << "Текущий режим полета: " 
              << getModeDescription(currentMode) << std::endl;
    
    return 0;
}