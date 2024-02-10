//
//  The One Function and The Power Of Matrix.cpp
//  The One Function and The Power Of Matrix
//
//  Created by 顏浩昀 on 2020/5/21.
//  Copyright © 2020 顏浩昀. All rights reserved.
//

#include <iostream>
#include "12767.h"

Matrix::Matrix(int n) : n(n)
{  //constructor
    matrix = new long long* [n];
    for(int i = 0; i < n; i++){
        matrix[i] = new long long[n];
    }
    toZero();
}

Matrix::~Matrix(){  //destructor

}

Matrix::Matrix(const Matrix& ref){   //copyconstructor
    n = ref.n;
    matrix = new long long* [n];
    for(int i = 0; i < n; i++){
        matrix[i] = new long long[n];
    }
    matrix = ref.matrix;
}

Matrix& Matrix::operator=(const Matrix& ref){
    this->n = ref.n;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            this->matrix[i][j] = ref.matrix[i][j];
        }
    }
    return *this;
}

long long& Matrix::operator()(const int& row, const int& column) const{
    return matrix[row][column];
}

Matrix Matrix::operator*(const Matrix& rhs) const{
    Matrix temp = *this;
    Matrix ans(n);
    ans.toZero();
    long long int tmp = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j ++){
            tmp = 0;
            for(int k = 0; k < n; k++){
                tmp += temp(i,k) * rhs(k,j) % mod;
                tmp%=mod;
            }
            ans(i,j) = tmp;
        }
    }
    return ans;
}

void Matrix::toIdentity(){
    this->toZero();
    for(int i = 0; i < n-1; i++){
        this->matrix[i][i+1] = 1;
    }
    for(int i = 0; i < n; i++){
        this->matrix[n-1][i] = 1;
    }
}

Matrix Matrix::power(int k) const{
    Matrix tmp(n);
    tmp = *this;
    if(k == 1)    return tmp;
    if(k%2){
        tmp = power((k-1)/2);
        return tmp*tmp*(*this);
    }
    else{
        tmp = power(k/2);
        return tmp*tmp;
    }
}

Matrix constructMatrix(int n){
    Matrix ret(n);
    ret.toIdentity();
    return ret;
}
