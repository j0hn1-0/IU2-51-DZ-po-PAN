#include <iostream>
#include <cmath>

bool isValidInput(double height, double acceleration) {
    return height > 0 && acceleration > 0;
}

double calculateClimbTime(double altitude, double verticalAcceleration) {
    return std::sqrt(2.0 * altitude / verticalAcceleration);
}

int main() {
    double climbHeight, verticalAccel;
    
    std::cout << "Высота набора (метры): ";
    std::cin >> climbHeight;
    
    std::cout << "Вертикальное ускорение (м/с²): ";
    std::cin >> verticalAccel;
    
    if (!isValidInput(climbHeight, verticalAccel)) {
        std::cerr << "Некорректные данные. Требуются положительные значения." 
                  << std::endl;
        return 1;
    }
    
    double timeToClimb = calculateClimbTime(climbHeight, verticalAccel);
    
    std::cout << "\nНеобходимое время для набора высоты: " 
              << timeToClimb << " секунд" << std::endl;
    
    return 0;
}