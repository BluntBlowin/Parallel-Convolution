#ifndef SEQUENTIALCONVOLUTION_H
#define SEQUENTIALCONVOLUTION_H

#include<vector>
#include<fstream>
#include <iostream>
#include "stopwatch.h"

class ConvolutionSeq
{
    	public:
		ConvolutionSeq( std::vector<int> input, std::vector<int> kernel ,  int r, int c, int kr, int kc );  //matrix,kernel,rows, columns, kernelRows,kernelColumns
		void Compute();  //Calculate convolution product
		void Reset();   //initialise matrix to 0
		void Print_to_File(std::ofstream &); //register the matrix in a file
		~ConvolutionSeq();

	private:
		std::vector<int> input;	   //input matrix
		std::vector<int> kernel;  //kernel matrix
		std::vector<int> output; //convolution product
		int rows;
		int columns;
		int krows;
		int kcolumns;
};
#endif // SEQUENTIALCONVOLUTION_H
