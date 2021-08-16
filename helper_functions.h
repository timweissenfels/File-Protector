//
// Created by Tim Weissenfels on 16.08.21.
//

#ifndef FILE_PROTECTOR_HELPER_FUNCTIONS_H
#define FILE_PROTECTOR_HELPER_FUNCTIONS_H

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

using namespace boost::multiprecision;

template<class T>
T generate_number(boost::mt19937 &random_generator, T max) {
    boost::random::uniform_int_distribution<T> dist(1, max);
    return dist(random_generator);
}

// Taken from https://stackoverflow.com/a/1900161/8964221
int getSeed();

#endif //FILE_PROTECTOR_HELPER_FUNCTIONS_H
