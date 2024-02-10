#ifndef __FUNCTION_H__
#define __FUNCTION_H__
typedef struct _Node{
    int size;
    int* data;
    struct _Node* next;
} Node;

Node* ReadOneList(){
    Node* cardstack = (Node*)malloc(sizeof(Node));
    scanf(" %d:", &(cardstack->size));
    cardstack->data = (int*)malloc(sizeof(int) * (cardstack->size));
    for(int i = 0; i < cardstack->size; i++){
        scanf(" %d", ((cardstack->data)+i));
    }
    cardstack->next = NULL;
    return cardstack;
}

void PrintList(Node* head){
    Node* print = head->next;
    while (print != NULL) {
        printf("%d", *(print->data));
        for(int i = 1; i < print->size; i++){
            printf(" %d", print->data[i]);
        }
        printf("\n");
        free(head);
        head = print;
        print = print->next;
    }
}

void Merge(Node* head, int a, int b){
    Node* search = head;
    Node* add = head;
    Node* tmp = head;
    while (a--)
        search = search->next;
    while (b--)
        add = add->next;
    while (tmp->next != search)
        tmp = tmp->next;
    int addsize = search->size;
    add->data = (int*)realloc(add->data, sizeof(int) * ((add->size)+addsize));
    for(int i = 0; i < addsize; i++){
        add->data[add->size+i] = search->data[i];
    }
    add->size += addsize;
    tmp->next = search->next;
    free(search);
}

void Cut(Node* head, int a, int b){
    Node* tmp = head;
    while(a--){
        tmp = tmp->next;
    }
    Node* newnode = (Node*)malloc(sizeof(Node));
    newnode->size = (tmp->size) - b;
    newnode->data = (int*)malloc(sizeof(int) * newnode->size);
    for(int i = 0; i < newnode->size; i++){
        newnode->data[i] = tmp->data[b+i];
    }
    tmp->size = b;
    tmp->data = (int*)realloc(tmp->data, sizeof(int) * b);
    newnode->next = tmp->next;
    tmp->next = newnode;
}

#endif
