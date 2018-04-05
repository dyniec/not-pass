CC=g++
CXX_FLAGS=-std=c++14	-Wall -Wextra -Wdouble-promotion -Winit-self -Wparentheses -Wsequence-point -Wfloat-equal -Wshadow
CXX_FLAGS=-std=c++14 -g -lpthread -lm -Wall -Wextra -Wdouble-promotion -Winit-self -Wparentheses -Wsequence-point -Wfloat-equal -Wshadow -D_GLIBCXX_DEBUG 
all:	main

main: main.cpp
		$(CC) main.cpp $(CXX_FLAGS) -o main
