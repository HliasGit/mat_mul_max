#include "mat_mul.hpp"

int main(){

    //Initialize everything
    {
        // Initialize the MPI environment
        MPI_Init(NULL, NULL);

        // Get the number of processes
        MPI_Comm_size(MPI_COMM_WORLD, &world_size);

        // Get the rank of the process
        MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

        // Get the name of the processor
        char processor_name[MPI_MAX_PROCESSOR_NAME];
        int name_len;
        MPI_Get_processor_name(processor_name, &name_len);

        // Print off a hello world message
        //printf("Hello world from processor %s, rank %d out of %d processors\n", processor_name, world_rank, world_size);
    }

    // From here scatter and gather
    {
        clock_t start, end;
        start = clock();

        if(SIZE%world_size!=0){
            std::cout << "not possible as now" << std::endl;
        } else {
            int size_mezzi = SIZE/2;
            int vert = world_rank/(world_size/2);
            int hor = (world_rank+2)%(world_size/2);
            int start_v = vert*size_mezzi;
            int end_v = (vert+1)*size_mezzi;
            int start_h = hor*size_mezzi;
            int end_h = (hor+1)*size_mezzi;

            double buffer1[size_mezzi*size_mezzi];
            double buffer2[size_mezzi*size_mezzi];

            mat_gen(buffer1, buffer2, world_size, world_rank, 0, 4, 0, 4);
    
            MPI_Barrier(MPI_COMM_WORLD);

            MPI_Gather(buffer1, size_mezzi*size_mezzi, MPI_DOUBLE, mat1, size_mezzi*size_mezzi, MPI_DOUBLE, 0, MPI_COMM_WORLD);
        }
    
        // Recording the end clock tick.
        end = clock();

        MPI_Barrier(MPI_COMM_WORLD);
    
        // Calculating total time taken by the program.
        double time_taken_to_gen = double(end - start) / double(CLOCKS_PER_SEC);
        std::cout << "Time taken by program to generate the matrices is : "  << time_taken_to_gen << std::setprecision(5) << " sec " << std::endl;
    }

    //Do the other stuffs
    {
        
        if(world_rank == 0){
            print_mat(mat1);
            //print_mat(mat2);
            //mat_mul(mat1, mat2, res);
            //print_mat(res);
        }

        MPI_Finalize(); // Finalize the MPI environment.
    }
    return 0;
}


//Generate the two matrices splitting the work among the processes
void mat_gen(double mat1[SIZE*SIZE/4], double mat2[SIZE*SIZE/4], int world_size, int world_rank, int start_h, int end_h, int start_v, int end_v){

    printf("Hello world from processor rank %d out of %d processors\n", world_rank, world_size);


    for(int i=start_v; i<end_v; i++){
        for(int j=start_h; j<end_h; j++){
            mat1[j*SIZE/2+i] = j*SIZE/2+i;
            mat2[j*SIZE/2+i] = j*SIZE/2+i;
            //std::cout << "mat 1: " << mat1[i][j] << ", mat 2: " << mat2[i][j] << std::endl;
        }
    }
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