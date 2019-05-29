
all: reduce

reduce: libRed.so main.cpp
	g++ -O2 -std=c++14 -Wall -fpic -fopenmp ./libRed.so main.cpp -o reduce

Red.o: Red.hpp Red.cpp
	g++ -O2 -std=c++14 -Wall -fpic -fopenmp -c Red.cpp -o Red.o

libRed.so: Red.o
	g++ -O2 -std=c++14 -Wall -Wextra -fpic -shared -o libRed.so Red.o -L -Wl,-soname,'libRed.so' -Wl,-rpath-link,'.' -Wl,-rpath,'$$ORIGIN'



clean:
	rm -f Red.o libRed.so reduce
