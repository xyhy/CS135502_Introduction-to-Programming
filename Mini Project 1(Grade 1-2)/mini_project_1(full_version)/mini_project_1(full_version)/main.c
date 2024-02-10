//
//  main.c
//  mini_project_1(full_version)
//
//  Created by 顏浩昀 on 2020/5/2.
//  Copyright © 2020 顏浩昀. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// global var
int sbcount = 0;
int reg[8] = {0};
int cur_reg = 0;
int outofreg = 0;

//define
#define MAXLEN 256
#define TBLSIZE 64
// Set PRINTERR to 1 to print error message while calling error()
// Make sure you set PRINTERR to 0 before you submit your code
#define PRINTERR 1

//lex.h

// Token types
typedef enum {
    UNKNOWN, END, ENDFILE,
    INT, ID,
    ADDSUB, MULDIV, LOGICAL,
    INCDEC, ASSIGN,
    LPAREN, RPAREN
} TokenSet;

// Test if a token matches the current token
extern int match(TokenSet token);
// Get the next token
extern void advance(void);
// Get the lexeme of the current token
extern char *getLexeme(void);


//parser.h

// Call this macro to print error message and exit the program
// This will also print where you called it in your program
#define error(errorNum) { \
    err_self(errorNum); \
}

// Error types
typedef enum {
    UNDEFINED, MISPAREN, NOTNUMID, NOTFOUND, RUNOUT, NOTLVAL, DIVZERO, SYNTAXERR, INCDECNOTID, OUTOFREG
} ErrorType;
// Structure of the symbol table
typedef struct {
    int val;
    char name[MAXLEN];
} Symbol;
// Structure of a tree node
typedef struct _Node {
    TokenSet data;
    int val;
    char lexeme[MAXLEN];
    struct _Node *left;
    struct _Node *right;
} BTNode;
// The symbol table
extern Symbol table[TBLSIZE];
// Initialize the symbol table with builtin variables
extern void initTable(void);
// Get the value of a variable
extern int getval(char *str);
// Set the value of a variable
extern int setval(char *str, int val);
// Make a new node according to token type and lexeme
extern BTNode *makeNode(TokenSet tok, const char *lexe);
// Free the syntax tree
extern void freeTree(BTNode *root);
extern BTNode *factor(void);
extern BTNode *term(void);
extern BTNode *term_tail(BTNode *left);
extern BTNode *expr(void);
extern BTNode *expr_tail(BTNode *left);
extern void statement(void);
// Print error message and exit the program
extern void err_self(ErrorType errorNum);


//codeGen.h
// Evaluate the syntax tree
extern int evaluateTree(BTNode *root);
// Print the syntax tree in prefix

//extern void printPrefix(BTNode *root);


//lex.c
static TokenSet getToken(void);
static TokenSet curToken = UNKNOWN;
static char lexeme[MAXLEN];

TokenSet getToken(void) {
    int i = 0;
    char c = '\0';

    while ((c = fgetc(stdin)) == ' ' || c == '\t');

    if (isdigit(c)) {
        lexeme[0] = c;
        c = fgetc(stdin);
        i = 1;
        while (isdigit(c) && i < MAXLEN) {
            lexeme[i] = c;
            ++i;
            c = fgetc(stdin);
        }
        ungetc(c, stdin);
        lexeme[i] = '\0';
        return INT;
    } else if (c == '+' || c == '-') {
        lexeme[0] = c;
        c = fgetc(stdin);
        if (c == lexeme[0]) {
            lexeme[1] = c;
            lexeme[2] = '\0';
            return INCDEC;
        } else {
            ungetc(c, stdin);
            lexeme[1] = '\0';
            return ADDSUB;
        }
    } else if (c == '&' || c == '|' || c == '^') {
        lexeme[0] = c;
        lexeme[1] = '\0';
        return LOGICAL;
    } else if (c == '*' || c == '/') {
        lexeme[0] = c;
        lexeme[1] = '\0';
        return MULDIV;
    } else if (c == '\n') {
        lexeme[0] = '\0';
        return END;
    } else if (c == '=') {
        strcpy(lexeme, "=");
        return ASSIGN;
    } else if (c == '(') {
        strcpy(lexeme, "(");
        return LPAREN;
    } else if (c == ')') {
        strcpy(lexeme, ")");
        return RPAREN;
    } else if (isalpha(c) || c == '_') {
        lexeme[0] = c;
        c = fgetc(stdin);
        i = 1;
        while (isalpha(c) || isdigit(c) || c == '_') {
            lexeme[i] = c;
            ++i;
            c = fgetc(stdin);
        }
        ungetc(c, stdin);
        lexeme[i] = '\0';
        return ID;
    } else if (c == EOF) {
        return ENDFILE;
    } else {
        return UNKNOWN;
    }
}

