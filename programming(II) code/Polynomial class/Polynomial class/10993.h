#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
#include <iostream>

class Polynomial
{

public:
    Polynomial();
/*    :greatestPower(0)
    {
        for(int i = 0; i < 101; i++){
            coefficients[i] = 0;
        }
    }*/
    Polynomial(const int pow, const int co[51]);
  /*  :greatestPower(pow)
    {
        for(int i = 0; i <= pow; i++){
            coefficients[i] = co[i];
        }
        for(int j = pow+1; j<101;j++){
            coefficients[j] = 0;
        }
    }*/
    Polynomial add(const Polynomial b) const; // add function
    Polynomial subtract(const Polynomial b) const; // subtract function
    Polynomial multiplication(const Polynomial b) const; // multiplication function
    
    void output() const;
private:
    int coefficients[101]; // integer coefficients
    int greatestPower; // integer greatestPower
}; // end class Polynomial

#endif

