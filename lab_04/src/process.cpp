#include <iostream>
#include <chrono>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;
using namespace std::chrono;

struct Result {
    double value;
    double duration;
};

double formula1(double x) {
    return x * x - x * x + 4 * x - 5 * x + x + x;
}

double formula2(double x) {
    return x + x;
}

void run_processes(int N, double x) {
    int pipe1[2], pipe2[2];
    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t pid1 = fork();
    if (pid1 == 0) {
        close(pipe1[0]);
        Result res;
        auto start = high_resolution_clock::now();
        for (int i = 0; i < N; ++i) {
            res.value = formula1(x);
        }
        auto end = high_resolution_clock::now();
        res.duration = duration_cast<duration<double>>(end - start).count();
        write(pipe1[1], &res, sizeof(res));
        close(pipe1[1]);
        exit(0);
    }

    pid_t pid2 = fork();
    if (pid2 == 0) {
        close(pipe2[0]);
        Result res;
        auto start = high_resolution_clock::now();
        for (int i = 0; i < N; ++i) {
            res.value = formula2(x);
        }
        auto end = high_resolution_clock::now();
        res.duration = duration_cast<duration<double>>(end - start).count();
        write(pipe2[1], &res, sizeof(res));
        close(pipe2[1]);
        exit(0);
    }

    close(pipe1[1]);
    close(pipe2[1]);

    Result res1, res2;
    read(pipe1[0], &res1, sizeof(res1));
    read(pipe2[0], &res2, sizeof(res2));

    close(pipe1[0]);
    close(pipe2[0]);

    waitpid(pid1, nullptr, 0);
    waitpid(pid2, nullptr, 0);

    auto start3 = high_resolution_clock::now();
    for (int i = 0; i < N; ++i) {
        double res3 = res1.value + res2.value - res1.value;
        asm volatile("" : "+g" (res3));
    }
    auto end3 = high_resolution_clock::now();
    double time3 = duration_cast<duration<double>>(end3 - start3).count();

    cout << "Processes time for " << N << " iterations:\n";
    cout << "Formula1: " << res1.duration << " sec\n";
    cout << "Formula2: " << res2.duration << " sec\n";
    cout << "Formula3: " << time3 << " sec\n";
    cout << "Total: " << max(res1.duration, res2.duration) + time3 << " sec\n";
}

int main() {
    double x = 5.0;
    run_processes(10000, x);
    run_processes(100000, x);
    return 0;
}