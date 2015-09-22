//  mpi sequence scanning
//	(c) 2015 Maulana Rizal Ibrahim <maulanarizalibrahim@gmail.com>


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

int main(void)
{
int p, size, rank;		// mpi declaration
char *X, *Y;			// sequence's length
short int ***c_out;		// score matrix
char ***b_out;
int m;					// row
int n;					// column
short int **c;			// length matrix
char **b;				// direction matrix
int diag, left, up;
int h, i, j;

MPI_Status status;
MPI_Init(NULL, NULL);
MPI_Comm_size(MPI_COMM_WORLD, &size);
MPI_Comm_rank(MPI_COMM_WORLD, &rank);


if(rank == 0){
	scanf("%d", &m);
	scanf("%d", &n);
	X = malloc((m+1) * sizeof(char *));
	Y = malloc((n+1) * sizeof(char *));
	scanf("%s", X);
	scanf("%s", Y);
	m = strlen(X);
	n = strlen(Y);
	c = malloc((m+1) * sizeof(short int *));
	b = malloc((m+1) * sizeof(char *));
	for(i = 0; i <= m; i++){
		c[i] = malloc((n+1) * sizeof(short int));
		b[i] = calloc(n+1, sizeof(char));
	}
	for (p = 1; p<size; p++){
		MPI_Send(&m, 1, MPI_INT, p, 0, MPI_COMM_WORLD);
		MPI_Send(&n, 1, MPI_INT, p, 1, MPI_COMM_WORLD);
		MPI_Send(X, m+1, MPI_CHAR, p, 2, MPI_COMM_WORLD);
		MPI_Send(Y, n+1, MPI_CHAR, p, 3, MPI_COMM_WORLD);
	}
} else
{
	MPI_Recv(&m, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
	MPI_Recv(&n, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
	int jlast, jfirst;
	jfirst = rank * n/size + 1;
	jlast  = (rank+1) * n/size;
	X = calloc(m+1,  sizeof(char));
	Y = calloc(n+1,  sizeof(char));
	MPI_Recv(X, m+1, MPI_CHAR, 0, 2, MPI_COMM_WORLD, &status);
	MPI_Recv(Y, n+1, MPI_CHAR, 0, 3, MPI_COMM_WORLD, &status);
	printf("processor %d punya X = %s\n", rank, X);
}

MPI_Barrier(MPI_COMM_WORLD);

int jlast, jfirst;
jfirst = rank * n/size + 1;
jlast  = (rank+1) * n/size;
printf("processor %d punya n = %d\n", rank, n);
printf("processor %d punya jfirst dan jlast = %d %d\n", rank, jfirst, jlast);
printf("processor %d punya X = %s\n", rank, X);
MPI_Finalize();
}
