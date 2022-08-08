// Tim Weissenfels 2021

//Header Files
#include "uint_bit_types.h"
#include "helper_functions.h"
#include "calculations.h"

int main() {
    std::pair<cpp_int,cpp_int> primes = get_primes<uint1024_t>();

    cpp_int totient = get_totient(primes);
    cpp_int n_value = get_n_value(primes);

    std::cout << primes.first << std::endl << primes.second << std::endl << std::endl;
    std::cout << totient << std::endl << std::endl;
    std::cout << n_value << std::endl << std::endl;

}
