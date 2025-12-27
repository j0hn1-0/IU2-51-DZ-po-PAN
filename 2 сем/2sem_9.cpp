#include <iostream>
#include <cmath>
#include <limits>

struct AircraftSpecs {
    double mass;           // кг
    double wingArea;       // м²
    double thrust;         // Н
    double liftCoefficient;
    double dragCoefficient;
};

namespace FlightConstants {
    const double AIR_DENSITY = 1.225;  // кг/м³
    const double SPEED = 250.0;        // м/с
    const double GRAVITY = 9.81;       // м/с²
}

double calculateDragForce(double airDensity, double speed, 
                          double wingArea, double dragCoefficient) {
    double dynamicPressure = 0.5 * airDensity * speed * speed;
    return dynamicPressure * wingArea * dragCoefficient;
}

double calculateAcceleration(double thrust, double dragForce, double mass) {
    return (thrust - dragForce) / mass;
}

AircraftSpecs inputAircraftData(int aircraftNumber) {
    AircraftSpecs specs;
    
    std::cout << "\n=== Данные самолета #" << aircraftNumber << " ===\n";
    
    std::cout << "Масса летательного аппарата (кг): ";
    std::cin >> specs.mass;
    
    std::cout << "Площадь несущей поверхности (м²): ";
    std::cin >> specs.wingArea;
    
    std::cout << "Тяга силовой установки (Н): ";
    std::cin >> specs.thrust;
    
    std::cout << "Коэффициент подъемной силы C_L: ";
    std::cin >> specs.liftCoefficient;
    
    std::cout << "Коэффициент сопротивления C_D: ";
    std::cin >> specs.dragCoefficient;
    
    return specs;
}

int main() {
    int numberOfAircraft;
    
    std::cout << "Введите количество воздушных судов для анализа: ";
    std::cin >> numberOfAircraft;
    
    if (numberOfAircraft <= 0) {
        std::cout << "Количество самолетов должно быть положительным!\n";
        return 1;
    }
    
    double maxAcceleration = -std::numeric_limits<double>::infinity();
    int bestPerformingAircraft = -1;
    AircraftSpecs bestAircraftSpecs;
    
    std::cout << "\n" << std::string(50, '=') << "\n";
    
    for (int i = 0; i < numberOfAircraft; ++i) {
        AircraftSpecs currentSpecs = inputAircraftData(i + 1);
        
        double dragForce = calculateDragForce(FlightConstants::AIR_DENSITY,
                                              FlightConstants::SPEED,
                                              currentSpecs.wingArea,
                                              currentSpecs.dragCoefficient);
        
        double acceleration = calculateAcceleration(currentSpecs.thrust,
                                                   dragForce,
                                                   currentSpecs.mass);
        
        std::cout << "→ Продольное ускорение: " << acceleration << " м/с²\n";
        
        if (acceleration > maxAcceleration) {
            maxAcceleration = acceleration;
            bestPerformingAircraft = i + 1;
            bestAircraftSpecs = currentSpecs;
        }
    }
    
    std::cout << "\n" << std::string(50, '=') << "\n";
    std::cout << "РЕЗУЛЬТАТЫ АНАЛИЗА:\n";
    
    if (bestPerformingAircraft != -1) {
        std::cout << "Самолет #" << bestPerformingAircraft 
                  << " демонстрирует максимальное ускорение: " 
                  << maxAcceleration << " м/с²\n";
        
        std::cout << "\nХарактеристики лучшего самолета:\n";
        std::cout << "- Масса: " << bestAircraftSpecs.mass << " кг\n";
        std::cout << "- Площадь крыла: " << bestAircraftSpecs.wingArea << " м²\n";
        std::cout << "- Тяга двигателя: " << bestAircraftSpecs.thrust << " Н\n";
        std::cout << "- C_L: " << bestAircraftSpecs.liftCoefficient << "\n";
        std::cout << "- C_D: " << bestAircraftSpecs.dragCoefficient << "\n";
    }
    
    return 0;
}