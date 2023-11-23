#include <iostream>
#include <omp.h>
#include <ctime>


int main(int argc, char *argv[]){	
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
	
	double start, finish;
	start = omp_get_wtime();
	
	for (int th = 1; th < threads; ++th){
		max = -1;
		#pragma omp parallel num_threads(th) shared(array, count) reduction(max: max) default(none)
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
	finish = omp_get_wtime();
	printf("Time: %lf \n", (finish - start));
	return(0);
}
