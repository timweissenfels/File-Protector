//
// Created by Tim Weissenfels on 16.08.21.
//

#ifndef FILE_PROTECTOR_CALCULATIONS_H
#define FILE_PROTECTOR_CALCULATIONS_H

//CPP Standard Libarys
#include <iostream>
#include <fstream>
#include <future>
#include <chrono>
#include <vector>

template <typename T>
uint16777216_t get_totient(std::pair<T,T> prime_pair) {
    uint16777216_t t = (prime_pair.first - 1) * (prime_pair.second - 1);
    return t;
}

//Return type defines key length (uint1024_t,uint2048_t uint4096_t,uint8192_t, etc.)
template <class T>
std::pair<T,T> get_primes() {
    std::pair<T,T> prime_pair(0,0);

    T max_num = std::numeric_limits<T>::max();
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

                if(prime_pair.second != 0) {
                            auto t = get_totient(prime_pair);
                            return prime_pair;
                        }
                    }
                }
            }
        }
#endif //FILE_PROTECTOR_CALCULATIONS_H
