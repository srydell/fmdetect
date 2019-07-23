#include <benchmark/benchmark.h>
#include <iostream>

static void BM_foo(benchmark::State &state) {
	std::cout << "Foo " << std::endl;
	for (auto _ : state) {
		std::cout << state.iterations() << " In loop " << std::endl;
	}
}

BENCHMARK(BM_foo);

BENCHMARK_MAIN();
