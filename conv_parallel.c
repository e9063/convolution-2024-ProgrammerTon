#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

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

    int  size_answer = NA - NF + 1;
    int *answer = (int*)malloc(sizeof(int) * size_answer);

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
    //printf("\n\nTime taken is %f\n\n", exec_time);
    
    for (int i = 0; i < size_answer; i++) {
        printf("%d\n", answer[i]);
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