FROM debian:latest

ENV CC="gcc" CFLAGS="-Wall -Wextra -Werror" LDFLAGS="-lreadline" READLINE_LINK=""

RUN apt-get -y update && \
	apt-get install \
	vim \
	make \
	git \
	lldb \
	valgrind \
	libcriterion-dev \
	libreadline-dev \
	strace \
	-y

#   docker run -it -v ~/files/marshell:/marsh [image_tag/image_ID]
#