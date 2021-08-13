FROM debian:latest

#Copy over Github repo to get install and cpp files
COPY . /repo
WORKDIR /repo

#Install all CPP Boost libarys
RUN apt-get update -y && apt-get upgrade -y
RUN apt-get install g++ git cmake -y
RUN apt-get install libboost-all-dev -y

#Setup Google Benchmarking libarys
RUN sh ./setup_google_benchmark.sh

#Build executable file File_Protector
RUN sh ./build.sh

# Run the program output from the previous step
CMD ["./File_Protector"]
