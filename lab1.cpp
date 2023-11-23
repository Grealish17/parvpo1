#include <iostream>
#include <omp.h>
#include <ctime>
#include <chrono>



int main(int argc, char *argv[]){
	using namespace std::chrono;
	std::chrono::high_resolution_clock::time_point t1 = high_resolution_clock::now();	
	const int count = 2000000000;
	const int threads = 16;
	const int random_seed = 567;
	int* array = 0;
	int max = -1;
	
	srand(random_seed);
	
	printf("OpenMP: %d;\n", _OPENMP);
	
	array = (int*)malloc(count * sizeof(int));
	for (int i = 0; i < count; ++i) {
		array[i]= rand();
	}
	
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
	
	// double start, finish;
	// start = omp_get_wtime();
	
	for (int th = 1; th < threads; ++th){
		max = -1;
		#pragma omp parallel num_threads(th) reduction(max: max)
		{
			#pragma omp for
			for (int i = 0; i < count; ++i) {
				if (array[i] > max) {
					max = array[i];
				}
			}
		}
	}
	
	free(array);
	// finish = omp_get_wtime();
	// printf("Time: %lf \n", (finish - start));
	printf("Time: %lf \n", time_span.count());
	return(0);
}
