#include "../commonTest.h"
#include "benchmark/benchmark.h"

void IntToString(benchmark::State& state) {
    while (state.KeepRunning()) {
        benchmark::DoNotOptimize(
           IntToStringConversionTest(state.range_x())
        );
    }
}
BENCHMARK(IntToString)->Arg(TEST_NUM_COUNT1000);

void DoubleToString(benchmark::State& state) {
    while (state.KeepRunning()) {
        benchmark::DoNotOptimize(
           DoubleToStringConversionTest(state.range_x())
        );
    }
}
BENCHMARK(DoubleToString)->Arg(TEST_NUM_COUNT1000);

BENCHMARK_MAIN()
