#include <stdio.h>
#include <math.h>

double factorial(double value)
{
  if(value < 0 || trunc(value) != value)
  {
    printf("Non Natural Number\n");
    return 0;
  }
  int i= 1;
  int fact = 1;
  while(i<=value)
  {
    fact = fact*i;
    i++;
  }
  return fact;
}

// Does not work
double errorf(double value, int order)
{
  int i = 0;
  double y = 0;
  while (i<=order)
  {
    y += (pow(-1.0, i)*pow(value, ((2.0*i) + 1.0)))/(((2.0*i)+1.0)*factorial(i));
    i++;
  }
  y *= 2.0/sqrt(M_PI);
  return y;
}
