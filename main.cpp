// Tim Weissenfels 2021

//CPP Standard Libarys
#include <iostream>
#include <fstream>
#include <future>
#include <chrono>
#include <vector>

//Boost Libarys
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <boost/multiprecision/miller_rabin.hpp>

//Google Benchmark
#include <benchmark/benchmark.h>

using namespace boost::multiprecision;

#define generate_large_number_type(TYPENAME,pre_TYPENAME,BIT_COUNT) \
    typedef number<cpp_int_backend<BIT_COUNT,BIT_COUNT,unsigned_magnitude,checked>> TYPENAME; \
    namespace std { \
        template<> class numeric_limits<TYPENAME> : public std::numeric_limits<unsigned int> { \
            public: \
                    static TYPENAME max() { \
                        TYPENAME ret = (std::numeric_limits<pre_TYPENAME>::max)(); \
                        return (ret*ret); \
                    }; \
        }; \
    }

generate_large_number_type(uint2048_t,uint1024_t,2048)
generate_large_number_type(uint4096_t,uint2048_t,4096)
generate_large_number_type(uint8192_t,uint4096_t,8192)
generate_large_number_type(uint16384_t,uint8192_t,16384)

template <class T>
T generate_number(boost::mt19937 &random_generator, T max) {
    boost::random::uniform_int_distribution<T> dist(1, max);
    return dist(random_generator);
}

// Taken from https://stackoverflow.com/a/1900161/8964221
int getSeed() {
    std::ifstream rand("/dev/urandom");
    char tmp[sizeof(int)];
    rand.read(tmp,sizeof(int));
    rand.close();
    int* number = reinterpret_cast<int*>(tmp);
    return (*number);
}

//Return type defines key lenght (uint1024_t,uint2048_t uint4096_t,uint8192_t, etc.)
template <class T>
std::pair<T,T> get_primes() {
    std::pair<T,T> prime_pair(0,0); 
    T max_num = (std::numeric_limits<T>::max)();
    boost::mt19937 random_generator((getSeed() + clock()));
    auto rand_num = generate_number(random_generator,max_num);
    boost::mt11213b second_generator(getSeed());

    auto prime_checker = []<typename G>(T num, G sec_gen) -> std::pair<bool,T> {
        if(miller_rabin_test(num, 45, sec_gen)) 
            return std::make_pair(true,num);
        return std::make_pair(false,num);
    };

    for(;;) {
        std::vector<std::future<std::pair<bool,T>>> primes;
        for(int i = 0; i < 1000;i++)
            primes.emplace_back(std::async(prime_checker,generate_number(random_generator,max_num),second_generator));

        for(auto& element : primes) {
            auto values = element.get();
            if(values.first == true) {
                if(prime_pair.first == 0)
                    prime_pair.first = values.second;
                else 
                    prime_pair.second = values.second;

                if(prime_pair.second != 0)
                    return prime_pair;
            }
        }
    }
}

template <typename T>
uint16384_t get_totient(std::pair<T,T> prime_pair) {
    //return ((prime_pair.first - 1) * (prime_pair.second - 1));
    return 0;
}

//BENCHMARKS
template <typename T>
static void BM_get_totient(benchmark::State& state) {
    std::pair<T,T> primes(get_primes<T>());
    for(auto _ : state)
        get_totient(primes);
}

BENCHMARK_TEMPLATE(BM_get_totient,uint1024_t)->Unit(benchmark::kMillisecond);

static void BM_getSeed(benchmark::State& state) {
    for(auto _ : state)
        getSeed();
}

BENCHMARK(BM_getSeed)->Unit(benchmark::kMillisecond);

template <typename T>
static void BM_get_primes(benchmark::State& state) {
    for(auto _ : state)
        get_primes<T>();
}

BENCHMARK_TEMPLATE(BM_get_primes,uint2048_t)->Unit(benchmark::kMillisecond);

static void BM_generate_number(benchmark::State& state) {
    boost::mt19937 generator(clock() + getSeed());
    auto max_num = (std::numeric_limits<uint8192_t>::max)();
    for(auto _ : state)
        generate_number(generator,max_num);
}

BENCHMARK(BM_generate_number)->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();
