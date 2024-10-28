#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    // ---- input and malloc A, F ----
    int NA, NF;
    scanf("%d %d", &NA, &NF);
    int *A = malloc(sizeof(int) * NA);
    int *F = malloc(sizeof(int) * NF);
    for(int i = 0; i < NA; i++){
        scanf("%d", &A[i]);
    }
    for(int i = 0; i < NF; i++){
        scanf("%d", &F[i]);
    }
    // ---- end input and malloc----

    // ---- set up variable and allocate ----
    int  size_answer = NA - NF + 1;
    int *answer = (int*)malloc(sizeof(int) * size_answer);
    clock_t start, end;
    double cpu_time_used;

    // ---- convolution and count time ----
    start = clock();
    for (int i = 0; i < size_answer; i++) {
        answer[i] = 0;
        for (int j = 0; j < NF; j++) {
            answer[i] += A[i + j] * F[NF - j - 1];
        }
    }
    end = clock();

    // ---- print time taken in output_sequential_time.txt ----
    FILE *time_file = fopen("output_sequential_time.txt", "w");
    fprintf(time_file, "Time taken for sequential is %f seconds\n", ((double) (end - start)) / CLOCKS_PER_SEC);
    fclose(time_file);

    // ---- print output ----
    for (int i = 0; i < size_answer; i++) {
        printf("%d", answer[i]);
        if(i!=size_answer-1){
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

/*
8 5
7
5
3
2
0
4
2
5
1
1
2
2
1
*/

//printf("thread number use : %d\n", omp_get_thread_num());