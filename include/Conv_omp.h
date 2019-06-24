#ifndef CONV_OMP_H
#define CONV_OMP_H

#include<iostream>
#include<vector>
#include<fstream>
#include "stopwatch.h"
class Conv_omp
{
    public:
        Conv_omp(std::vector<int> input_matrix, std::vector<int> kernel_matrix, int rows, int columns, int krows, int kcolumns);
        ~Conv_omp();
        void Reset();
        void Compute();
        void Print_to_File(std::ofstream &f);

    protected:
    private:
        std::vector<int> input;	   //input matrix
		std::vector<int> kernel;  //kernel matrix
		std::vector<int> output; //convolution product
		int rows;
		int columns;
		int krows;
		int kcolumns;
};

#endif // CONV_OMP_H
