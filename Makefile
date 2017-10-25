

build:
	g++ -std=c++11 -I/t t/test.cpp -o test-all -lgtest -pthread

clean:
	\rm test-all

