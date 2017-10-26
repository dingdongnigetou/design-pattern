

build:
	mkdir -p bin
	g++ -std=c++11 -I/t t/test.cpp -o bin/test-all -lgtest -pthread

clean:
	\rm -f bin/*

