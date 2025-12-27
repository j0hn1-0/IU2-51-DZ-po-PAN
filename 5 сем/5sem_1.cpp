#include <iostream>
#include <cmath>

class Engine {
    double thrust, fuelRate, fuel;
public:
    Engine(double t, double fr, double f) 
        : thrust(t), fuelRate(fr), fuel(f) {}
    
    double getThrust() const { return (fuel > 0) ? thrust : 0; }
    double getFuel() const { return fuel; }
    
    void update(double dt) {
        if (fuel > 0) {
            fuel -= fuelRate * dt;
            if (fuel < 0) fuel = 0;
        }
    }
};

class Airplane {
    Engine engine;
    double mass, alt, vel, time;
    const double g = 9.81, cd = 0.03, area = 50;
    
    double drag() const {
        return 0.5 * 1.225 * vel * vel * cd * area;
    }
    
public:
    Airplane(double m, double h0, const Engine& e)
        : mass(m), alt(h0), vel(0), time(0), engine(e) {}
    
    void simulate(double dt, double Tmax) {
        std::cout << "Время\tВысота\tСкорость\tТопливо\n";
        
        while (time < Tmax && engine.getFuel() > 0) {
            double F = engine.getThrust();
            double D = drag();
            double a = (F - D) / mass - g;
            
            vel += a * dt;
            alt += vel * dt;
            engine.update(dt);
            time += dt;
            
            if (time < 10 || fmod(time, 10) < dt) {
                printf("%5.1f\t%6.1f\t%7.1f\t%7.1f\n", 
                       time, alt, vel, engine.getFuel());
            }
            
            if (alt < 0) {
                std::cout << "Посадка в " << time << " с\n";
                break;
            }
        }
    }
};

int main() {
    Engine jet(50000, 2.5, 1000);
    Airplane plane(20000, 0, jet);
    
    plane.simulate(0.5, 200);
    
    return 0;
}