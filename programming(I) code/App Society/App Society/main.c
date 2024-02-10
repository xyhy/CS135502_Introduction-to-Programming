//
//  main.c
//  App Society
//
//  Created by 顏浩昀 on 2019/11/26.
//  Copyright © 2019 顏浩昀. All rights reserved.
//

#include <stdio.h>
#include <string.h>
int age[1001] = {0};
int grade[1001] = {0};
char name[1001][10] = {'\0'};
void swap(int a, int b){
    int tmp_age, tmp_grade;
    char tmp_name[10] = {'\0'};
        tmp_age = age[a];
        age[a] = age[b];
        age[b] = tmp_age; // swap age
        tmp_grade = grade[a];
        grade[a] = grade[b];
        grade[b] = tmp_grade; // swap grade
        strcpy(tmp_name, name[a]);
        strcpy(name[a], name[b]);
        strcpy(name[b], tmp_name); // swap name
}
int main() {
    int n = 0, f = 0;
    scanf("%d %d", &n, &f);
    for(int i = 0; i < n; i++){
        scanf("%s %d %d", name[i], &grade[i], &age[i]);
    }
    for(int j = 0; j < n; j++){
        for(int k = j+1; k < n; k++){
            if(grade[k] < grade[j])
                swap(j, k);
            else if(grade[k] == grade[j]){
                if(age[k] > age[j])
                    swap(j, k);
                else if(age[k] == age[j]){
                    if(strcmp(name[j], name[k]) < 0)
                        swap(j, k);
                }
            }
        }
    }
    for(int w = 0; w < f; w++){
        printf("%s\n", name[w]);
    }
    return 0;
}
