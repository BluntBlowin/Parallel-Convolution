/*#include <iostream>
#include <omp.h>
#include <cstdlib>

using namespace std;

int main(){
    int n = 10000000;
    int* A = new int[n];
    int sum = 0;
    double wtime = 0.0;
    for(int i = 0; i < n; i++){
        A[i] = rand() % 255 +1;
    }
    for(int i=0; i<1;i++){
    wtime = omp_get_wtime();
    for(int i = 0; i<n;i++){
        sum+= A[i];
    }
    wtime = omp_get_wtime() - wtime;
    cout << "Temps serie: " << wtime << endl;
    }
    for(int i=0; i<1;i++){
    wtime = omp_get_wtime();
    #pragma omp parallel
    {
    int ID = omp_get_thread_num();
    #pragma omp for
    for(int i = 0; i<n/4;i++){
        #pragma omp critical
        {
        sum+= A[ID*n/4 + i];
        }
    }

    }
    wtime = omp_get_wtime() - wtime;
    cout << "Temps parallele avec section critique: " << wtime << endl;    }
    for(int i=0; i<1;i++){
    wtime = omp_get_wtime();
    cout << "All threads started at : " << wtime << endl;
    #pragma omp parallel
    {
    int ID = omp_get_thread_num();
    #pragma omp for
    for(int i = 0; i<n/4;i++){
        sum+= A[ID*n/4 + i];
    }
    #pragma omp critical
    {
        cout << "Thread " << ID << " arrived after " << omp_get_wtime() - wtime <<endl;
    }
    #pragma omp barrier

    }

    }
    for(int i=0; i<1;i++){
    wtime = omp_get_wtime();
    #pragma omp parallel
    {
    int ID = omp_get_thread_num();
    #pragma omp for nowait
    for(int i = 0; i<n/4;i++){
        sum+= A[ID*n/4 + i];
    }
    }
    wtime = omp_get_wtime() - wtime;
    cout << "Temps parallele sans synchro: " << wtime << endl;
    }

}
*/
