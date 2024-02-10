//
//  main.c
//  Hakka's Dream
//
//  Created by 顏浩昀 on 2019/10/13.
//  Copyright © 2019 顏浩昀. All rights reserved.
//

#include <stdio.h>
#include<math.h>

int main() {
    int T = 0;
    int first_month = 0, last_month = 0;
    double Rate = 0, Hakka_rate = 0;
    scanf("%d", &T);
    while(T>0){
        scanf("%d%d", &first_month, &last_month);
        Rate = (double)last_month/(double)first_month;
        Rate -= 1;
        Rate *= 100;
        Hakka_rate = roundf(Rate * 100)/100;
        if(Hakka_rate >= 5){
            printf("%7.2f%% (#`Д´)ﾉ\n",Hakka_rate);
        }else if(Hakka_rate <= -5){
            printf("%7.2f%% (ゝ∀･)b\n",Hakka_rate);
        }else if(Hakka_rate < 0.005 && Hakka_rate > -0.005){
            printf("   0.00%% \\^o^/\n");
        }else{
            printf("%7.2f%% \\^o^/\n",Hakka_rate);
        }
        T--;
    }
    return 0;
}
