#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

double formula1(double x) {
    return x * x - x * x + 4 * x - 5 * x + x + x;
}

double formula2(double x) {
    return x + x;
}

double formula3(double res1, double res2) {
    return res1 + res2 - res1;
}

void run_sequential(int N, double x) {
    auto start = high_resolution_clock::now();

    for (int i = 0; i < N; ++i) {
        double res1 = formula1(x);
        double res2 = formula2(x);
        double res3 = formula3(res1, res2);
        asm volatile("" : "+g" (res3)); // Предотвращаем оптимизацию
    }

    auto end = high_resolution_clock::now();
    duration<double> diff = end - start;
    cout << "Sequential time for " << N << " iterations: " << diff.count() << " sec\n";
}

int main() {
    double x = 5.0;
    run_sequential(10000, x);
    run_sequential(100000, x);
    return 0;
}