g++ main.cpp -pthread -lbenchmark  -isystem benchmark/include -Lbenchmark/build/src -O2 -o File-Protector  -Wfatal-errors -I ./boost
./File-Protector
