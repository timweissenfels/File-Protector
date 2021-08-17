FROM ubuntu:bionic

#Copy over Github repo to get install and cpp files
COPY . /repo
WORKDIR /repo

#Install all CPP Boost library's
RUN apt-get update -y
RUN apt-get install -y g++ git cmake libboost-all-dev \
 && apt-get clean \
 && rm -rf /var/lib/apt/lists/*

#Clone GTest
RUN git clone https://github.com/google/benchmark.git /repo/benchmark
RUN git clone https://github.com/google/googletest.git /repo/benchmark/googletest
WORKDIR /repo/benchmark

#Build GBenchmark & GTest
RUN cmake -E make_directory "build"
RUN cmake -E chdir "build" cmake -DCMAKE_BUILD_TYPE=Release ../
RUN cmake --build "build" --config Release

WORKDIR /repo

#Build executable file File_Protector
RUN cmake .
RUN make
