CC=g++
CXX_FLAGS=-std=c++14 -O2 -Wall -Wextra -Wdouble-promotion -Winit-self -Wparentheses -Wsequence-point -Wfloat-equal -Wshadow
all:	main

main: main.cpp
		$(CC) main.cpp $(CXX_FLAGS) -o main
