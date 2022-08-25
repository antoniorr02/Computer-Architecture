/**
 * 
 Cláusula reductions
 *
 **/

#include <stdio.h>
#include <stdlib.h>

#ifdef _OPENMP
  #include <omp.h>
#else
   #define omp_get_thread_num() 0
#endif

/**
 * @file  reduction-clause.c 
 * @brief _Parte del código de suma paralalela_
 * @param int n=atoi(argv[1])  número de componentes a sumar
 * @return 0 upon exit success (print la suma de los componentes de un vector fuera del <tt>parallel</tt>)
 *  
 * **Objetivo**
 * 
 * El código usa:
 * 
 * - Directivas <tt>parallel, for</tt> 
 * - Cláusulas <tt>reduction default private shared </tt> 
 * - Funciones <tt>omp_get_thread_num()</tt> 
 *
 * **Compilación **
 * @code
 * gcc -O2 -fopenmp -o reduction-clause reduction-clause.c
 * @endcode
 * 
 *  **Ejecución **
 * ~~~~~~~~~~~~~~~~~~~~~
 * reduction-clause   16  (para 16 componentes a sumar)
 * ~~~~~~~~~~~~~~~~~~~~~
 * 
**/
int main(int argc, char **argv)
{ 
   int n = 0, size=7;

   #pragma omp parallel for reduction(*:n)
   for (int i=n; i<size; i++)
   {   
       n *= i;
       printf("La hebra %d multiplico i=%d\n", omp_get_thread_num(),i);
   } 

   printf("Tras 'parallel' suma=%d\n",n);
   return(0);
}
