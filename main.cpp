// Tim Weissenfels 2021

//Header Files
#include "uint_bit_types.h"
#include "helper_functions.h"
#include "calculations.h"

int main() {
    std::pair<cpp_int,cpp_int> primes = get_primes<uint2048_t>();

    cpp_int totient = get_totient(primes);
    cpp_int n_value = get_n_value(primes);

    std::cout << t.first << std::endl << t.second << std::endl;
    std::cout << x << std::endl;

}