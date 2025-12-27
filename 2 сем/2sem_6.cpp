#include <iostream>
#include <iomanip>

struct FlightCondition {
    double velocity;    // скорость, м/с
    double density;     // плотность воздуха, кг/м³
};

double computeLiftForce(double airDensity, double speed, 
                        double wingArea, double liftCoefficient) {
    const double factor = 0.5;
    return factor * airDensity * speed * speed * wingArea * liftCoefficient;
}

void printTableHeader() {
    std::cout << std::setw(8) << "№" 
              << std::setw(12) << "Скорость" 
              << std::setw(14) << "Плотность"
              << std::setw(18) << "Подъемная сила" << std::endl;
    std::cout << std::setw(8) << "п/п" 
              << std::setw(12) << "(м/с)" 
              << std::setw(14) << "(кг/м³)"
              << std::setw(18) << "(Н)" << std::endl;
    std::cout << std::string(52, '-') << std::endl;
}

int main() {
    const int NUM_CONDITIONS = 5;
    const double WING_AREA = 50.0;
    const double LIFT_COEFFICIENT = 0.3;
    
    FlightConditions conditions[NUM_CONDITIONS] = {
        {100.0, 1.225},
        {110.0, 1.200},
        {120.0, 1.180},
        {130.0, 1.150},
        {140.0, 1.120}
    };
    
    std::cout << "Таблица расчета аэродинамической подъемной силы\n";
    std::cout << "Площадь крыла: " << WING_AREA << " м², "
              << "C_L: " << LIFT_COEFFICIENT << "\n\n";
    
    printTableHeader();
    
    for (int i = 0; i < NUM_CONDITIONS; ++i) {
        double liftForce = computeLiftForce(conditions[i].density,
                                            conditions[i].velocity,
                                            WING_AREA,
                                            LIFT_COEFFICIENT);
        
        std::cout << std::setw(8) << i + 1
                  << std::setw(12) << std::fixed << std::setprecision(1) << conditions[i].velocity
                  << std::setw(14) << std::fixed << std::setprecision(3) << conditions[i].density
                  << std::setw(18) << std::fixed << std::setprecision(2) << liftForce
                  << std::endl;
    }
    
    return 0;
}