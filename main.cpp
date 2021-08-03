// Tim Weissenfels 2021

#include <iostream>
#include <fstream>
#include <chrono>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <boost/multiprecision/miller_rabin.hpp>

using namespace boost::multiprecision;

/*
1.Generate a random 512 bit odd number, say p

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
bool isPrime(T numb)
{
    T it;
    for (it = 2; it < numb; it++)
    {
        if ((numb % it) == 0) {
            std::cout << "Non" << std::endl;
            return false;
        }
    }

    return true;
}

template <class T>
bool check_prime(T num) {
   if(num % 2 == 0)
       return false;

   boost::mt11213b gen2(clock());

   for(unsigned i = 0; i < 100000; ++i) {
      if(miller_rabin_test(num, 25, gen2)) 
        return true;
   }
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
    uint128_t max_num = (std::numeric_limits<uint128_t>::max)();
    auto t1 = std::chrono::high_resolution_clock::now(); 
    
    //Get Random 128 Bit odd Number
    boost::mt19937 random_generator(clock());
    auto rand_num = generate_number(random_generator,max_num);
   
    while(!check_prime(rand_num)) { 
        rand_num = generate_number(random_generator,max_num);
        std::cout << rand_num << std::endl;
    }

    std::cout << "FOUND: " << rand_num << std::endl;
    
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>( t2 - t1 ).count();
    std::cout << duration << std::endl;
    return 0;
}
