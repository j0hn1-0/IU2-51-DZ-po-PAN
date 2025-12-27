#include <iostream>

class Autopilot {
    double course, alt;
    
public:
    Autopilot(double c, double a) : course(c), alt(a) {}
    
    void setCourse(double delta) { course += delta; }
    void setAlt(double delta) { alt += delta; }
    
    void print() const {
        std::cout << "Course=" << course 
                  << " Alt=" << alt << "\n";
    }
};

int main() {
    Autopilot ap(90, 1000);
    ap.setCourse(10);
    ap.setAlt(500);
    ap.print();
    
    return 0;
}