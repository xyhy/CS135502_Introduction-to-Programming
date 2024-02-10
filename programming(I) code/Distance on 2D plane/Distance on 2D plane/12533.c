//
//  main.c
//  Distance on 2D plane
//
//  Created by 顏浩昀 on 2019/12/22.
//  Copyright © 2019 顏浩昀. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include "12533.h"


int main(void)
{
   Point *point_array;
   int i, length, N;
   float ans;

   scanf("%d", &length);
   // give point_array memory and get first element address
   point_array = ones_vec_1(length);

   scanf("%d", &N);
   for (i = 0; i < N; i++){
      int first, second;
      scanf("%d %d", &first, &second);
      // compute distance of two points
      ans = compute_distance(point_array, first, second);
      printf("%.3f\n", ans);
   }

   return 0;
}