void advance(void) {
    curToken = getToken();
}

int match(TokenSet token) {
    if (curToken == UNKNOWN)
        advance();
    return token == curToken;
}

char *getLexeme(void) {
    return lexeme;
}


//parser.c
Symbol table[TBLSIZE];

void initTable(void) {
    strcpy(table[0].name, "x");
//    printf("MOV r0 [0]\n");
//    reg[0] = 1;
    strcpy(table[1].name, "y");
//    printf("MOV r1 [4]\n");
//    reg[1] = 1;
    strcpy(table[2].name, "z");
//    printf("MOV r2 [8]\n");
//    reg[2] = 1;
    sbcount = 3;
}

int getval(char *str) {
    int i = 0;

    for (i = 0; i < sbcount; i++)
        if (strcmp(str, table[i].name) == 0)
            return table[i].val;

    error(NOTFOUND);
    return 0;
}

int setval(char *str, int val) {
    int i = 0;

    for (i = 0; i < sbcount; i++) {
        if (strcmp(str, table[i].name) == 0) {
            table[i].val = val;
            return val;
        }
    }

    if (sbcount >= TBLSIZE)
        error(RUNOUT);
    
    strcpy(table[sbcount].name, str);
    table[sbcount].val = val;
    sbcount++;
    return val;
}

