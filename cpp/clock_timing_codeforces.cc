#include <algorithm>
#include <array>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <vector>
#if defined(_WIN32) || defined(_WIN64)
#include <Windows.h>
#endif
using namespace std;

long double cpu_time() {
#if defined(_WIN32) || defined(_WIN64)
    FILETIME creation_ft, exit_ft, kernel_ft, user_ft;
    GetProcessTimes(GetCurrentProcess(), &creation_ft, &exit_ft, &kernel_ft, &user_ft);

    auto extract_time = [](FILETIME ft) {
        return 1e-7L * (ft.dwLowDateTime | uint64_t(ft.dwHighDateTime) << 32);
    };

    return extract_time(user_ft) + extract_time(kernel_ft);
#else
    return (long double) clock() / CLOCKS_PER_SEC;
#endif
}

#include <sys/time.h>

long double wall_time() {
    timeval tv;
    gettimeofday(&tv, nullptr);
    return tv.tv_sec + tv.tv_usec * 1e-6L;
}

const double TIME_CUTOFF = 1.0;
const int ITERATIONS = 1e6;

int main() {
    long double clock_begin = clock();
    long double wall_begin = wall_time();
    auto chrono_begin = chrono::steady_clock::now();
    long double cpu_begin = cpu_time();
    int64_t sum = 0;

    while ((clock() - clock_begin) / CLOCKS_PER_SEC < TIME_CUTOFF) {
        for (int iter = 0; iter < ITERATIONS; iter++)
            sum += iter % 3;
    }

    cout << "clock: " << (clock() - clock_begin) / CLOCKS_PER_SEC << 's' << endl;
    cout << "wall: " << wall_time() - wall_begin << 's' << endl;
    cout << "chrono: " << 1e-6L * chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - chrono_begin).count() << 's' << endl;
    cout << "cpu: " << cpu_time() - cpu_begin << 's' << endl;
    cout << "sum = " << sum << endl;
}