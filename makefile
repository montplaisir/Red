
all: omp

omp: main.cpp
	g++ main.cpp -o omp -fopenmp

clean:
	rm -f omp
