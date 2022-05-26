// suma.cc: en la mayoría de sistemas la pila está limitada a 8KB, 
// consultar con 'ulimit -s' y ampliar con 'ulimit -s unlimited'

#include <algorithm>  // bind generate
#include <chrono>     // high_resolution_clock;
#include <functional> // bind
#include <iostream>   // cout endl
#include <random>     // default_random_engine uniform_int_distribution
#include <sstream>    // istringstream
#include <stdexcept>  // invalid_argument

const size_t MAX = 1 << 26; // 2^26 ~ 64MB

#ifdef DATA
double v1[MAX], v2[MAX], v3[MAX];
#endif

int main(int argc, char *argv[])
{
	if (argc != 2)
		throw std::runtime_error("uso: " + std::string(argv[0]) + " tamaño_vector");

	size_t size;

	std::istringstream iss(argv[1]);
	iss >> size;
	if(!iss || size > MAX)
		throw std::invalid_argument("el tamaño de vector excede " + std::to_string(MAX));

#ifdef STACK
	double v1[size], v2[size], v3[size];
#endif

#ifdef HEAP
	double *v1(new double[size]), *v2(new double[size]), *v3(new double[size]);
#endif

	auto rng = std::bind(std::uniform_real_distribution<double>(),
	                     std::default_random_engine());

	std::generate(v1, v1 + size, rng);
	std::generate(v2, v2 + size, rng);

	auto start = std::chrono::high_resolution_clock::now();
	for (unsigned i = 0; i < size; ++i)
		v3[i] = v1[i] + v2[i];
	auto stop  = std::chrono::high_resolution_clock::now();

	std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count() << std::endl;

	double ret = v3[std::default_random_engine()() % size];

#ifdef HEAP
	delete[] v1;
	delete[] v2;
	delete[] v3;
#endif

	return ret;
}
