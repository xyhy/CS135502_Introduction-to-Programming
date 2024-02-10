#ifndef FUNC_H_INCLUDED
#define FUNC_H_INCLUDED

typedef struct _Node{
    int number;
    struct _Node* next;
    struct _Node* prev;
}Node;

Node* head;
Node* cur;
Node* createList(int n){
    Node* tmp = NULL;
    for(int i = 1; i <= n; i++){
        Node* newnode = (Node*)malloc(sizeof(Node));
        newnode->number = i;
        if(i == 1){
            head = newnode;
            newnode->next = head;
            newnode->prev = head;
            tmp = head;
        }else{
            newnode->next = head;
            newnode->prev = tmp;
            head->prev = newnode;
            tmp->next = newnode;
            tmp = newnode;
        }
    }
    return head;
}
void freeList(){
    free(cur);
}
int solveJosephus(int step){
    cur = head;
    int kill = 0;
    int clockwise = 0;
    while(cur->next != cur){
        ++kill;
        if(!clockwise){
            if(kill == step){
                cur->prev->next = cur->next;
                cur->next->prev = cur->prev;
                free(cur);
                cur = cur->prev;
                kill = 0;
                clockwise = 1;
            }else{
                cur = cur->next;
            }
        }else if(clockwise){
            if(kill == step){
                cur->prev->next = cur->next;
                cur->next->prev = cur->prev;
                free(cur);
                cur = cur->next;
                kill = 0;
                clockwise = 0;
            }else{
                cur = cur->prev;
            }
        }
    }
    return cur->number;
}

#endif
