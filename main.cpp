// Tim Weissenfels 2021

//Google Benchmark
#include <benchmark/benchmark.h>

//Header Files
#include "uint_bit_types.h"
#include "helper_functions.h"
#include "calculations.h"


//------------------BENCHMARKS-----------------------//

template <typename T>
static void BM_get_totient(benchmark::State& state) {
    std::pair<T,T> primes(get_primes<T>());
    for(auto _ : state)
        get_totient(primes);
}

BENCHMARK_TEMPLATE(BM_get_totient,uint1024_t)
    ->Unit(benchmark::kMillisecond)
    ->Iterations(1);

static void BM_getSeed(benchmark::State& state) {
    for(auto _ : state)
        getSeed();
}

BENCHMARK(BM_getSeed)
    ->Unit(benchmark::kMillisecond)
    ->Iterations(5);

template <typename T>
static void BM_get_primes(benchmark::State& state) {
    for(auto _ : state)
        get_primes<T>();
}

BENCHMARK_TEMPLATE(BM_get_primes,uint1024_t)
    ->Unit(benchmark::kMillisecond)
    ->Iterations(1);

static void BM_generate_number(benchmark::State& state) {
    boost::mt19937 generator(clock() + getSeed());
    auto max_num = (std::numeric_limits<uint8192_t>::max)();
    for(auto _ : state)
        generate_number(generator,max_num);
}

BENCHMARK(BM_generate_number)
    ->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();
