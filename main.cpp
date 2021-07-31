// Tim Weissenfels 2021

#include <iostream>
#include <fstream>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>

using namespace boost::multiprecision;

/*
1.Generate a random 512 bit odd number, say p

2. Test to see if p is prime; 
if it is, return p; this is expected to occur after testing about Log(p)/2∼177 candidates

3. Otherwise set p=p+2, goto 2
*/

template <class T>
T generate_number(auto &random_generator, T max) {
    boost::random::uniform_int_distribution<T> dist(1, max);
    return dist(random_generator);
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
    uint512_t max_num = (std::numeric_limits<uint512_t>::max)();
    
    //Get Random 512 Bit odd Number
    boost::mt19937 random_generator(getSeed());
    uint512_t rand_num = 0;
    while(rand_num % 2 == 0) { rand_num = generate_number(random_generator,max_num);}

    std::cout << rand_num << std::endl; 
    return 0;
}
