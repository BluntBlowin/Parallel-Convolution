
#include"fonctons.h"
#include "seq_main.h"
#include "main_omp.h"
int main()
{
sequentialConvolutionSinglePass(); //convolution Version 0 --Sequential Version dans : code source dans "fonctons.cpp"
seq_main();         //convolution Version 0.5 --Sequential Version amelior�e         :  code source dans "SeequentialCnvolution.cpp"
main_omp();         //convolution Version 2 --some amelioration of the Version 1     : code source dans "Conv_omp.cpp"

firstVersion();     //convolution Version 1 --Parallel                               : code source dans "finalVersion.cpp"
finalParallelVersion(); //convolution Version 3 --Parallel                           : code source dans "finalVersion.cpp"
}

/*
la fonction seq_main() et main_omp a besoin de configurer CodeBlocks pour que l'instruction typedef std::chrono::high_resolution_clock clock; marche bien

    firstVersion() pr�sente une premiere version parallele de la convolution ou nous avons d�couper la matrice
en lignes ,le premier thread execute le premier quart de lignes et ainsi de suite
cette version permet d'arriver � une convolution deux fois plus rapide que la version s�quentielle.

    main_omp() est une petite am�liration   de firstVersion().

    Dans la derniere verision nous avons d�coup� notre matrice initiale en autant de sous-matrices que la taille de la
matrice finale,et nous avons appliqu� la convolution sur toutes ces sous matrices en parallele
cela augmente l'espace m�moire beaucoup mais cela diminu 4 quatre fois le temps n�cessaire de calcul.
*/


