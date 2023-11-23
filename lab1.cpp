#include <iostream>
#include <omp.h>
#include <ctime>


int main(int argc, char *argv[]){
	double start, finish;
	start = omp_get_wtime();
	
	const int count = 1000000;
	const int threads = 16;
	const int random_seed = 567;
	const int reps = 2000;
	int** array = 0;
	int max = -1;
	
	srand(random_seed);
	
	printf("OpenMP: %d;\n", _OPENMP);
	printf("Arrays length: %d; Max threads: %d; Reps: %d;\n", count, threads-1, reps);
	
	array = (int**)malloc(reps * sizeof(int*));
	for (int i = 0; i < reps; ++i) {
		array[i] = (int*)malloc(count * sizeof(int));
		for (int j = 0; j < count; ++j) {
			array[i][j] = rand();
		}
	}
	
	for (int th = 1; th < threads; ++th){
		for (int i = 0; i < reps; ++i){
			max = -1;
			#pragma omp parallel num_threads(th) shared(array, i, count) reduction(max: max) default(none)
			{
				#pragma omp for
				for (int j = 0; j < count; ++j) {
					if (array[i][j] > max) {
						max = array[i][j];
					}
				}
			}
		}
	}
	finish = omp_get_wtime();
	printf("Time: %lf \n", (finish - start));
	return(0);
}
