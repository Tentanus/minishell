FROM debian:latest

ENV CC="gcc" CFLAGS="-Wall -Wextra -Werror" LDFLAGS="-lreadline" READLINE_LINK=""

RUN apt-get -y update \
&& \
	apt-get install \
	gcc \
	vim \
	make \
	git \
	lldb \
	valgrind \
	libcriterion-dev \
	libreadline-dev \
	strace \
	manpages \
	less \
	-y \
&& \
	apt-get clean \
&& \
	rm -rf /var/lib/apt/lists/*

ADD docker_config/.vimrc /root/.vimrc

#	to build image:
#	docker build ./ -f docker_config/Dockerfile
#
#	to run docker container:
#	docker run -it --rm -v ~/files/marshell:/marsh [image_tag/image_ID]
#
#	to run valgrind:
#	valgrind --leak-check=full --show-leak-kinds=all --suppressions=[SUPPRESSIONFILE.supp] [EXE]
#
#		apt-get -y update && \
#		apt-get install \
#		make \
#		clang \
#		valgrind \
#		libreadline-dev \
#		strace \
#		lldb \
#		-y && \
#		apt-get clean && \
#		rm -rf /var/lib/apt/lists/* && \
#		mkdir -p /usr/lib/local/lib/python3.10 && \
#		ln -s /usr/lib/llvm-14/lib/python3.10/dist-packages /usr/lib/local/lib/python3.10/dist-packages#
#
#	last two lines might be required to get cirterion working. it needs a symbolic link to function