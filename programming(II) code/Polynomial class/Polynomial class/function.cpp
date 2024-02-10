//
//  function.cpp
//  Polynomial class
//
//  Created by 顏浩昀 on 2020/4/28.
//  Copyright © 2020 顏浩昀. All rights reserved.
//


#include <iostream>
#include <stdio.h>
#include <string>
#include "10993.h"


Polynomial::Polynomial()
:greatestPower(0)
{
    for(int i = 0; i < 101; i++){
        coefficients[i] = 0;
    }
}
Polynomial::Polynomial(const int pow, const int co[51])
:greatestPower(pow)
{
    for(int i = 0; i <= pow; i++){
        coefficients[i] = co[i];
    }
    for(int j = pow+1; j<101;j++){
        coefficients[j] = 0;
    }
}

Polynomial Polynomial::add(const Polynomial b) const{ // add function
    Polynomial ans;
    if(greatestPower > b.greatestPower) ans.greatestPower = greatestPower;
    else    ans.greatestPower = b.greatestPower;
    for(int i = ans.greatestPower; i >= 0; i--){
        ans.coefficients[i] = coefficients[i] + b.coefficients[i];
    }
    return ans;
}
Polynomial Polynomial::subtract(const Polynomial b) const{ // subtract function
    Polynomial ans;
    if(greatestPower > b.greatestPower) ans.greatestPower = greatestPower;
    else    ans.greatestPower = b.greatestPower;
    for(int i = ans.greatestPower; i >= 0; i--){
        ans.coefficients[i] = coefficients[i] - b.coefficients[i];
    }
    return ans;
}
Polynomial Polynomial::multiplication(const Polynomial b) const{ // multiplication function
    Polynomial ans;
    ans.greatestPower = greatestPower + b.greatestPower;
    for(int i = greatestPower; i >= 0; i--){
        for(int j = b.greatestPower; j >= 0; j--){
            ans.coefficients[i+j] += (coefficients[i]*(b.coefficients[j]));
        }
    }
    return ans;
}

void Polynomial::output() const{
    for(int i = greatestPower; i > 0; i--){
        std::cout<<coefficients[i]<<" ";
    }
    std::cout<<coefficients[0];
}
