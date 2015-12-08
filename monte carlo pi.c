#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define R 30000

//Exercises!

    //Exercise 2 - calc pi with monte carlo approximation & MPI_Reduce();

int main(int argc, char *argv[])
{

    int myid, nprocs, n, i, sum=0;
    double x, y, pi, tot, mcpi=0;
    time_t t;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    if (myid==0){
        srand((unsigned) time(&t));
        n = rand()%R;
    }
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    for (i=0; i<n; i++){
        x = (double)abs(rand()%R)/(double)(R-1);
        y = (double)abs(rand()%R)/(double)(R-1);
        if (x*x + y*y <=1) sum++;
    //printf("new point with x=%f and y=%f\n", x, y);
    }
    pi = (double)sum*4/n;
    //printf("pi is %f\n",pi);
    //printf("no of hits: %d out of %d\n", sum, n);
    MPI_Reduce(&pi, &tot, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    if (myid==0){
        mcpi = tot/(double)nprocs;
        printf("pi, averaged from %d experiments across %d nodes is %f", n*nprocs, nprocs, mcpi);
    }
    MPI_Finalize();
    return 0;
}
