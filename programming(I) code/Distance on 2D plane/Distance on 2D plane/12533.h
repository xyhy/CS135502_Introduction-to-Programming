#ifndef _FUNCTION_H
#define _FUNCTION_H

typedef struct {
    int x;
    int y;
} Point;


Point *ones_vec_1(int length){
    Point *array_vec;
    array_vec = (Point*)malloc(length*sizeof(Point));
    for(int i = 0; i < length; i++){
        scanf("%d %d", &array_vec[i].x, &array_vec[i].y);
    }
    return array_vec;
}
float compute_distance(Point* a, int first_id, int second_id){
    int x, y;
    x = (a[first_id].x-a[second_id].x)*(a[first_id].x-a[second_id].x);
    y = (a[first_id].y-a[second_id].y)*(a[first_id].y-a[second_id].y);
    return sqrt(x+y);
}

#endif
