// Tim Weissenfels 2021

#include <iostream>
#include <fstream>
#include <chrono>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <boost/multiprecision/miller_rabin.hpp>

using namespace boost::multiprecision;

typedef number<cpp_int_backend<2048, 2048, unsigned_magnitude, checked>> uint2048_t;
typedef number<cpp_int_backend<4096, 4096, unsigned_magnitude, checked>> uint4096_t;

namespace std {
    template<> class numeric_limits<uint2048_t> : public std::numeric_limits<unsigned int> {
        public:
            static constexpr uint2048_t max() {
                uint2048_t ret = (std::numeric_limits<uint1024_t>::max)();
                return (ret*ret);
            }
    };
    template<> class numeric_limits<uint4096_t> : public std::numeric_limits<unsigned int> {
        public:
            static constexpr uint4096_t max() {
                uint4096_t ret = (std::numeric_limits<uint2048_t>::max)();
                return (ret*ret);
            }
    };
}

template <class T>
T generate_number(auto &random_generator, T max) {
    boost::random::uniform_int_distribution<T> dist(1, max);
    return dist(random_generator);
}

template <class T>
bool check_prime(T num) {
   if(num % 2 == 0)
       return false;

   boost::mt11213b gen2(clock());

   if(miller_rabin_test(num, 40, gen2)) 
        return true;
   return false;
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

template <class T>
T gen_prime() {
    
    T max_num = (std::numeric_limits<T>::max)();
    boost::mt19937 random_generator(getSeed());
    auto rand_num = generate_number(random_generator,max_num);
    
    while(!check_prime(rand_num)) {
        rand_num = generate_number(random_generator,max_num);
    }

    return rand_num;
}

int main() {
    std::cout << gen_prime<uint2048_t>() << std::endl;
}
