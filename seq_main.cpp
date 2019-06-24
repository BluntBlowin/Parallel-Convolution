#include "SequentialConvolution.h"

int seq_main(){
    int rows=4000;
	int columns=4000;
	int krows=5;
	int kcolumns=5;
	char *inputm="data/inputs/input_4001_2001.txt";
	char *kernel="data/kernels/kernel_5.txt";
	char *outputm="data/output.txt";



	if( krows%2==0 || kcolumns%2==0)
	{
		std::cerr<<"Number of kernel rows and columns must be odd"<<std::endl;
		return 1;
	}


//================================ lecture from the file ============================
	/* INPUT MATRIX */

	std::ifstream matrixfile(inputm,std::ios::in);
	if(!matrixfile)
	{
		std::cerr<<"Impossible to read input matrix"<<std::endl;
		return 1;
	}
	std::vector<int> inputmatrix(rows*columns);

	for(int i = 0; i < rows; ++i){
			for(int j = 0; j < columns; ++j){
				matrixfile>>inputmatrix[i*columns+j];
			}
	}
	matrixfile.close();

	/* KERNEL */

	std::ifstream kernelfile(kernel,std::ios::in);
	if(!kernelfile)
	{
		std::cerr<<"Impossible to read kernel"<<std::endl;
		return 1;
	}
	std::vector<int> kernelmatrix(krows*kcolumns);
	for(int i = 0; i < krows; ++i){
			for(int j = 0; j < kcolumns; ++j){
				kernelfile>>kernelmatrix[i*kcolumns+j];
			}
	}
	kernelfile.close();
	std::ofstream outputfile(outputm,std::ios::out);
//============ LECTURE END ============================================


//      Sequential Version

	ConvolutionSeq C(inputmatrix,kernelmatrix, rows, columns, krows, kcolumns);
	C.Compute();
	C.Print_to_File(outputfile);
	outputfile.close();
	return 0;
}
