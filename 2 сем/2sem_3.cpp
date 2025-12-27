#include <iostream>

const double GRAVITY = 9.81;

struct AircraftForces {
    double mass;        // масса, кг
    double lift;        // подъемная сила, Н
    double drag;        // сопротивление, Н
    double thrust;      // тяга, Н
};

void calculateAccelerations(const AircraftForces& forces, 
                           double& horizontalAcc, double& verticalAcc) {
    horizontalAcc = (forces.thrust - forces.drag) / forces.mass;
    verticalAcc = (forces.lift - forces.mass * GRAVITY) / forces.mass;
}

int main() {
    AircraftForces forces;
    
    std::cout << "=== Расчет ускорений летательного аппарата ===\n";
    
    std::cout << "Масса самолета, кг: ";
    std::cin >> forces.mass;
    
    std::cout << "Подъемная сила L, Н: ";
    std::cin >> forces.lift;
    
    std::cout << "Аэродинамическое сопротивление D, Н: ";
    std::cin >> forces.drag;
    
    std::cout << "Тяга силовой установки T, Н: ";
    std::cin >> forces.thrust;
    
    double ax, ay;
    calculateAccelerations(forces, ax, ay);
    
    std::cout << "\nРезультаты расчета:\n";
    std::cout << "Продольное ускорение (по вектору скорости): " 
              << ax << " м/с²\n";
    std::cout << "Нормальное ускорение (по вертикали): " 
              << ay << " м/с²\n";
    
    return 0;
}