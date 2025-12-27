#include <iostream>
#include <fstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <string>
#include <cstdio>
#include <algorithm>
#include <limits>

class SensorDataAnalyzer {
private:
    struct Measurement {
        double time;
        double sensor1Value;
        double sensor2Value;
        double difference;
        
        Measurement(double t, double s1, double s2) 
            : time(t), sensor1Value(s1), sensor2Value(s2) {
            difference = std::abs(s1 - s2);
        }
    };
    
    std::vector<Measurement> measurements;
    
public:
    bool loadSensorData(const std::string& filename) {
        std::ifstream inputFile(filename);
        
        if (!inputFile.is_open()) {
            std::cerr << "Ошибка: не удается открыть файл '" << filename << "'\n";
            return false;
        }
        
        std::string headerLine;
        if (!std::getline(inputFile, headerLine)) {
            std::cerr << "Ошибка: файл пуст или поврежден\n";
            return false;
        }
        
        double timeStamp, sensor1Reading, sensor2Reading;
        char separator;
        int lineNumber = 1;
        
        while (inputFile >> timeStamp >> separator >> sensor1Reading >> separator >> sensor2Reading) {
            if (separator != ',') {
                std::cerr << "Предупреждение: нестандартный разделитель в строке " << lineNumber << "\n";
            }
            
            measurements.emplace_back(timeStamp, sensor1Reading, sensor2Reading);
            lineNumber++;
        }
        
        inputFile.close();
        
        if (measurements.empty()) {
            std::cerr << "Ошибка: файл не содержит измерений\n";
            return false;
        }
        
        std::cout << "Загружено " << measurements.size() << " измерений\n";
        return true;
    }
    
    void analyzeDiscrepancies() {
        if (measurements.empty()) {
            std::cerr << "Нет данных для анализа\n";
            return;
        }
        
        double maxDifference = 0.0;
        double sumDifferences = 0.0;
        double maxSensor1 = measurements[0].sensor1Value;
        double minSensor1 = measurements[0].sensor1Value;
        
        for (const auto& measurement : measurements) {
            sumDifferences += measurement.difference;
            
            if (measurement.difference > maxDifference) {
                maxDifference = measurement.difference;
            }
            
            if (measurement.sensor1Value > maxSensor1) {
                maxSensor1 = measurement.sensor1Value;
            }
            
            if (measurement.sensor1Value < minSensor1) {
                minSensor1 = measurement.sensor1Value;
            }
        }
        
        double averageDifference = sumDifferences / measurements.size();
        double sensor1Range = maxSensor1 - minSensor1;
        
        std::cout << "\nСтатистика расхождений:\n";
        std::cout << "Максимальное расхождение: " << maxDifference << " м\n";
        std::cout << "Среднее расхождение: " << averageDifference << " м\n";
        std::cout << "Диапазон датчика 1: " << sensor1Range << " м\n";
        
        if (maxDifference / sensor1Range > 0.1) {
            std::cout << "ВНИМАНИЕ: значительные расхождения между датчиками (>10% диапазона)!\n";
        }
    }
    
    bool saveComparisonResults(const std::string& outputFilename) {
        std::ofstream outputFile(outputFilename);
        
        if (!outputFile.is_open()) {
            std::cerr << "Ошибка создания файла результатов\n";
            return false;
        }
        
        outputFile << "Time(s),Sensor1(m),Sensor2(m),Difference(m)\n";
        
        for (const auto& measurement : measurements) {
            outputFile << measurement.time << ","
                      << measurement.sensor1Value << ","
                      << measurement.sensor2Value << ","
                      << measurement.difference << "\n";
        }
        
        outputFile.close();
        std::cout << "Результаты сохранены в '" << outputFilename << "'\n";
        return true;
    }
    
    void visualizeData() const {
        #ifdef _WIN32
            std::cout << "Запуск визуализации... (требуется gnuplot)\n";
        #endif
        
        FILE* gnuplotPipe = popen("gnuplot -persist", "w");
        
        if (!gnuplotPipe) {
            std::cerr << "Ошибка: gnuplot не найден. Установите gnuplot для визуализации.\n";
            return;
        }
        
        fprintf(gnuplotPipe, "set multiplot layout 2,1 title 'Сравнение показаний датчиков высоты'\n");
        fprintf(gnuplotPipe, "set grid\n");
        
        // График показаний датчиков
        fprintf(gnuplotPipe, "set title 'Показания датчиков высоты'\n");
        fprintf(gnuplotPipe, "set xlabel 'Время, с'\n");
        fprintf(gnuplotPipe, "set ylabel 'Высота, м'\n");
        fprintf(gnuplotPipe, "plot 'diff.csv' using 1:2 with lines lw 2 title 'Датчик #1', ");
        fprintf(gnuplotPipe, "'diff.csv' using 1:3 with lines lw 2 title 'Датчик #2'\n");
        
        // График расхождений
        fprintf(gnuplotPipe, "set title 'Расхождение между датчиками'\n");
        fprintf(gnuplotPipe, "set ylabel 'Δh, м'\n");
        fprintf(gnuplotPipe, "plot 'diff.csv' using 1:4 with lines lw 2 title 'Разность показаний'\n");
        
        fprintf(gnuplotPipe, "unset multiplot\n");
        fflush(gnuplotPipe);
        
        int status = pclose(gnuplotPipe);
        if (status != 0) {
            std::cerr << "Предупреждение: gnuplot завершился с ошибкой\n";
        }
    }
    
    void generateSummaryReport() const {
        std::cout << "\n=== СВОДНЫЙ ОТЧЕТ ===\n";
        std::cout << "Количество измерений: " << measurements.size() << "\n";
        
        if (!measurements.empty()) {
            std::cout << "Период измерений: " << measurements.front().time 
                      << " - " << measurements.back().time << " с\n";
        }
    }
};

int main() {
    SensorDataAnalyzer analyzer;
    
    std::cout << "=== АНАЛИЗАТОР ДАННЫХ ДАТЧИКОВ ВЫСОТЫ ===\n";
    
    // Загрузка данных
    if (!analyzer.loadSensorData("sensors.csv")) {
        return 1;
    }
    
    // Анализ расхождений
    analyzer.analyzeDiscrepancies();
    
    // Сохранение результатов
    if (!analyzer.saveComparisonResults("diff.csv")) {
        return 1;
    }
    
    // Генерация отчета
    analyzer.generateSummaryReport();
    
    // Визуализация
    std::cout << "\nПостроение графиков сравнения...\n";
    analyzer.visualizeData();
    
    return 0;
}