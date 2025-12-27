#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>

class Trajectory {
private:
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <stdexcept>

class DataPoint {
public:
    double time;
    double position;
    double velocity;
    
    DataPoint(double t, double x, double v = 0.0) 
        : time(t), position(x), velocity(v) {}
};

class TrajectoryAnalyzer {
private:
    std::vector<DataPoint> dataPoints;
    
public:
    bool loadTrajectoryData(const std::string& filename) {
        std::ifstream inputFile(filename);
        
        if (!inputFile.is_open()) {
            std::cerr << "Ошибка: невозможно открыть файл '" << filename << "'\n";
            return false;
        }
        
        std::string header;
        if (!std::getline(inputFile, header)) {
            std::cerr << "Ошибка: файл пуст или поврежден\n";
            return false;
        }
        
        double timeValue, positionValue;
        char separator;
        
        while (inputFile >> timeValue >> separator >> positionValue) {
            if (separator != ',') {
                std::cerr << "Предупреждение: нестандартный разделитель в строке\n";
            }
            dataPoints.emplace_back(timeValue, positionValue);
        }
        
        inputFile.close();
        
        if (dataPoints.empty()) {
            std::cerr << "Ошибка: файл не содержит данных\n";
            return false;
        }
        
        std::cout << "Загружено " << dataPoints.size() << " точек данных\n";
        return true;
    }
    
    void calculateVelocities() {
        if (dataPoints.size() < 2) {
            std::cerr << "Недостаточно данных для вычисления скорости\n";
            return;
        }
        
        // Вычисление скорости методом конечных разностей
        for (size_t i = 0; i < dataPoints.size() - 1; ++i) {
            double deltaTime = dataPoints[i + 1].time - dataPoints[i].time;
            double deltaPosition = dataPoints[i + 1].position - dataPoints[i].position;
            
            if (deltaTime > 0) {
                dataPoints[i].velocity = deltaPosition / deltaTime;
            } else {
                dataPoints[i].velocity = 0.0;
            }
        }
        
        // Экстраполяция последнего значения скорости
        if (dataPoints.size() > 1) {
            dataPoints.back().velocity = dataPoints[dataPoints.size() - 2].velocity;
        }
    }
    
    bool saveResultsToFile(const std::string& filename) {
        std::ofstream outputFile(filename);
        
        if (!outputFile.is_open()) {
            std::cerr << "Ошибка создания файла результатов\n";
            return false;
        }
        
        // Запись заголовка
        outputFile << "Time(s),Position(m),Velocity(m/s)\n";
        
        // Запись данных
        for (const auto& point : dataPoints) {
            outputFile << point.time << "," 
                      << point.position << "," 
                      << point.velocity << "\n";
        }
        
        outputFile.close();
        std::cout << "Результаты сохранены в '" << filename << "'\n";
        return true;
    }
    
    void displayStatistics() const {
        if (dataPoints.empty()) return;
        
        std::cout << "\nСтатистика траектории:\n";
        std::cout << "Временной диапазон: " << dataPoints.front().time 
                  << " - " << dataPoints.back().time << " с\n";
        
        double minVel = dataPoints[0].velocity;
        double maxVel = dataPoints[0].velocity;
        
        for (const auto& point : dataPoints) {
            if (point.velocity < minVel) minVel = point.velocity;
            if (point.velocity > maxVel) maxVel = point.velocity;
        }
        
        std::cout << "Минимальная скорость: " << minVel << " м/с\n";
        std::cout << "Максимальная скорость: " << maxVel << " м/с\n";
    }
    
    void plotResults() const {
        #ifdef _WIN32
            std::cout << "Визуализация (для Windows требуется установленный gnuplot)\n";
        #endif
        
        FILE* gnuplotPipe = popen("gnuplot -persist", "w");
        
        if (!gnuplotPipe) {
            std::cerr << "Ошибка: gnuplot не найден. Установите gnuplot для визуализации.\n";
            return;
        }
        
        fprintf(gnuplotPipe, "set multiplot layout 2,1 title 'Анализ траектории движения'\n");
        
        // График позиции
        fprintf(gnuplotPipe, "set title 'Зависимость положения от времени'\n");
        fprintf(gnuplotPipe, "set xlabel 'Время, с'\n");
        fprintf(gnuplotPipe, "set ylabel 'Координата, м'\n");
        fprintf(gnuplotPipe, "set grid\n");
        fprintf(gnuplotPipe, "plot 'velocity.csv' using 1:2 with lines lw 2 title 'x(t)'\n");
        
        // График скорости
        fprintf(gnuplotPipe, "set title 'Зависимость скорости от времени'\n");
        fprintf(gnuplotPipe, "set ylabel 'Скорость, м/с'\n");
        fprintf(gnuplotPipe, "plot 'velocity.csv' using 1:3 with lines lw 2 title 'v(t)'\n");
        
        fprintf(gnuplotPipe, "unset multiplot\n");
        fflush(gnuplotPipe);
        
        int status = pclose(gnuplotPipe);
        if (status != 0) {
            std::cerr << "Предупреждение: gnuplot завершился с ошибкой\n";
        }
    }
};

int main() {
    TrajectoryAnalyzer analyzer;
    
    std::cout << "=== Анализатор траектории движения ===\n";
    
    // Загрузка данных
    if (!analyzer.loadTrajectoryData("traj.csv")) {
        return 1;
    }
    
    // Вычисление скоростей
    analyzer.calculateVelocities();
    
    // Сохранение результатов
    if (!analyzer.saveResultsToFile("velocity.csv")) {
        return 1;
    }
    
    // Вывод статистики
    analyzer.displayStatistics();
    
    // Визуализация
    std::cout << "\nПостроение графиков...\n";
    analyzer.plotResults();
    
    return 0;
}
}