//
//  main.c
//  svool dliow
//
//  Created by 顏浩昀 on 2019/9/18.
//  Copyright © 2019 顏浩昀. All rights reserved.
//

#include <stdio.h>

int main() {
    char input[5];
    for(int a = 0; a < 5; a++){
        scanf("%c", &input[a]);
        input[a] = 'a' + 'z' - input[a];
    }
    for(int a = 0; a < 5; a++){
        printf("%c", input[a]);
    }
    return 0;
}
