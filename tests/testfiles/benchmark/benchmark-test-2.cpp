#include <cmath>
#include <ostream>
#include <random>
#include <benchmark/benchmark.h>

template<typename Real>
BM_PowTemplated(benchmark::State& state) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<Real> dis(1, 10);
    auto s = dis(gen);
    auto t = dis(gen);
    Real y;
    while (state.KeepRunning()) {
        benchmark::DoNotOptimize(y = std::pow(s, t));
    }
    std::ostream cnull(0);
    cnull << y;
}

BENCHMARK_TEMPLATE(BM_PowTemplated, float, double, long double);
BENCHMARK_MAIN();
