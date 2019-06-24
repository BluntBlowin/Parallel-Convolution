
#include <iostream>
#include <cstdint>
#include <math.h>
#include <omp.h>
#include <vector>
#include "hpc_helpers.hpp"

using namespace std;


int firstVersion(){

TIMERSTART(overall)
TIMERSTART(alloc)
const int m = 500;
const int n= 500;
const int u =5;
const int v = 5;
omp_set_num_threads(m);
int** A = new int*[m+u-1];
for(int i = 0; i < m+u-1; ++i)
A[i] = new int[n+v-1];

int** B = new int*[u];
for(int i = 0; i <u; ++i)
B[i] = new int[v];

int** D = new int*[m];
for(int i = 0; i <m; ++i)
D[i] = new int[n];

int C[m*n];

int*** TEMP = new int**[m*n];
for(int i = 0; i < m*n; ++i)
TEMP[i] = new int*[u];



for(int i = 0; i < m*n; ++i){
for(int j = 0; j < u; ++j){

TEMP[i][j] = new int[v];


}
}
int counter1 = 0;
int counter2 = 0;

for(int i = 0; i < m*n; ++i){
for(int j = 0; j < u; ++j){
for(int k = 0; k < v; ++k){
TEMP[i][j][k] = A[counter2][counter1];
counter1++;

}
counter1=0;

}
if(counter1 == v-1)
{counter2++;
}
}
TIMERSTOP(alloc)
TIMERSTART(init)
for( int row = 0; row < m+u-1; row++){
for( int col = 0; col < n+v-1; col++)
{
A[row][col] = rand() % 255 + 1;
}
}
for( int row = 0; row < u; row++){
for( int col = 0; col < v; col++)
{
B[row][col] = rand() % 255 + 1;
}
}
/* for( int row = 0; row < m; row++){
for( int col = 0; col < n; col++)
{
C[row][col] = 0;
}
}  */
for( int col = 0; col < m*n; col++)
{
C[col] = 0;
}  TIMERSTOP(init)

for(int k = 0; k < 2; k++){

TIMERSTART(mult_seq)
bool parallel = false;


#pragma omp parallel for if(parallel)
for(uint64_t i = 0; i < m; i++){
for(uint64_t j = 0; j < n; j++){
for(uint64_t row = 0; row < u; row++){
for(uint64_t col = 0; col < v; col++){
D[i+j] += A[i+row][j+col] * B[row][col];
}
}
}
}
TIMERSTOP(mult_seq)
}

for(int k = 0; k < 2; k++){
int pl = m;
TIMERSTART(mult_par)
bool parallel = true;

#pragma omp parallel
{
for(uint64_t i = 0; i < u; i++){
for(uint64_t j = 0; j < v; j++){

C[omp_get_thread_num()] += TEMP[omp_get_thread_num()][i][j] * B[i][j];

}
}
}/*
#pragma omp parallel for if(parallel)
for(int i = 0; i < m; i++){
for(int j = 0; j < n; j++){
for(int row = 0; row < u; row++){
for(int col = 0; col < v; col++){
C[i][j] += A[i+row][j+col] * B[row][col];
}
}
}
}*/
TIMERSTOP(mult_par)
}

TIMERSTOP(overall)


}


int finalParallelVersion(){

TIMERSTART(overall)
TIMERSTART(alloc)
const int m = 100;
const int n= 100;
const int u =5;
const int v = 5;
omp_set_num_threads(m);
int** A = new int*[m+u-1];
for(int i = 0; i < m+u-1; ++i)
A[i] = new int[n+v-1];

int** B = new int*[u];
for(int i = 0; i <u; ++i)
B[i] = new int[v];

int** D = new int*[m];
for(int i = 0; i <m; ++i)
D[i] = new int[n];

int C[m*n];

int*** TEMP = new int**[m*n];
for(int i = 0; i < m*n; ++i)
TEMP[i] = new int*[u];



for(int i = 0; i < m*n; ++i){
for(int j = 0; j < u; ++j){

TEMP[i][j] = new int[v];


}
}
int counter1 = 0;
int counter2 = 0;

for(int i = 0; i < m*n; ++i){
for(int j = 0; j < u; ++j){
for(int k = 0; k < v; ++k){
TEMP[i][j][k] = A[counter2][counter1];
counter1++;

}
counter1=0;

}
if(counter1 == v-1)
{counter2++;
}
}
TIMERSTOP(alloc)
TIMERSTART(init)
for( int row = 0; row < m+u-1; row++){
for( int col = 0; col < n+v-1; col++)
{
A[row][col] = rand() % 255 + 1;
}
}
for( int row = 0; row < u; row++){
for( int col = 0; col < v; col++)
{
B[row][col] = rand() % 255 + 1;
}
}
/* for( int row = 0; row < m; row++){
for( int col = 0; col < n; col++)
{
C[row][col] = 0;
}
}  */
for( int col = 0; col < m*n; col++)
{
C[col] = 0;
}  TIMERSTOP(init)

for(int k = 0; k < 2; k++){

TIMERSTART(mult_seq)
bool parallel = false;


#pragma omp parallel for if(parallel)
for(uint64_t i = 0; i < m; i++){
for(uint64_t j = 0; j < n; j++){
for(uint64_t row = 0; row < u; row++){
for(uint64_t col = 0; col < v; col++){
D[i+j] += A[i+row][j+col] * B[row][col];
}
}
}
}
TIMERSTOP(mult_seq)
}

for(int k = 0; k < 2; k++){
int pl = m;
TIMERSTART(mult_par)
bool parallel = true;

#pragma omp parallel
{
for(uint64_t i = 0; i < u; i++){
for(uint64_t j = 0; j < v; j++){

C[omp_get_thread_num()] += TEMP[omp_get_thread_num()][i][j] * B[i][j];

}
}
}/*
#pragma omp parallel for if(parallel)
for(int i = 0; i < m; i++){
for(int j = 0; j < n; j++){
for(int row = 0; row < u; row++){
for(int col = 0; col < v; col++){
C[i][j] += A[i+row][j+col] * B[row][col];
}
}
}
}*/
TIMERSTOP(mult_par)
}

TIMERSTOP(overall)


}
