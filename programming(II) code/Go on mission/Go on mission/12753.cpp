//
//  main.cpp
//  Go on mission
//
//  Created by 顏浩昀 on 2020/5/15.
//  Copyright © 2020 顏浩昀. All rights reserved.
//
#include <iostream>
#include "12753.h"

using namespace std;

int main()
{
    int n; cin >> n;
    // initialize health condition
    BigInt hi, kaminari, kedamono;
    cin >> hi; kaminari = kedamono = hi;
    // go on mission
    solution(hi, kaminari, kedamono, n);
    // output result
    cout << hi << endl;
    cout << kaminari << endl;
    cout << kedamono << endl;
}
