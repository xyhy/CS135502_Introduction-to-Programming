#include<stdio.h>

int main(){
    int question = 0; // initiate is solution
    int valid = 0;  // valid solution
    char arr[13][13];
    for(int a = 0; a < 13; a++){
        scanf("%s", arr[a]);
    }
    for(int a = 0; a < 13; a++){
        for(int b = 0; b<13; b++){
            if(arr[a][b] == 'x'){
                question = 1;       // is question
                break;
            }
        }
        if(question == 1){
            break;
        }
    }
    if(question == 0){              // compare valid solution
        for(int a = 0; a<13; a++){
            for(int b = 0; b<13; b++){
                if((arr[a][b] == '-') || (arr[a][b] == '_') || (arr[a][b] == '|')){
                    continue;
                }else{
                    for(int c = b+1; c<13; c++){
                        if(arr[a][b] != arr[a][c]){
                            continue;
                        }else{
                            valid = 1;
                            break;
                        }
                    }
                }
            }
        }
        if(valid == 0){
            for(int a = 0; a<13; a++){
                for(int b = 0; b<13; b++){
                    if((arr[b][a] == '-') || (arr[b][a] == '_') || (arr[b][a] == '|')){
                        continue;
                    }else{
                        for(int c = b+1; c<13; c++){
                            if(arr[b][a] != arr[c][a]){
                                continue;
                            }else{
                                valid = 1;
                                break;
                            }
                        }
                    }
                }
            }
        }
        if(valid == 0){
            for(int a = 1; a<4; a++){
                for(int b = 1; b<4; b++){
                        for(int c = b+1; c<4; c++){
                            if(arr[a][b] != arr[a][c]){
                                continue;
                            }else{
                                valid = 1;
                                break;
                            }
                        }
                    }
                }
            }
        if(valid == 0){
                       for(int a = 5; a<8; a++){
                           for(int b = 5; b<8; b++){
                                   for(int c = b+1; c<8; c++){
                                       if(arr[a][b] != arr[a][c]){
                                           continue;
                                       }else{
                                           valid = 1;
                                           break;
                                       }
                                   }
                               }
                           }
                       }
        if(valid == 0){
                   for(int a = 9; a<12; a++){
                       for(int b = 9; b<12; b++){
                               for(int c = b+1; c<12; c++){
                                   if(arr[a][b] != arr[a][c]){
                                       continue;
                                   }else{
                                       valid = 1;
                                       break;
                                   }
                               }
                           }
                       }
                   }
        if(valid == 0){
            printf("solution, valid\n");
        }else{
            printf("solution, invalid\n");
        }
    }else{              // compare valid question
        for(int a = 0; a<13; a++){
            for(int b = 0; b<13; b++){
                if((arr[a][b] == '-') || (arr[a][b] == '_') || (arr[a][b] == '|')||(arr[a][b] == 'x')){
                    continue;
                }else{
                    for(int c = b+1; c<13; c++){
                        if(arr[a][b] != arr[a][c]){
                            continue;
                        }else{
                            valid = 1;
                            break;
                        }
                    }
                }
            }
        }
        if(valid == 0){
            for(int a = 0; a<13; a++){
                for(int b = 0; b<13; b++){
                    if((arr[b][a] == '-') || (arr[b][a] == '_') || (arr[b][a] == '|')||(arr[b][a] == 'x')){
                        continue;
                    }else{
                        for(int c = b+1; c<13; c++){
                            if(arr[b][a] != arr[c][a]){
                                continue;
                            }else{
                                valid = 1;
                                break;
                            }
                        }
                    }
                }
            }
        }
        if(valid == 0){
            for(int a = 1; a<4; a++){
                for(int b = 1; b<4; b++){
                        for(int c = b+1; c<4; c++){
                            if((arr[a][b] != arr[a][c]) || (arr[a][b] == 'x')){
                                continue;
                            }else{
                                valid = 1;
                                break;
                            }
                        }
                    }
                }
            }
        if(valid == 0){
                       for(int a = 5; a<8; a++){
                           for(int b = 5; b<8; b++){
                                   for(int c = b+1; c<8; c++){
                                       if((arr[a][b] != arr[a][c])|| (arr[a][b] == 'x')){
                                           continue;
                                       }else{
                                           valid = 1;
                                           break;
                                       }
                                   }
                               }
                           }
                       }
        if(valid == 0){
                   for(int a = 9; a<12; a++){
                       for(int b = 9; b<12; b++){
                               for(int c = b+1; c<12; c++){
                                   if((arr[a][b] != arr[a][c]) || (arr[a][b] == 'x')){
                                       continue;
                                   }else{
                                       valid = 1;
                                       break;
                                   }
                               }
                           }
                       }
                   }
        if(valid == 0){
            printf("question, valid\n");
        }else{
            printf("question, invalid\n");
        }
    }
    return 0;
}
