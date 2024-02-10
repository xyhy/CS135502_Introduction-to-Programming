#ifndef FUNCTION_H
#define FUNCTION_H

void execInst(int *ptrArr[], char inst, int param1, int param2){
    if(inst == 'P'){
        ptrArr[param1] = ptrArr[param2];
    }else if(inst == 'S'){
        *ptrArr[param1] = param2;
    }
}

#endif
