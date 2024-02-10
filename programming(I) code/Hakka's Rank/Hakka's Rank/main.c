//
//  main.c
//  Hakka's Rank
//
//  Created by 顏浩昀 on 2019/10/14.
//  Copyright © 2019 顏浩昀. All rights reserved.
//

#include <stdio.h>


int main(){
    int N = 0;
    int rank = 1;
    scanf("%d", &N);
    int A[N];
    int backup[N];
    int r[N];
    for(int i = 0; i < N; i++){
        scanf("%d", &A[i]);
        backup[i] = A[i];
    }
    for(int a = 0; a < N; a++){
        for(int b = a; b < N; b++){
            if(A[a] > A[b]){
                int tmp;
                tmp = A[a];
                A[a] = A[b];
                A[b] = tmp;
            }
        }
    }
    for(int c = 0; c < N; c++){
        if(A[c] == A[c-1]){
            r[c] = r[c-1];
            rank +=1;
        }else{
            r[c] = rank;
            rank +=1;
        }
    }
    for(int a = 0; a < N-1; a++){
        for(int b = 0; b < N; b++){
            if(backup[a] == A[b]){
                printf("%d ", r[b]);
                break;
            }
        }
    }
    for(int c = 0; c < N; c++){
        if(backup[N-1] == A[c]){
            printf("%d\n", r[c]);
            break;
        }
    }
    return 0;
}
