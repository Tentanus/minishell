FROM debian:latest

ENV CC="gcc" CFLAGS="-Wall -Wextra -Werror" READLINE_LINK="-lreadline"

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

#	
#	start up docker application
#
#	to build image:
#	docker build ./ -f docker_config/Dockerfile
#
#	to find image_ID:
#	docker image list
#
#	to run docker container:
#	docker run -it --rm -v $HOME/files/marshell:/marsh [image_tag/image_ID]
#	docker run -it --rm -v $HOME/Desktop/minishell:/marsh [image_tag/image_ID]
#
#	cd marsh
#	make fclean
#	make dock (executable = "marshell")
#
#	to run valgrind:
#	valgrind --leak-check=full --show-leak-kinds=all --suppressions=[SUPPRESSIONFILE.supp] [EXE]
#	leaks shown at exit (or ctrl-D)
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
