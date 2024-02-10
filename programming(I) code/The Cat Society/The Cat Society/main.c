//
//  main.c
//  The Cat Society
//
//  Created by 顏浩昀 on 2020/1/3.
//  Copyright © 2020 顏浩昀. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct struct_cat{
    char name[30];
    int occupation;
    int age;
}cat;

int compare(const void* a, const void* b){
    cat A = *(cat*)a;
    cat B = *(cat*)b;
    if(A.occupation == B.occupation){
        if(A.occupation == 5){
            if(A.age < B.age){
                return -1;
            }else if (A.age > B.age){
                return 1;
            }else if (A.age == B.age){
                return strcmp(A.name, B.name);
            }else{
                return 0;
            }
        }else{
            if(A.age > B.age){
                return -1;
            }else if (A.age < B.age){
                return 1;
            }else if(A.age == B.age){
                return strcmp(A.name, B.name);
            }else{
                return 0;
            }
        }
    }else if (A.occupation < B.occupation){
        return -1;
    }else if(A.occupation > B.occupation){
        return 1;
    }else{
        return 0;
    }
}

int main(){
    int n = 0, m = 0;
    cat CAT[10050];
    while(~scanf("%d %d", &n, &m)){
        for(int i = 0; i<n; i++){
            char temp_occupation[20];
            scanf("%s %s %d", CAT[i].name, temp_occupation, &(CAT[i].age));
            if(temp_occupation[0] == 'e')
                CAT[i].occupation = 1;
            else if (temp_occupation[0] == 'n')
                CAT[i].occupation = 2;
            else if (temp_occupation[0] == 'k')
                CAT[i].occupation = 3;
            else if (temp_occupation[0] == 'w')
                CAT[i].occupation = 4;
            else if (temp_occupation[0] == 'a')
                CAT[i].occupation = 5;
            else if (temp_occupation[0] == 'm')
                CAT[i].occupation = 6;
            else if (temp_occupation[0] == 'd')
                CAT[i].occupation = 7;
            else if (temp_occupation[0] == 'l')
                CAT[i].occupation = 8;
        }
        qsort(CAT, n, sizeof(cat), compare);
        for(int j = 0; j<m && j<n; j++){
            printf("%s\n", CAT[j].name);
        }
    }
    return 0;
}
