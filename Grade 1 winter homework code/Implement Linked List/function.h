#include <stdio.h>
#include <stdlib.h>
typedef struct _Node {
    int data;
    struct _Node *next;
} Node;

Node* Create_Node(int x){
    Node* new_node = (Node*) malloc(sizeof(Node));
    new_node->data = x;
    new_node->next = NULL;
    return new_node;
}

Node* createList(int *a, int size){
    Node* head = NULL;
    Node* tail = NULL;
    int i = 0;
    for(;i < size; i++){
        Node* newnode = Create_Node(a[i]);
        if(i == 0){
            head = newnode;
            tail = newnode;
        }else if (i == 1){
            head->next = newnode;
            tail->next = newnode;
            tail = newnode;
        }
        tail->next = newnode;
        tail = newnode;
    }
    return head;
}
void push_front(Node** head, int val){
    Node* new_head = Create_Node(val);
    new_head->next = *head;
    *head = new_head;
}
void deleteElementByIdx(Node** head, int idx){
    if(*head == NULL) return;
    if(idx == 0){
        *head = (*head)->next;
        return;
    }
    Node* pre_ptr = NULL;
    Node* now_ptr = *head;
    int index = 0;
    while(index != idx){
        if(now_ptr == NULL) return;
        pre_ptr = now_ptr;
        now_ptr = now_ptr->next;
        index++;
    }
    pre_ptr->next = now_ptr->next;   // 接到要刪的後面一個.
}
Node* copyList(Node* head){
    Node* copy_head = Create_Node(head->data);
    Node* pre_ptr = copy_head;
    Node* now_ptr = head->next;  //point to next node.
    while (now_ptr != NULL) {
        Node* newnode = Create_Node(now_ptr->data);
        pre_ptr->next = newnode;
        pre_ptr = newnode;
        now_ptr = now_ptr->next; // point to next node's next.
    }
    return copy_head;
}
void SwapElementByIdx(Node** head, int idx1, int idx2){
    if(idx1 == idx2) return;
    Node* now_ptr = *head;
    Node* node_1 = NULL;
    Node* node_2 = NULL;
    int found = 0; // idx1 && idx2 exist iff found is 2.
    int index = 0; // now index position.
    while(found != 2){
        if(now_ptr == NULL) return;
        if(index == idx1){
            node_1 = now_ptr;
            found++;
        }
        if(index == idx2){
            node_2 = now_ptr;
            found++;
        }
        now_ptr = now_ptr->next;
        index++;
    }
    // swap.
    int tmp = node_1->data;
    node_1->data = node_2->data;
    node_2->data = tmp;
}
