#include <benchmark/benchmark.h>

std::set<int> ConstructRandomSet(int size) {
    std::set<int> s;
    for (int i = 0; i < size; ++i) s.insert(i);
    return s;
}

static void BM_SetNoop(benchmark::State &state) {
    for (auto _ : state) {
        state.PauseTiming();
        std::set<int> data = ConstructRandomSet(state.range(0));
        state.ResumeTiming();

        // Nothing here
    }
    state.SetComplexityN(state.range(0));
}

BENCHMARK(BM_SetNoop)->Range(1 << 14, 1 << 22)->Complexity();
BENCHMARK_MAIN()
