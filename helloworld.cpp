#include <iostream>
#include <mpi.h>
using namespace std;

int main(int argc, char** argv) {
    // Initialize the MPI environment
    MPI_Init(NULL, NULL);

    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // Print off a hello world message
    cout << "Hello world from processor " << world_rank << " of " << world_size << endl;

    // Finalize the MPI environment.
    MPI_Finalize();
}