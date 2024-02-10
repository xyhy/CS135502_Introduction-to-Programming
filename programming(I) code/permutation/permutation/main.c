//
//  main.c
//  permutation
//
//  Created by 顏浩昀 on 2019/11/4.
//  Copyright © 2019 顏浩昀. All rights reserved.
//

#include <stdio.h>

char list[10];

void show(int n)
{
    int i;
    printf("(%c", list[0]);
    for (i=1; i<n; i++) {
        printf(",%c", list[i]);
    }
    printf(")\n");
}

void Swap(int k, int i)
{
    char tmp;
    tmp = list[k];
    list[k] = list[i];
    list[i] = tmp;
}

void Perm(int k, int n)
{
    if(k == n){
        show(n);
    }else{
        for(int x = k; x<n; x++){
            Swap(x, k);
            Perm(k+1, n);
            Swap(x, k);
        }
    }
}

int main(void)
{
    int num, i;
    scanf("%d", &num);
    for(i=0; i<num; i++)
        list[i] = '1'+i;
    Perm(0, num);
    return 0;
}
