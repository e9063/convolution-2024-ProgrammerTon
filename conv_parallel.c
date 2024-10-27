#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

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

    int size_answer = NA - NF + 1;
    int *answer = (int *)malloc(sizeof(int) * size_answer);

    double itime, ftime, exec_time;
    itime = omp_get_wtime();

    omp_set_num_threads(4);
    #pragma omp parallel for
    for (int i = 0; i < size_answer; i++) {
        answer[i] = 0;
        for (int j = 0; j < NF; j++) {
            answer[i] += A[i + j] * F[NF - j - 1];
        }
    }

    ftime = omp_get_wtime();
    exec_time = ftime - itime;

    for (int i = 0; i < size_answer; i++) {
        printf("%d", answer[i]);
        if (i != size_answer - 1) {
            printf("\n");
        }
    }

    // Write execution time to output_1_time.txt
    FILE *time_file = fopen("output_1_time.txt", "w");
    fprintf(time_file, "Time taken is %f seconds\n", exec_time);
    fclose(time_file);

    // ---- free memory ----
    free(F);
    free(A);
    free(answer);
    // ---- end free ----
    return 0;
}
