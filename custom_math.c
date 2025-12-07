#include <stdio.h>
#include "fonction.h"
#include <math.h>

double power(double a,double b){
    double result=1;
    int i;
    if (b<0){
        b=-b;
        for(i=0;i<b;i++){
            result=result*a;}
            return 1/result;    
    }
  for(i=0;i<b;i++){
    result=result*a;
  } 
  return result;
} 
double factorial(double a){
    int i, F=1;
    if(a==0) return 1;
    if(a<0) return NAN; //erreur
    for(i=1;i<=a;i++){
        F=F*i;
    } return F;
} 

double square_root(double a) {
    if (a < 0) return NAN; // erreur
    double guess = a / 2;
    for (int i = 0; i < 20; i++) {
        guess = (guess + a / guess) / 2.0;
    }
    return guess;
}
double exponential(double a) {
    double sum = 1.0;
    double term = 1.0;

    for (int i = 1; i <= 20; i++) {
        term *= a / i;
        sum += term;
    }
    return sum;
}
double sine(double a) {
    double term = a;
    double sum = a;

    for (int i = 1; i <= 10; i++) {
        term *= (-1) * a * a / ((2*i)*(2*i+1));
        sum += term;
    }
    return sum;
}
double cosine(double a) {
    double term = 1;
    double sum = 1;

    for (int i = 1; i <= 10; i++) {
        term *= (-1) * a * a / ((2*i-1)*(2*i));
        sum += term;
    }
    return sum;
}
double tangent(double a) {
    double c = cosine(a);
    if (c == 0) return NAN; // erreur
    return sine(a) / c;
} 
double dgr_to_rad(double a){
    return a*3,14/180;
}
double rad_to_dgr(double a){
    return a*180/3,14;
}





