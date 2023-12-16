#include <iostream>
#include <omp.h>
#include <ctime>

int main(int argc, char *argv[]){
	const int count = 20000000;
	const int threads = 16;
    const int reps = 200;
	const int random_seed = 567;
	int* array = 0;
	int max = -1;
	
	srand(random_seed);
	
	printf("OpenMP: %d;\n", _OPENMP);

    double start, finish;
    start = omp_get_wtime();

	array = (int*)malloc(count * sizeof(int));
	for (int i = 0; i < count; ++i) {
		array[i]= rand();
	}

	for(int j(0); j<reps; ++j){
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
    }
	
	free(array);
	finish = omp_get_wtime();
	printf("Time : %lf \n", (finish - start));
	return(0);
}
