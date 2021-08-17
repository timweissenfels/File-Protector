FROM ubuntu:bionic

#Copy over Github repo to get install and cpp files
COPY . /repo
WORKDIR /repo

#Install all CPP Boost library's
RUN apt-get update -y
RUN apt-get install -y g++ git cmake libboost-all-dev \
 && apt-get clean \
 && rm -rf /var/lib/apt/lists/*

########################################################
# Essential packages for remote debugging and login in
########################################################

RUN apt-get update && apt-get install -y \
    apt-utils gcc g++ openssh-server cmake build-essential gdb gdbserver rsync vim

RUN mkdir /var/run/sshd
RUN echo 'root:root' | chpasswd
RUN sed -i 's/PermitRootLogin prohibit-password/PermitRootLogin yes/' /etc/ssh/sshd_config

# SSH login fix. Otherwise user is kicked off after login
RUN sed 's@session\s*required\s*pam_loginuid.so@session optional pam_loginuid.so@g' -i /etc/pam.d/sshd

ENV NOTVISIBLE "in users profile"
RUN echo "export VISIBLE=now" >> /etc/profile

# 22 for ssh server. 7777 for gdb server.
EXPOSE 22 7777

RUN useradd -ms /bin/bash debugger
RUN echo 'debugger:pwd' | chpasswd

#Clone GTest
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

# Run the program output from the previous step
ENTRYPOINT ["/usr/sbin/sshd"]
CMD ["-D"]
