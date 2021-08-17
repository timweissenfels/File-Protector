//
// Created by Tim Weissenfels on 16.08.21.
//

#ifndef FILE_PROTECTOR_UINT_BIT_TYPES_H
#define FILE_PROTECTOR_UINT_BIT_TYPES_H
#include <boost/multiprecision/cpp_int.hpp>

using namespace boost::multiprecision;

#define generate_large_number_type(TYPENAME,BIT_COUNT) \
typedef number<cpp_int_backend<BIT_COUNT,BIT_COUNT,unsigned_magnitude,unchecked,void>> TYPENAME; \
namespace std { \
    template<> class numeric_limits<TYPENAME> : public std::numeric_limits<unsigned int> { \
        public: \
            static TYPENAME max() { \
            return ~(TYPENAME(0)); \
            }; \
    }; \
}

generate_large_number_type(uint2048_t,2048)
generate_large_number_type(uint4096_t,4096)
generate_large_number_type(uint8192_t,8192)
generate_large_number_type(uint16384_t,16384)
generate_large_number_type(uint32768_t,32768)
generate_large_number_type(uint65536_t,65536)
generate_large_number_type(uint131072_t,131072)
generate_large_number_type(uint262144_t,262144)
generate_large_number_type(uint524288_t,524288)
generate_large_number_type(uint1048576_t,1048576)
generate_large_number_type(uint2097152_t,2097152)
generate_large_number_type(uint4194304_t,4194304)
generate_large_number_type(uint8388608_t,8388608)
generate_large_number_type(uint16777216_t,16777216)

#endif //FILE_PROTECTOR_UINT_BIT_TYPES_H
