#ifndef FUNCTION_H
#define FUNCTION_H

#define COLUMN 5
void sortArray(int R, int (*array)[COLUMN]){
    for(int k = 0; k < R; k++){
        for(int i = 0; i<COLUMN-1; i++){
            for(int j = 0; j<COLUMN-1-i; j++){
                if((array[k][j]) > (array[k][j+1]) ){
                    int tmp;
                    tmp = (array[k][j]);
                    (array[k][j]) = (array[k][j+1]);
                    (array[k][j+1]) = tmp;
                }
            }
        }
    }
}

#endif
