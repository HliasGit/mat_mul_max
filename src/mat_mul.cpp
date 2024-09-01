#include "mat_mul.hpp"

int main(){

    // Initialize the MPI environment
    MPI_Init(NULL, NULL);

    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // Get the name of the processor
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);

    // Print off a hello world message
    printf("Hello world from processor %s, rank %d out of %d processors\n",
           processor_name, world_rank, world_size);

    double mat1[SIZE][SIZE], mat2[SIZE][SIZE], res[SIZE][SIZE];

    mat_gen(mat1, mat2, world_size, world_rank);
    
    if(world_rank == 0){
        print_mat(mat1);
        print_mat(mat2);

        //mat_mul(mat1, mat2, res);

        //print_mat(res);
    }

    // Finalize the MPI environment.
    MPI_Finalize();
    
    return 0;

}

void mat_gen(double mat1[SIZE][SIZE], double mat2[SIZE][SIZE], int world_size, int world_rank){
    clock_t start, end;
 
    /* Recording the starting clock tick.*/
    start = clock();

    if(SIZE%world_size!=0){
        std::cout << "not possible as now" << std::endl;
    } else {

        int size_mezzi = SIZE/2;

        int vert = world_rank/(world_size/2);
        int hor = (world_rank+2)%(world_size/2);

        for(int i=vert*size_mezzi; i<(vert+1)*size_mezzi; i++){
            for(int j=hor*size_mezzi; j<(hor+1)*size_mezzi; j++){
                mat1[i][j] = rand() % 1000;
                mat2[i][j] = rand() % 1000;
                //std::cout << "mat 1: " << mat1[i][j] << ", mat 2: " << mat2[i][j] << std::endl;
            }
        }
    }

 
 
    // Recording the end clock tick.
    end = clock();

    MPI_Barrier(MPI_COMM_WORLD);
 
    // Calculating total time taken by the program.
    double time_taken_to_gen = double(end - start) / double(CLOCKS_PER_SEC);
    std::cout << "Time taken by program to generate the matrices is : "  << time_taken_to_gen << std::setprecision(5) << " sec " << std::endl;
    
}

void mat_mul(double mat1[SIZE][SIZE], double mat2[SIZE][SIZE], double res[SIZE][SIZE]){
    double sum;
    clock_t start, end;

    start = clock();

    for(int i=0; i<SIZE; i++){
        for(int j=0; j<SIZE; j++){
            for(int k=0; k<SIZE; k++){
                res[i][j] += mat1[i][k]*mat2[k][j];
            }
        }
    }

    // Recording the end clock tick.
    end = clock();
 
    // Calculating total time taken by the program.
    double time_taken_to_solve = double(end - start) / double(CLOCKS_PER_SEC);
    std::cout << "Time taken by program to solve the matrices is : "  << time_taken_to_solve << std::setprecision(5) << " sec " << std::endl;
    
}

void print_mat(double res[SIZE][SIZE]){
    clock_t start, end;
 
    /* Recording the starting clock tick.*/
    start = clock();

    std::cout << "res mat:" << std::endl;

    for(int i=0; i<SIZE; i++){
        for(int j=0; j<SIZE; j++){
            std::cout << res[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
 
    // Recording the end clock tick.
    end = clock();
 
    // Calculating total time taken by the program.
    double time_taken_to_print = double(end - start) / double(CLOCKS_PER_SEC);
    std::cout << "Time taken by program to print the matrix is : "  << time_taken_to_print << std::setprecision(5) << " sec " << std::endl;
    
}