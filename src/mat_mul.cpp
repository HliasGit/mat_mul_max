#include "mat_mul.hpp"

int main(){

    double mat1[SIZE][SIZE], mat2[SIZE][SIZE], res[SIZE][SIZE];

    mat_gen(mat1, mat2);
    
    mat_mul(mat1, mat2, res);

    print_mat(res);
    
    
    
    
    return 0;

}

void mat_gen(double mat1[SIZE][SIZE], double mat2[SIZE][SIZE]){
    clock_t start, end;
 
    /* Recording the starting clock tick.*/
    start = clock();

    for(int i=0; i<SIZE; i++){
        for(int j=0; j<SIZE; j++){
            mat1[i][j] = rand() % 1000;
            mat2[i][j] = rand() % 1000;
            //std::cout << "mat 1: " << mat1[i][j] << ", mat 2: " << mat2[i][j] << std::endl;
        }
    }
 
    // Recording the end clock tick.
    end = clock();
 
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