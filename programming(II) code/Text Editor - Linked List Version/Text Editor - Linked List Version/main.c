//
//  main.c
//  Text Editor - Linked List Version
//
//  Created by 顏浩昀 on 2020/3/9.
//  Copyright © 2020 顏浩昀. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    char letter;
    struct node *prev;
    struct node *next;
} Node;

Node* CreateNewNode(char c){
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->letter = c;
    return newNode;
}

int main() {
    int time = 0;
    scanf("%d", &time);
    while (time--) {
        int len = 0;
        Node *head = CreateNewNode('\0');
        Node *cursor;
        Node *tail = CreateNewNode('\0');
        head->prev = NULL;
        head->next = tail;
        tail->prev = head;
        tail->next = NULL;
        cursor = head;
        scanf(" %d", &len);
        while (len--) {
            char c;
            scanf(" %c", &c);
            if(c == 'L'){
                if(cursor == head) continue;
                cursor = (cursor->prev);
            }else if(c == 'R'){
                if(cursor->next == tail) continue;
                cursor = (cursor->next);
            }else if(c == 'B'){
                if(cursor == head) continue;
                Node *tmp_cur = cursor;
                cursor->prev->next = cursor->next;
                cursor->next->prev = cursor->prev;
                cursor = cursor->prev;
                free(tmp_cur);
            }else{
                Node *insert = CreateNewNode(c);
                insert->next = cursor->next;
                insert->prev = cursor;
                cursor->next->prev = insert;
                cursor->next = insert;
                cursor = insert;
            }
        }
        cursor = head->next;
        while (cursor != tail) {
            printf("%c", cursor->letter);
            cursor = cursor->next;
            free(cursor->prev);
        }
        printf("\n");
    }
    return 0;
}
