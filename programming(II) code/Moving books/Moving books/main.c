//
//  main.c
//  Moving books
//
//  Created by 顏浩昀 on 2020/3/24.
//  Copyright © 2020 顏浩昀. All rights reserved.
//

#include <stdio.h>
#include <string.h>

int table_and_book[25][25] = {0};
int address[25] = {0};

void sendbook(int book, int destination){
    int i;
    for(i = 0; table_and_book[destination][i] != -1; i++){} // the empty of destination table.
    table_and_book[destination][i] = book;
    table_and_book[address[book]/100][address[book]%100] = -1;
    address[book] = destination*100 + i;
}
void returnTOtable(int book){
    for(int i = book+1; );
}

void moveAontoB(int A, int B){  // put a on b adjacent.
    returnTOtable(A);
    returnTOtable(B);
}
void moveAoverB(int A, int B){  // put a on top of b's stack.
    returnTOtable(A);
}
void pileAontoB(int A, int B){  // put a's stack on b adjcent.
    returnTOtable(B);
}
void pileAoverB(int A, int B){  // put a's stack on b's stack.
    
}

int main() {
    int books = 0;
    char op[4], op2[4];
    int a, b;
    scanf("%d", &books);
    for(int i = 0; i < books; i++){
        address[i] = i*100;
    }
    for(int i = 0; i < books; i++){
        table_and_book[i][0] = i;
        for(int j = 1; j < books; j++){
            table_and_book[i][j] = -1;
        }
    }
    while (scanf("%s", op)) {
        if(!strcmp(op, "exit")) break;
        scanf(" %d %s %d", &a, op2, &b);
        if(a == b) continue;;
        if(!strcmp(op, "move") && !strcmp(op2, "onto"))
            moveAontoB(a, b);
        if(!strcmp(op, "move") && !strcmp(op2, "over"))
            moveAoverB(a, b);
        if(!strcmp(op, "pile") && !strcmp(op2, "onto"))
            pileAontoB(a, b);
        if(!strcmp(op, "pile") && !strcmp(op2, "over"))
            pileAoverB(a, b);
    }
    return 0;
}
