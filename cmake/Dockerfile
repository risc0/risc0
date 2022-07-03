FROM ubuntu:20.04
RUN echo 0
RUN apt-get update -y
RUN apt-get install wget -y
RUN apt-get install vim -y
RUN apt-get install apt-utils -y
RUN apt-get install libncurses5 -y
RUN apt-get install cmake -y
RUN apt-get install build-essential -y
RUN apt-get install git -y
RUN apt-get install autoconf automake autotools-dev curl python3 libmpc-dev libmpfr-dev libgmp-dev gawk build-essential bison flex texinfo gperf libtool patchutils bc zlib1g-dev libexpat-dev  -y
RUN echo "git clone https://github.com/risc0/risc0.git" > runner.sh
RUN echo "cd risc0" >> runner.sh
RUN echo "git checkout cmakenative" >> runner.sh 
RUN echo "cmake . -B cmake-build" >> runner.sh
RUN echo "cd cmake-build && make -j 2" >> runner.sh
RUN echo "cd cmake-build && make test" >> runner.sh
CMD ["sh","/runner.sh"]
