/*

   This program will numerically compute the integral of

   4/(1+x*x) 

   from 0 to 1.  The value of this integral is pi -- which 
   is great since it gives us an easy way to check the answer.

*/

#include <iostream>
#include <mpi.h>
using namespace std;

int main()
{
	// Initialize the MPI environment and get rank and size
	int np, rank;
	MPI_Status status;
	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	// initialize variables
	int i, j;
	long num_steps = 100000000;
	double x, step, pi, sum = 0.0, recv_sum;
	double start_time, run_time;
	step = 1.0 / (double)num_steps;

	start_time = MPI_Wtime();
	// do the integration
	for (int i = rank; i < num_steps; i += np) {
		x = (i + 0.5) * step;
		sum += 4.0 / (1.0 + x * x);
	}	
	// accumulate results at root
	if (rank > 0) {
		MPI_Send(&sum, 1, MPI_DOUBLE, 0, rank, MPI_COMM_WORLD);
	}
	else {
		for (int p = 1; p < np; p++) {
			MPI_Recv(&recv_sum, 1, MPI_DOUBLE, p, p, MPI_COMM_WORLD, &status);
			sum += recv_sum;
		}
		pi = step * sum;
	}
	run_time = MPI_Wtime() - start_time;

	// output results
	if (rank == 0) {
		cout << "pi is " << pi
			 << ", computed by " << np
			 << " procs in " << run_time << " seconds"
			 << endl;
	}

	// Finalize the MPI environment.
	MPI_Finalize();
}
