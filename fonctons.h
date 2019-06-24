#include <omp.h>
#include <iostream>
#include <ctime>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>

void afficher(int **matrix,int rows,int cols);

int **convolute(int **matrix,int rows,int cols,int **mask,int rowConvol,int colConvol);


void sequentialConvolutionSinglePass();
void parallelConvolutionFirstVersion();

void criticalSection();
int finalParallelVersion();
int firstVersion();


