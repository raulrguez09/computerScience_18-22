#include <omp.h>
#include <iostream>

int main(void)
{
	#pragma omp parallel
	std::cout << std::to_string(omp_get_thread_num()) + ": hello world!\n";
}
