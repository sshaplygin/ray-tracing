
all: build run

build:
	g++ -std=c++11 -o source main.cpp
	mkdir -p out
	mv source ./out/source

run:
	./out/source > output.ppm
