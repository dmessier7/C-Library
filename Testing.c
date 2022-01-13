#include <stdio.h>
#include <math.h>
//#include<stdlib.h>
#include </Users/danielmessier/Documents/C-Library/Numerical_Methods/Interpolation.c>
#include </Users/danielmessier/Documents/C-Library/Numerical_Methods/General.c>
#include </Users/danielmessier/Documents/C-Library/Numerical_Methods/ODEmethods.c>

double func2v(double t, double x)
{
  double xp = -0.0480749415*pow(x, (-1.5));
  return xp;
}
double func(double x)
{
  double y = x*log(x);
  return y;
}
double deriv(double x)
{
  double y = 6.0*exp(6.0*x) + 2.881*exp(2.0*x) - 8.316*exp(4.0*x);
  return y;
}

double dderiv(double x)
{
  double y = 36.0*exp(6.0*x) + 5.762*exp(2.0*x) - 33.264*exp(4.0*x);
  return y;
}

int recursion(int n)
{
  if(n == 0){return 0;}
  else {return (n+recursion(n-1));}
}

int main()
{
//  double y = 1.0 + (22.0/60.0) + (7/pow(60.0, 2.0)) + (42/pow(60.0, 3.0)) + (33/pow(60.0, 4.0)) + (4/pow(60.0, 5.0)) + (40/pow(60.0, 6.0));
//  printf("%0.15f\n", y);
//  Newtons(func, deriv, -0.3, -5.0, 1000);
//  ModNewtons(func, deriv, dderiv, -0.3, -5.0, 1000);
//  double l[8];
//  double li[5];
//  Aitkens(func, l, li, 0.5, 5.0);
//    Steffensens(func, 0.5, -5.0, 1000);
//  double I = CTrapInt(func, 1.0, 2.0, 4);
//  printf("Integral: %0.15f\n", I);
  //RK4(func2v, 0.0, 1530.0, 102, 8.0);
  int a = recursion(100);
  printf("%d\n", a);


}
