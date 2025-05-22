#include <iostream>
#include <chrono>
#include <thread>
#include <future>

using namespace std;
using namespace std::chrono;

double formula1(double x) {
    return x * x - x * x + 4 * x - 5 * x + x + x;
}

double formula2(double x) {
    return x + x;
}

void run_threads(int N, double x) {
    double res1, res2;
    double time1, time2, time3;

    auto future1 = async(launch::async, [&]() {
        auto start = high_resolution_clock::now();
        for (int i = 0; i < N; ++i) {
            res1 = formula1(x);
        }
        auto end = high_resolution_clock::now();
        return duration_cast<duration<double>>(end - start).count();
    });

    auto future2 = async(launch::async, [&]() {
        auto start = high_resolution_clock::now();
        for (int i = 0; i < N; ++i) {
            res2 = formula2(x);
        }
        auto end = high_resolution_clock::now();
        return duration_cast<duration<double>>(end - start).count();
    });

    time1 = future1.get();
    time2 = future2.get();

    auto start3 = high_resolution_clock::now();
    for (int i = 0; i < N; ++i) {
        double res3 = res1 + res2 - res1;
        asm volatile("" : "+g" (res3));
    }
    auto end3 = high_resolution_clock::now();
    time3 = duration_cast<duration<double>>(end3 - start3).count();

    cout << "Threads time for " << N << " iterations:\n";
    cout << "Formula1: " << time1 << " sec\n";
    cout << "Formula2: " << time2 << " sec\n";
    cout << "Formula3: " << time3 << " sec\n";
    cout << "Total: " << max(time1, time2) + time3 << " sec\n";
}

int main() {
    double x = 5.0;
    run_threads(10000, x);
    run_threads(100000, x);
    return 0;
}