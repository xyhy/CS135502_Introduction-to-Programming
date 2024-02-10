#include <stdlib.h>
unsigned*** new_3d_array(unsigned n,unsigned m,unsigned k){
    unsigned *a, **b, ***c;
    a =(unsigned*) malloc(n * m *k * sizeof(unsigned));
    b =(unsigned**) malloc(n * m * sizeof(unsigned*));
    c =(unsigned***) malloc(n * sizeof(unsigned**));
    for(unsigned i = 0; i < n; i++){
        c[i] = b+i*m;
        for(unsigned j = 0; j < m; j++){
            b[i*m+j] = a+(i*m+j)*k ;
        }
    }
    return c;
}
void delete_3d_array(unsigned ***arr){
    free(arr[0][0]);
    free(arr[0]);
    free(arr);
}
