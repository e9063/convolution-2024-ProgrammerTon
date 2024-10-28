#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

int main() {
    // ---- input and malloc A, F ----
    int NA, NF;
    scanf("%d %d", &NA, &NF);
    int *A = malloc(sizeof(int) * NA);
    int *F = malloc(sizeof(int) * NF);
    for (int i = 0; i < NA; i++) {
        scanf("%d", &A[i]);
    }
    for (int i = 0; i < NF; i++) {
        scanf("%d", &F[i]);
    }
    // ---- end input and malloc ----

    // ---- choose number of thread, set up variable, and allocate ----
    omp_set_num_threads(4);
    int size_answer = NA - NF + 1;
    int *answer = (int *)malloc(sizeof(int) * size_answer);
    clock_t start, end;
    
    // ---- convolution and count time ----
    start = clock();
    #pragma omp parallel for
    for (int i = 0; i < size_answer; i++) {
        answer[i] = 0;
        for (int j = 0; j < NF; j++) {
            answer[i] += A[i + j] * F[NF - j - 1];
        }
    }
    end = clock();

    // ---- print time taken in output_parallel_time.txt ----
    FILE *time_file = fopen("output_parallel_time.txt", "w");
    fprintf(time_file, "Time taken for parallel is %f seconds\n", ((double) (end - start)) / CLOCKS_PER_SEC);
    fclose(time_file);

    // ---- print output ----
    for (int i = 0; i < size_answer; i++) {
        printf("%d", answer[i]);
        if (i != size_answer - 1) {
            printf("\n");
        }
    }

    // ---- free memory ----
    free(F);
    free(A);
    free(answer);
    // ---- end free ----
    return 0;
}
