/*2D c o n v o l u t i o n on e ac h p l an e */
 void twoPassConv ( float ***A , float ***B , float *k, int planeId , int rows , int cols ) {
 // horizontal pass
#pragma omp parallel for
for (int i = 2 ; i <rows −2; i ++) {
	#pragma simd
	for (int j = 2 ; j <cols −2; j ++ ) {
		B[ planeId ] [ i ] [ j ] =  A[ planeId ] [ i ] [ j −2] *k [ 0 ] +
									A[ planeId ] [ i ] [ j −1] *k [ 1 ] +
									A[ planeId ] [ i ] [ j ] *k [ 2 ] +
									A[ planeId ] [ i ] [ j +1 ] *k [ 3 ] +
									A[ planeId ] [ i ] [ j +2 ] *k [ 4 ] ;						
	}
 }
 // vertical pass
 #pragma omp parallel for
 for (int i = 2 ; i <rows −2; i ++) {
	#pragma simd
	for (int j = 2 ; j <cols−2; j ++ ) {
		A[ planeId] [ i ] [ j ] = 	B [ planeId ] [ i −2] [ j ] *k [ 0 ] +
									B [ planeId ] [ i −1] [ j ] *k [ 1 ] +
									B [ planeId ] [ i ] [ j ] *k [ 2 ] +
									B [ planeId ] [ i + 1 ] [ j ] *k [ 3 ] +
									B [ planeId ] [ i + 2 ] [ j ] *k [ 4 ] ;
	}
 }
 return ;}
 
 
 /*calls two PassConv on each plane */

 void conv ( float ***A, float ***B, float *ker ,pimae a ) {

	#pragma no vector
	for (int planeId = 0 ; planeId  <a.planes ;planeId ++ ) {
		two PassConv( A , B , ker , planeId , a.rows ,a.cols ) ;
	}
 return ;