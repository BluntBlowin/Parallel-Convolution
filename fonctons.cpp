#include"fonctons.h"

int rows=500,cols=500;

void sequentialConvolutionSinglePass(){
int rows =10, cols =10;        //Matrix
int** matrix = new int*[rows];
for (int i = 0; i < rows; ++i)
    matrix[i] = new int[cols];
for(int i=0;i<rows;i++)
    for(int j=0;j<cols;j++)
        matrix[i][j]=1;


int rowConvol=5,colConvol=5;   //convolution mask
int **mask =new int*[rowConvol];
for (int i = 0; i < rowConvol; ++i)
    mask[i] = new int[colConvol];
for(int i=0;i<rowConvol;i++)
    for(int j=0;j<colConvol;j++)
        mask[i][j]=i+j;

int convolMatrixRows=rows-rowConvol+1,convolMatrixcols=cols-colConvol+1; //convolution product
int** ConvolMatrix = new int*[convolMatrixRows];
for (int i = 0; i < convolMatrixRows; ++i)
    ConvolMatrix[i] = new int[convolMatrixcols];


for(int i=0;i<convolMatrixRows;i++)
    for(int j=0;j<convolMatrixcols;j++)
        ConvolMatrix[i][j]=0;


int s=0;
double t1,t2;
t1=clock();

    for(int i=0;i<convolMatrixRows;i++){
       for(int j=0;j<convolMatrixcols;j++){
            for(int ik=0;ik<rowConvol;ik++){
                for(int jk=0;jk<colConvol;jk++){
                 s=s+mask[ik][jk]*matrix[i+ik][j+jk];
                }
            }
        ConvolMatrix[i][j]=s;
        s=0;
        }
    }

t2=clock();
   std::cout<<"\tend"<<std::endl;
  std::cout<<"\tTime in "<<t2-t1<<std::endl;

}


void parallelConvolutionFirstVersion(){
int rows =500, cols =500;        //Matrix
int** matrix = new int*[rows];
for (int i = 0; i < rows; ++i)
    matrix[i] = new int[cols];
for(int i=0;i<rows;i++)
    for(int j=0;j<cols;j++)
        matrix[i][j]=1;


int rowConvol=2,colConvol=2;   //convolution mask
int **mask =new int*[rowConvol];
for (int i = 0; i < rowConvol; ++i)
    mask[i] = new int[colConvol];
for(int i=0;i<rowConvol;i++)
    for(int j=0;j<colConvol;j++)
        mask[i][j]=i+j;


int convolMatrixRows=rows-rowConvol+1,convolMatrixcols=cols-colConvol+1; //convolution product
int** ConvolMatrix = new int*[convolMatrixRows];
for (int i = 0; i < convolMatrixRows; ++i)
    ConvolMatrix[i] = new int[convolMatrixcols];


for(int i=0;i<convolMatrixRows;i++)
    for(int j=0;j<convolMatrixcols;j++)
        ConvolMatrix[i][j]=0;


std::cout<<"\tbegin..."<<std::endl;
int s=0;
float t1,t2;
t1=omp_get_wtime();

    for(int i=0;i<convolMatrixRows;i++){
       for(int j=0;j<convolMatrixcols;j++){
            #pragma omp parallel for
            for(int ik=0;ik<rowConvol;ik++){
                for(int jk=0;jk<colConvol;jk++){
                 s=s+mask[ik][jk]*matrix[i+ik][j+jk];
                }
            }
        ConvolMatrix[i][j]=s;
        s=0;
        }
    }

t2=omp_get_wtime();
//    afficher(ConvolMatrix,convolMatrixRows,convolMatrixcols);
   std::cout<<"\tend"<<std::endl;
  std::cout<<"\tTime :"<<t2-t1<<std::endl;

}

// OpenMP Critical
void criticalSection(){
    int n=99;
    int *t;
    t=new int [n];
        t[150]=1562;
        t[250]=-1;


std::cout<<"chercher le Max et le Min dans la table"<<std::endl;
std::cout<<std::endl;

float t1=0,t2=0;

std::cout<<"Sequential Version"<<std::endl;
std::cout<<"\tBegin"<<std::endl;
int Min=t[0];
int Max=t[0];
t1=clock();
for(int i=1;i<n;i++){
    if(t[i]>Max) Max=t[i];
    if(t[i]<Min) Min=t[i];
}
t2=clock();
std::cout<<"\tEnd"<<std::endl;
std::cout<<"\tMax = "<<Max<<" Min= "<<Min<<std::endl;
std::cout<<"\tTime : "<<t2-t1<<std::endl;

std::cout<<"Paralle Version with critical section"<<std::endl;
std::cout<<"\tBegin"<<std::endl;
Min=t[0];
Max=t[0];
t1=clock();
#pragma omp parallel for
for(int i=1;i<n;i++){
    #pragma omp critical
       {
         if(t[i]>Max) Max=t[i];
       }
    #pragma omp critical
        {
            if(t[i]<Min) Min=t[i];
        }

}
t2=clock();
std::cout<<"\tEnd"<<std::endl;
std::cout<<"\tMax = "<<Max<<" Min= "<<Min<<std::endl;
std::cout<<"\tTime : "<<t2-t1<<std::endl;

std::cout<<std::endl<<"Calculer la somme"<<std::endl;
int somme=0;

std::cout<<"Sequential Version"<<std::endl;
std::cout<<"\tBegin"<<std::endl;

t1=clock();
for(int i=0;i<n;i++){
   somme=somme+t[i];
}
t2=clock();
std::cout<<"\tEnd"<<std::endl;
std::cout<<"\tSomme= "<<somme<<std::endl;
std::cout<<"\tTime : "<<t2-t1<<std::endl;

std::cout<<"Paraller Version"<<std::endl;
somme=0;
std::cout<<"\tBegin"<<std::endl;
t1=clock();
#pragma omp parallel for
for(int i=0;i<n;i++){
    #pragma omp critical
        somme=somme+t[i];
}
t2=clock();
std::cout<<"\tEnd"<<std::endl;
std::cout<<"\tSomme= "<<somme<<std::endl;
std::cout<<"\tTime : "<<t2-t1<<std::endl;

std::cout<<"Effet de Barrier"<<std::endl;

int th_id, nthreads;

#pragma omp parallel private(th_id)
    {
    th_id = omp_get_thread_num();

    if ( th_id == 3 ) {
      printf("I will wait until my brothers arrive\n");
    }
    printf("Hello World from thread %d\n", th_id);

    #pragma omp barrier
    if ( th_id == 3 ) {
      printf("Hey it's thread 3\n");
    }

  }

}

// 07


