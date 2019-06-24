#include "SequentialConvolution.h"


ConvolutionSeq::ConvolutionSeq(std::vector<int> input_matrix, std::vector<int> kernel_matrix, int rows, int columns, int krows, int kcolumns)
		: rows(rows),columns(columns),krows(krows), kcolumns(kcolumns)
		{

			Reset();
			input.reserve(rows*columns);
			kernel.reserve(krows*kcolumns);
			input=input_matrix;
			kernel=kernel_matrix;
		}

void ConvolutionSeq::Reset(){
	output.resize(rows*columns,0);
}

void ConvolutionSeq::Compute(){
	int index1, index2, a, b;
	std::cout<<"sequential version 0.5 convolution d'une matrice 4000*4000 avec un kernel 5*5... ....."<<std::endl;
	stopwatch sw;
	sw.reset();
	sw.start();

	for(int x=0;x<rows;++x){
		for(int y=0;y<columns;++y){

			for(int i=0;i<krows;++i){
				for(int j=0;j<kcolumns;++j){

					a=x+i-krows/2;
					b=y+j-kcolumns/2;

					if(a<0)
						index1=rows+a;
					else if(a>rows-1)
						index1=a-rows;
					else
						index1=a;

					if(b<0)
						index2=columns+b;
					else if(b>columns-1)
						index2=b-columns;
					else
						index2=b;

					output[x*columns+y]+=input[index1*columns+index2]*kernel[i*kcolumns+j];

				}
			}

		}
	}
	sw.stop();
	std::cout<<"EOF sequential version 0.5"<<std::endl;
	std::cout << "\tElapsed time: " << sw.elapsed_ms() << " ms" << std::endl;

}
void ConvolutionSeq::Print_to_File(std::ofstream &f)
{
	if(!f)
	{
		std::cout<<"Cannot open output file"<<std::endl;
		return ;
	}
	for(int i = 0; i <rows; i++){
			for(int j = 0; j < columns; j++){
				if(j!= columns-1)
					f<<output[i*columns+j]<<' ';
				else
					f<<output[i*columns+j];
			}
			f<<std::endl;
	}
	f.close();
}

ConvolutionSeq::~ConvolutionSeq() {}





