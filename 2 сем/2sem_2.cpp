#include <iostream>

namespace Aerodynamics {
    struct FlightParameters {
        double airDensity;    // кг/м³
        double velocity;      // м/с
        double referenceArea; // м²
        double dragCoefficient;
    };
    
    double computeDragForce(const FlightParameters& params) {
        const double dynamicPressure = 0.5 * params.airDensity * 
                                       params.velocity * params.velocity;
        return dynamicPressure * params.referenceArea * params.dragCoefficient;
    }
}

int main() {
    using std::cout;
    using std::cin;
    
    Aerodynamics::FlightParameters params;
    
    cout << "Плотность воздушной среды (кг/м³): ";
    cin >> params.airDensity;
    
    cout << "Скорость движения (м/с): ";
    cin >> params.velocity;
    
    cout << "Характерная площадь (м²): ";
    cin >> params.referenceArea;
    
    cout << "Коэффициент аэродинамического сопротивления C_D: ";
    cin >> params.dragCoefficient;
    
    double dragForce = Aerodynamics::computeDragForce(params);
    
    cout << "\nСила лобового сопротивления D = " 
         << dragForce << " Н" << std::endl;
    
    return 0;
}