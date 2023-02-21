FROM ubuntu:latest

ENV CC=clang CFLAGS="-Wall -Wextra -g -fsanitize=address" LDFLAGS="-lreadline" READLINE_LINK=""

RUN apt-get update && \
    apt-get install vim \
    libcriterion-dev \
    make \
    clang \
    valgrind \
    libreadline-dev \
    strace \
    lldb \
    -y && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/* && \
    mkdir -p /usr/lib/local/lib/python3.10 && \
    ln -s /usr/lib/llvm-14/lib/python3.10/dist-packages /usr/lib/local/lib/python3.10/dist-packages