#include <iostream>

class Engine {
    double thrust, flow, fuel;
    
public:
    Engine(double t, double f, double fu) : thrust(t), flow(f), fuel(fu) {}
    
    double getThrust() const { return thrust; }
    bool hasFuel() const { return fuel > 0; }
    
    void burn(double dt) {
        if (fuel <= 0) return;
        double used = flow * dt;
        fuel -= (used > fuel) ? fuel : used;
    }
};

class Nav {
    double h, v, m, a;
    
public:
    Nav(double alt, double vel, double mass) : h(alt), v(vel), m(mass), a(0) {}
    
    void update(double thrust, double dt) {
        a = thrust / m - 9.81;
        v += a * dt;
        h += v * dt;
        if (h < 0) h = 0;
    }
    
    void print(double t) const {
        std::cout << "t=" << t << " h=" << h << " v=" << v << "\n";
    }
};

class FlightSys {
    Engine eng;
    Nav nav;
    double time;
    
public:
    FlightSys(const Engine& e, const Nav& n) : eng(e), nav(n), time(0) {}
    
    void run(double dt, double T) {
        while (time < T && eng.hasFuel()) {
            eng.burn(dt);
            nav.update(eng.getThrust(), dt);
            nav.print(time);
            time += dt;
        }
        std::cout << "Done\n";
    }
};

int main() {
    Engine e(15000, 5, 50);
    Nav n(0, 0, 1000);
    FlightSys fs(e, n);
    
    fs.run(1.0, 20.0);
    
    return 0;
}