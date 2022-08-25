#include <stdio.h>
#include <stdlib.h>

#ifdef _OPENMP
    #include <omp.h>
#else
    #define omp_get_thread_num() 0
#endif

int main(int argc, char **argv) {
    int i, n=16, chunk, a[n], suma=0;
    
    if(argc < 2)
    {
        fprintf(stderr,"\nFalta el tamaÃ±o de chunk\n");
        exit(-1);
    }

    chunk = atoi(argv[1]); 

    for (i=0; i<n; i++)
        a[i] = i;
 
    #pragma omp parallel 
    {
        #pragma omp for firstprivate(suma) \
                lastprivate(suma) schedule(guided,chunk)
            for (i=0; i<n; i++)
            {
                suma = suma + a[i];
                printf(" thread %d suma a[%d] suma=%d \n",
                     omp_get_thread_num(),i,suma);
            }
            
            #pragma omp single 
            {
            printf("asdf: %d\n", omp_get_dynamic());
            int var = omp_get_dynamic();
            if (var > 0)
                printf("dyn-var=true --> Asignación de hebras automática\n");
            else 
                printf("dyn-var=false\n");

            omp_set_dynamic(1);

            if (var > 0)
                printf("dyn-var=true --> Asignación de hebras automática\n");
            else 
                printf("dyn-var=false\n");

            var = omp_get_max_threads();
            printf("nthreads-var=%d\n --> Número de hebras que se utilizarán",var);
            var = omp_get_thread_limit();
            printf("thread-limit-var=%d\n --> Máximo número de hebras para todos los programas",var);

            printf("Identificador de hebra: %d\n",omp_get_thread_num());
            printf("Número de hebras ejecutándose en paralelo en este momento: %d\n", omp_get_num_threads());
            printf("Sección paralela: %d\n", omp_in_parallel());
            printf("Numero de procesadores: %d\n", omp_get_num_procs());
        }
    }

    printf("Fuera de 'parallel for' suma=%d\n",suma);

}
