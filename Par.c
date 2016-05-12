#include <stdio.h> 
#include <math.h> 
#include <mpi.h> 
#include <stdlib.h> 

double mat_mult_vector(double *a_local, double *x, double *temp_local, int n, int n_local) 
{ 
int i,j; 
for (i=0; i<n_local; i++) 
{ 
temp_local[i] = 0.0; 
} 

for (i=0; i<n_local; i++) 
{ 
for (j=0; j<n; j++) 
{ 
temp_local[i] += a_local[i*n+j] * x[j]; 
} 
} 
} 

void vector_sub(double *temp_local, double *b_local, int n_local) 
{ 
int i; 
for (i=0; i< n_local; i++) 
{ 
temp_local[i] -= b_local[i]; 
} 
} 

void vector_mult_scalar(double *temp_local, double t, int n_local) 
{ 
int i; 
for (i=0; i < n_local; i++) 
{ 
temp_local[i] *= t; 
} 
} 

double vector_norm(double *temp_local, int n_local) 
{ 
int i; 
double res= 0.0; 
for (i = 0; i<n_local; i++) 
{ 
res += temp_local[i] * temp_local[i]; 
} 
double rec; 
MPI_Allreduce(&res, &rec, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD); 
return sqrt(rec); 
} 

int main(int argc, char *argv[]) 
{ 
int size, rank; 
MPI_INIT(&argc, &argv); 
MPI_Comm_size(MPI_COMM_WORLD, &size); 
MPI_Comm_rank(MPI_COMM_WORLD, &rank); 

double begin, end; 

const int n = atoi(argv[1]); 

double *a = (double *)malloc(n*n*sizeof(double)); 
double *b = (double *)malloc(n*sizeof(double)); 
double *x = (double *)malloc(n*sizeof(double)); 

begin = MPI_Wtime(); 

int sign = atoi(argv[2]); 

const double t = (sign == 0) ? 0.00001 : -0.00001; 
const double e = 0.00001; 

int n_local = n / size; 

if (rank == 0) 
{ 
int i; 
int j; 
for (i=0; i<n; i++) 
{ 
for (j=0; j<n; j++) 
{ 
a[i*n+j] = (i==j) ? 2.0 : 1.0; 
} 

b[i] = (double) n+1; 
x[i] = 0.0; 
} 
} 

double *a_local = (double *)malloc(n_local*n*sizeof(double)); 
double *temp_local = (double *)malloc(n_local*sizeof(double)); 
double *b_local = (double *)malloc(n_local*sizeof(double)); 
double *x_local = (double *)malloc(n_local*sizeof(double)); 

MPI_Bcast(b, n, MPI_DOUBLE, 0, MPI_COMM_WORLD); 

MPI_Bcast(x, n, MPI_DOUBLE, 0, MPI_COMM_WORLD); 

MPI_Scatter(a, n_local*n, MPI_DOUBLE, a_local, n_local*n, MPI_DOUBLE, 0, MPI_COMM_WORLD); 

double b_norm = vector_norm(b_local, n_local); 
double temp_norm = 0.0; 
do 
{ 
mat_mult_vector(a_local, x, temp_local, n, n_local); 
vector_sub(temp_local, b_local, n_local); 
temp_norm = vector_norm(temp_local, n_local); 
vector_mult_scalar(temp_local, t, n_local); 
vector_sub(x_local, temp_local, n_local); 
MPI_Allgather(x_local, n_local, MPI_DOUBLE, x, n_local, MPI_DOUBLE, MPI_COMM_WORLD); 
} 
while ((temp_norm / b_norm) >= e); 

end = MPI_Wtime(); 

printf("time %f proc %d\n", end -begin , rank); 

free(a_local); 
free(temp_local); 
free(b_local); 
free(x_local); 
free(a); 
free(b); 
free(x); 
MPI_Finalize();
