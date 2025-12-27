#include <iostream>

double calculateLiftForce(double density, double velocity, 
                         double wingArea, double liftCoefficient) {
    return 0.5 * density * velocity * velocity * wingArea * liftCoefficient;
}

int main() {
    double airDensity, velocity, wingArea, liftCoefficient;
    
    std::cout << "Введите плотность воздуха (кг/м³): ";
    std::cin >> airDensity;
    
    std::cout << "Введите скорость (м/с): ";
    std::cin >> velocity;
    
    std::cout << "Введите площадь крыла (м²): ";
    std::cin >> wingArea;
    
    std::cout << "Введите коэффициент подъемной силы C_L: ";
    std::cin >> liftCoefficient;
    
    double liftForce = calculateLiftForce(airDensity, velocity, 
                                         wingArea, liftCoefficient);
    
    std::cout << "Подъемная сила L = " << liftForce << " Н" << std::endl;
    
    return 0;
}
