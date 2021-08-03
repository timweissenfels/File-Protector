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
/*
1.Generate a random 2048 bit odd number, say p

2. Test to see if p is prime; 
if it is, return p; this is expected to occur after testing about Log(p)/2 ∼177 candidates

3. Otherwise set p=p+2, goto 2
*/

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

   if(miller_rabin_test(num, 45, gen2)) 
        return true;
   return false;
}

// Taken from https://stackoverflow.com/a/1900161/8964221
int getSeed()
{
    std::ifstream rand("/dev/urandom");
    char tmp[sizeof(int)];
    rand.read(tmp,sizeof(int));
    rand.close();
    int* number = reinterpret_cast<int*>(tmp);
    return (*number);
}

int main() {
    uint2048_t max_num = (std::numeric_limits<uint1024_t>::max)();
    max_num *= max_num;
    
    //Get Random 2048 Bit odd Number
    boost::mt19937 random_generator(getSeed());
    auto rand_num = generate_number(random_generator,max_num);
    while(!check_prime(rand_num)) { 
        rand_num = generate_number(random_generator,max_num);
    }

    std::cout << rand_num << std::endl;
    return 0;
}
