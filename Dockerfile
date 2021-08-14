FROM debian:bullseye

#Copy over Github repo to get install and cpp files
COPY . /repo
WORKDIR /repo

#Install all CPP Boost libarys
RUN apt-get update -y
RUN apt-get install -y g++ git cmake libboost-all-dev \
 && apt-get clean \
 && rm -rf /var/lib/apt/lists/*

#Setup Google Benchmarking libarys
RUN sh ./setup_google_benchmark.sh

#Build executable file File_Protector
RUN sh ./build.sh

# Run the program output from the previous step
CMD ["./File_Protector"]
