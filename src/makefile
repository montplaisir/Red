
all: paral

paral: libRed.so main.cpp
	g++ -O2 -std=c++14 -Wall -fpic -fopenmp ./libRed.so main.cpp -o paral

libRed.so: RedMgr.hpp
	g++ -O2 -std=c++14 -Wall -Wextra -fpic -fopenmp -shared -o libRed.so -L -Wl,-soname,'libRed.so' -Wl,-rpath-link,'.' -Wl,-rpath,'$$ORIGIN'



clean:
	rm -f libRed.so paral
