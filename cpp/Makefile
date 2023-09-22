
all: build run

build:
	g++ -std=c++2b -o source main.cpp
	mkdir -p out
	mv source ./out/source

run:
	./out/source > output.ppm
