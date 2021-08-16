//
// Created by Tim Weissenfels on 16.08.21.
//

#include "helper_functions.h"

// Taken from https://stackoverflow.com/a/1900161/8964221
int getSeed() {
    std::ifstream rand("/dev/urandom");
    char tmp[sizeof(int)];
    rand.read(tmp,sizeof(int));
    rand.close();
    int* number = reinterpret_cast<int*>(tmp);
    return (*number);
}
