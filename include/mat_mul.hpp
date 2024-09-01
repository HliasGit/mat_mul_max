#ifndef MAT_MUL_H

    #define MAT_MUL_H

    #include <iostream>
    #include <stdlib.h>
    #include <mpi.h>
    #include <stdio.h>
    #include <bits/stdc++.h>

    #define SIZE 8

    void mat_gen(double mat1[SIZE][SIZE], double mat2[SIZE][SIZE], int world_size, int world_rank);
    void mat_mul(double mat1[SIZE][SIZE], double mat2[SIZE][SIZE], double res[SIZE][SIZE]);
    void print_mat(double res[SIZE][SIZE]);
    
#endif //MAT_MUL_H