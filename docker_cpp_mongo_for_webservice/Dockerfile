FROM ubuntu:18.04

RUN apt update
RUN apt -y upgrade
RUN apt install -y --no-install-recommends \
    autoconf \
    automake \
    ca-certificates \
    libtool \
    g++ \
    gcc \
    gdb \
    git \
    make \
    pkg-config \
    wget \
    libssl-dev \
    cmake

######### Installing mongo-c-driver ##############
RUN wget https://github.com/mongodb/mongo-c-driver/releases/download/1.14.0/mongo-c-driver-1.14.0.tar.gz
RUN tar xvzf mongo-c-driver-1.14.0.tar.gz
RUN mkdir mongo-c-driver-1.14.0/cmake-build
RUN cd mongo-c-driver-1.14.0/cmake-build && cmake -DENABLE_AUTOMATIC_INIT_AND_CLEANUP=OFF .. && make && make install


######### Installing mongo-cxx-driver ############
RUN git clone https://github.com/mongodb/mongo-cxx-driver.git --branch releases/stable --depth 1
RUN cd mongo-cxx-driver/build && cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr/local .. && make EP_mnmlstc_core  && make && make install


################## clean up ######################
RUN rm -rf /mongo-c-driver-1.14.0 && rm -rf /mongo-cxx-driver && rm mongo-c-driver-1.14.0.tar.gz

############# installation libboost ##############
RUN cd /tmp && wget https://dl.bintray.com/boostorg/release/1.69.0/source/boost_1_69_0.tar.gz \
	&& tar xzf boost_1_69_0.tar.gz \
	&& cd boost_1_69_0/ && ./bootstrap.sh && ./b2 variant=release install \
	&& rm /tmp/boost_1_69_0.tar.gz && rm -rf /tmp/boost_1_69_0

############### running example ##################
COPY test.cpp .
RUN c++ --std=c++11 test.cpp -o test \
    -I/usr/local/include/mongocxx/v_noabi \
    -I/usr/local/include/bsoncxx/v_noabi \
    -L/usr/local/lib -lmongocxx -lbsoncxx
RUN LD_LIBRARY_PATH=/usr/local/lib/ ./test