BTNode *makeNode(TokenSet tok, const char *lexe) {
    BTNode *node = (BTNode*)malloc(sizeof(BTNode));
    strcpy(node->lexeme, lexe);
    node->data = tok;
    node->val = 0;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void freeTree(BTNode *root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

//TO DO
// factor := INT | ADDSUB INT |
//                ID  | ADDSUB ID  |
//                INCDEC ID | ID ASSIGN expr |
//                LPAREN expr RPAREN |
//                ADDSUB LPAREN expr RPAREN |
BTNode *factor(void) {
    BTNode *retp = NULL, *left = NULL;

    if (match(INT)) {
        retp = makeNode(INT, getLexeme());
        advance();
    }else if (match(ID)) {
        left = makeNode(ID, getLexeme());
        advance();
        if (!match(ASSIGN)) {
            retp = left;
        } else {
            retp = makeNode(ASSIGN, getLexeme());
            advance();
            retp->left = left;
            retp->right = expr();
        }
    }else if(match(INCDEC)){
        retp = makeNode(INCDEC, getLexeme());
        retp->right = makeNode(INT, "1");
        advance();
        if(!match(ID)){
            error(INCDECNOTID);
        }else{
            retp->left = makeNode(ID, getLexeme());
            advance();
        }
    }else if (match(ADDSUB)) {
        retp = makeNode(ADDSUB, getLexeme());
        retp->left = makeNode(INT, "0");
        advance();
        if (match(INT)) {
            retp->right = makeNode(INT, getLexeme());
            advance();
        } else if (match(ID)) {
            retp->right = makeNode(ID, getLexeme());
            advance();
        } else if (match(LPAREN)) {
            advance();
            retp->right = expr();
            if (match(RPAREN))
                advance();
            else
                error(MISPAREN);
        } else {
            error(NOTNUMID);
        }
    } else if (match(LPAREN)) {
        advance();
        retp = expr();
        if (match(RPAREN))
            advance();
        else
            error(MISPAREN);
    } else {
        error(NOTNUMID);
    }
    return retp;
}

// term := factor term_tail
BTNode *term(void) {
    BTNode *node = factor();
    return term_tail(node);
}

// term_tail := MULDIV factor term_tail | NiL
BTNode *term_tail(BTNode *left) {
    BTNode *node = NULL;

    if (match(MULDIV)) {
        node = makeNode(MULDIV, getLexeme());
        advance();
        node->left = left;
        node->right = factor();
        return term_tail(node);
    } else {
        return left;
    }
}

// expr := term expr_tail
BTNode *expr(void) {
    BTNode *node = term();
    return expr_tail(node);
}

//TO DO
// expr_tail := ADDSUB_LOGICAL term expr_tail | NiL
BTNode *expr_tail(BTNode *left) {
    BTNode *node = NULL;

    if (match(ADDSUB)) {
        node = makeNode(ADDSUB, getLexeme());
        advance();
        node->left = left;
        node->right = term();
        return expr_tail(node);
    }else if(match(LOGICAL)){
        node = makeNode(LOGICAL, getLexeme());
        advance();
        node->left = left;
        node->right = term();
        return expr_tail(node);
    }else {
        return left;
    }
}

// statement := ENDFILE | END | expr END
void statement(void) {
    BTNode *retp = NULL;
    if (match(ENDFILE)) {
        printf("MOV r0 [0]\n");
        printf("MOV r1 [4]\n");
        printf("MOV r2 [8]\n");
        printf("EXIT 0\n");
        exit(0);
    } else if (match(END)) {
        //printf(">> ");
        advance();
    } else {
        retp = expr();
        if (match(END)) {
            evaluateTree(retp);
            //printf("%d\n", evaluateTree(retp));
            //printf("x = %d, y = %d, z = %d\n", table[0].val, table[1].val, table[2].val);
            
            //printf("Prefix traversal: ");
            //printPrefix(retp);
            //printf("\n");
            
            freeTree(retp);
            //printf(">> ");
            advance();
            for(int r = 0; r < 8; r++){
                reg[r] = 0;
            }
        } else {
            error(SYNTAXERR);
        }
    }
}

void err_self(ErrorType errorNum) {
    /*
    if (PRINTERR) {
        fprintf(stderr, "error: ");
        switch (errorNum) {
            case MISPAREN:
                fprintf(stderr, "mismatched parenthesis\n");
                break;
            case NOTNUMID:
                fprintf(stderr, "number or identifier expected\n");
                break;
            case NOTFOUND:
                fprintf(stderr, "variable not defined\n");
                break;
            case RUNOUT:
                fprintf(stderr, "out of memory\n");
                break;
            case NOTLVAL:
                fprintf(stderr, "lvalue required as an operand\n");
                break;
            case DIVZERO:
                fprintf(stderr, "divide by constant zero\n");
                break;
            case SYNTAXERR:
                fprintf(stderr, "syntax error\n");
                break;
            case INCDECNOTID:
                fprintf(stderr, "++ or -- not valid\n");
            default:
                fprintf(stderr, "undefined error\n");
                break;
        }
    }*/
    printf("EXIT 1\n");
    exit(0);
}



//codeGen.c
int checkid(BTNode *root){
    if(root->data != ID){
        if((root->right != NULL) && (root->left != NULL))
            return checkid(root->left) | checkid(root->right);
        else if (root->left == NULL && root->right == NULL)
            return 0;
        else if(root->left == NULL)
            return checkid(root->right);
        else
            return checkid(root->left);
    }
    else    return 1;
}


int valid_reg(){
    for(int i = 0; i < 8; i++){
        if(reg[i])  continue;
        else    return i;
    }
    return 8;
}

int evaluateTree(BTNode *root) {
    int retval = 0, lv = 0, rv = 0, j=0;

    if (root != NULL) {
        switch (root->data) {
            case ID:
                cur_reg = valid_reg();
                for(j = 0; j < TBLSIZE; j++){
                    if(strcmp(table[j].name, root->lexeme)==0){
                        j*=4;
                        break;
                    }
                }
                
                if(cur_reg == 8){
                    outofreg++;
                    printf("MOV [%d] r6\n", 256-4*outofreg);
                    printf("MOV r6 r7\n");
                    printf("MOV r7 [%d]\n", j);
                    retval = getval(root->lexeme);
                }
                else{
                    retval = getval(root->lexeme);
                    reg[cur_reg] = 1;
                    printf("MOV r%d [%d]\n", cur_reg, j);
                }
                break;
            case INT:
                cur_reg = valid_reg();
                retval = atoi(root->lexeme);
                if(cur_reg == 8){
                    outofreg++;
                    printf("MOV [%d] r6\n", 256-4*outofreg);
                    printf("MOV r6 r7\n");
                    printf("MOV r7 %d\n", retval);
                }
                else{
                    reg[cur_reg] = 1;
                    printf("MOV r%d %d\n", cur_reg, retval);
                }
                break;
            case ASSIGN:
                rv = evaluateTree(root->right);
                retval = setval(root->left->lexeme, rv);
                for(j = 0; j < TBLSIZE; j++){
                    if(strcmp(table[j].name, root->left->lexeme)==0){
                        j*=4;
                        break;
                    }
                }
                printf("MOV [%d] r%d\n", j, cur_reg);
                break;
            case INCDEC:
                lv = evaluateTree(root->left);
                rv = evaluateTree(root->right);
                for(j = 0; j < TBLSIZE; j++){
                    if(strcmp(table[j].name, root->left->lexeme)==0){
                        j*=4;
                        break;
                    }
                }
                if(strcmp(root->lexeme, "++") == 0){
                    retval = setval(root->left->lexeme, lv+rv);
                    if(outofreg != 0){
                        printf("ADD r6 r7\n");
                        printf("MOV [%d] r6\n", j);
                        printf("MOV r7 r6\n");
                        printf("MOV r6 [%d]\n", 256-4*outofreg);
                        outofreg--;
                        if(outofreg == 0)   cur_reg=7;
                    }else{
                        printf("ADD r%d r%d\n", cur_reg-1, cur_reg);
                        reg[cur_reg--] = 0;
                        printf("MOV [%d] r%d\n", j, cur_reg);
                    }
                }else if(strcmp(root->lexeme, "--") == 0){
                    retval = setval(root->left->lexeme, lv-rv);
                    if(outofreg != 0){
                        retval = lv - rv;
                        printf("SUB r6 r7\n");
                        printf("MOV [%d] r6\n", j);
                        printf("MOV r7 r6\n");
                        printf("MOV r6 [%d]\n", 256-4*outofreg);
                        outofreg--;
                        if(outofreg == 0)   cur_reg=7;
                    }
                    else{
                        printf("SUB r%d r%d\n", cur_reg-1, cur_reg);
                        reg[cur_reg--] = 0;
                        printf("MOV [%d] r%d\n", j, cur_reg);
                    }
                }
                break;
            case ADDSUB:
            case MULDIV:
            case LOGICAL:
                lv = evaluateTree(root->left);
                rv = evaluateTree(root->right);
                if (strcmp(root->lexeme, "+") == 0) {
                    retval = lv + rv;
                    if(outofreg != 0){
                        printf("ADD r6 r7\n");
                        printf("MOV r7 r6\n");
                        printf("MOV r6 [%d]\n", 256-4*outofreg);
                        outofreg--;
                        if(outofreg == 0)   cur_reg=7;
                    }
                    else{
                        printf("ADD r%d r%d\n", cur_reg-1, cur_reg);
                        reg[cur_reg--] = 0;
                    }
                } else if (strcmp(root->lexeme, "-") == 0) {
                    if(outofreg != 0){
                        retval = lv - rv;
                        printf("SUB r6 r7\n");
                        printf("MOV r7 r6\n");
                        printf("MOV r6 [%d]\n", 256-4*outofreg);
                        outofreg--;
                        if(outofreg == 0)   cur_reg=7;
                    }
                    else{
                        printf("SUB r%d r%d\n", cur_reg-1, cur_reg);
                        reg[cur_reg--] = 0;
                    }
                } else if (strcmp(root->lexeme, "*") == 0) {
                    retval = lv * rv;
                    if(outofreg != 0){
                        printf("MUL r6 r7\n");
                        printf("MOV r7 r6\n");
                        printf("MOV r6 [%d]\n", 256-4*outofreg);
                        outofreg--;
                        if(outofreg == 0)   cur_reg=7;
                    }
                    else{
                        printf("MUL r%d r%d\n", cur_reg-1, cur_reg);
                        reg[cur_reg--] = 0;
                    }
                } else if (strcmp(root->lexeme, "/") == 0) {
                    if(outofreg != 0){
                        if (rv == 0){
                            if(!checkid(root->right)){
                                error(DIVZERO);
                            }
                            else{
                                printf("DIV r6 r7\n");
                                printf("MOV r7 r6\n");
                                printf("MOV r6 [%d]\n", 256-4*outofreg);
                                outofreg--;
                                if(outofreg == 0)   cur_reg=7;
                            }
                        }
                        else{
                            retval = lv / rv;
                            printf("DIV r6 r7\n");
                            printf("MOV r7 r6\n");
                            printf("MOV r6 [%d]\n", 256-4*outofreg);
                            outofreg--;
                            if(outofreg == 0)   cur_reg=7;
                        }
                    }
                    else{
                        if (rv == 0){
                            if(!checkid(root->right)){
                                error(DIVZERO);
                            }
                            else{
                                printf("DIV r%d r%d\n", cur_reg-1, cur_reg);
                                reg[cur_reg--] = 0;
                            }
                        }
                        else{
                            retval = lv / rv;
                            printf("DIV r%d r%d\n", cur_reg-1, cur_reg);
                            reg[cur_reg--] = 0;
                        }
                    }
                }else if (strcmp(root->lexeme, "&") == 0) {
                    retval = lv & rv;
                    if(outofreg != 0){
                        printf("AND r6 r7\n");
                        printf("MOV r7 r6\n");
                        printf("MOV r6 [%d]\n", 256-4*outofreg);
                        outofreg--;
                        if(outofreg == 0)   cur_reg=7;
                    }else{
                        printf("AND r%d r%d\n", cur_reg-1, cur_reg);
                        reg[cur_reg--] = 0;
                    }
                }else if (strcmp(root->lexeme, "|") == 0) {
                    retval = lv | rv;
                    if(outofreg != 0){
                        printf("OR r6 r7\n");
                        printf("MOV r7 r6\n");
                        printf("MOV r6 [%d]\n", 256-4*outofreg);
                        outofreg--;
                        if(outofreg == 0)   cur_reg=7;
                    }
                    else{
                        printf("OR r%d r%d\n", cur_reg-1, cur_reg);
                        reg[cur_reg--] = 0;
                    }
                }else if (strcmp(root->lexeme, "^") == 0) {
                    retval = lv ^ rv;
                    if(outofreg != 0){
                        printf("XOR r6 r7\n");
                        printf("MOV r7 r6\n");
                        printf("MOV r6 [%d]\n", 256-4*outofreg);
                        outofreg--;
                        if(outofreg == 0)   cur_reg=7;
                    }
                    else{
                        printf("XOR r%d r%d\n", cur_reg-1, cur_reg);
                        reg[cur_reg--] = 0;
                    }
                }
                break;
            default:
                retval = 0;
        }
    }
    return retval;
}



//main.c
int main(int argc, const char * argv[]) {
    initTable();
    //printf(">> ");
    while (1) {
        statement();
    }
    return 0;
}
