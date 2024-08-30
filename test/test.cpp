#include "mat_mul.hpp"
#include <gtest/gtest.h>


TEST(Mat_Mul, Identity) {
    double prova[SIZE][SIZE];
    double res[SIZE][SIZE];
    double identity[SIZE][SIZE];
    for(int i=0; i<SIZE; i++){
        for(int j=0; j<SIZE; j++){
            prova[i][j] = rand() % 1000;
            if(i==j){
                identity[i][j] = 1;
            } else {
                identity[i][j] = 0;
            };
        }
    }

    mat_mul(prova, identity, res);

    EXPECT_EQ(res, prova);
}