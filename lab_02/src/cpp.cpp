#include <iostream>
#include <chrono>
#include <limits>
#include <string>

double calculate(double x) {
    return x*x - x*x + x*4 - x*5 + x + x;
}

int main() {
    const double x = 3.0;
    
    while(true) {
        std::cout << "Enter iterations count (or 'q' to quit): ";
        std::string input;
        std::cin >> input;

        // 1. Проверка на выход
        if(input == "q" || input == "Q") {
            std::cout << "Exiting program..." << std::endl;
            break;
        }

        // 2. Проверка что ввод - число
        bool is_valid = true;
        for(char c : input) {
            if(!isdigit(c)) {
                is_valid = false;
                break;
            }
        }

        if(!is_valid) {
            std::cerr << "Error: Input must be positive integer!\n\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        // 3. Преобразование и проверка диапазона
        try {
            int n = std::stoi(input);
            
            if(n <= 0) {
                std::cerr << "Error: Number must be greater than zero!\n\n";
                continue;
            }

            // 4. Вычисления
            auto start = std::chrono::high_resolution_clock::now();
            for(int i = 0; i < n; ++i) {
                volatile double result = calculate(x);
            }
            auto end = std::chrono::high_resolution_clock::now();

            // 5. Вывод результата
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
            std::cout << "Time: " << duration.count() << " ms\n" << std::endl;

        } catch(const std::exception& e) {
            std::cerr << "Error: " << e.what() << "\n\n";
        }
    }
    
    return 0;
}