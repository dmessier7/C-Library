#include <stdio.h>
#include <math.h>


// Bisection Method
double Bisection(double (*f)(double), double a1 ,double b1, double e, int ItLimit)
{
  double error = 1.0;
  double min = pow(10.0, e);
  double a = a1;
  double b = b1;
  double p = (a1+b1)/2.0;
  double o;
  int i = 1;
  double fa = (*f)(a);
  double fb = (*f)(b);
  if (fa*fb > 0.0){printf("fa*fb: %0.15f\n,  Zero not on the interval", fa*fb); return 0;}
  while ((ItLimit >i) && (error > min))
  {
    double fu = (*f)(p);
    if (fu == 0.0)
    {
      break;
    }
    o = p;
    if(fu*fa > 0)
    {
      a = p;
    }
    else if (fu*fa < 0)
    {
      b = p;
    }
    p = (a+b)/2.0;
    error = fabs(p-o);
    i++;
  }
  printf("Final p = %0.15f\n", p);
  printf("p number = %0.d\n", i);
  return 0;
}

// Fixed Point Iteration
double FixedPoint(double (*f)(double), double guess, double e, int ItLimit)
{
  double min = pow(10.0, e);
  double error = 1.0;
  double p = guess;
  int i = 0;
  while((ItLimit >i) && (error > min))
  {
    if ((*f)(p) == p) {break;}
    double o = p;
    p = (*f)(p);
    error = fabs(p-o);
    i++;
  }
  printf("Final p = %0.15f\n", p);
  printf("# of steps = %0.d\n", i);
  return 0;
}

// Newtons method
double Newtons(double (*f)(double), double (*der)(double), double guess, double e, int ItLimit)
{
  double min = pow(10.0, e);
  double p0 = guess;
  double E = 1;
  int i = 0;
  while((ItLimit >i))
  {
    double p = p0 - ((*f)(p0)/(*der)(p0));
    E = fabs(p-p0);
    if (!(E > min)) {break;}
    p0 = p;
    i++;
  }
  printf("Final p = %0.15f\n", p0);
  printf("# of steps = %0.d\n", i);
  return 0;
}

// Secant Method
double Secant(double (*f)(double), double g1, double g2, double e, int ItLimit)
{
  double min = pow(10.0, e);
  double p0 = g1;
  double p1 = g2;
  double q0 = (*f)(p0);
  double E = 1;
  int i = 2;
  while(ItLimit >i)
  {
    double q1 = (*f)(p1);
    if ((q1-q0) == 0)
    {
      printf("Undefined");
      return 0;
    }
    double p = p1 - (q1*(p1-p0))/(q1-q0);
    E = fabs(p-p1);
    if (!(E > min)) {break;}
    q0 = q1;
    p0 = p1;
    p1 = p;
    i++;
  }
  printf("Final p = %0.15f\n", p1);
  printf("# of steps = %0.d\n", i);
  return 0;
}

double ModNewtons(double (*f)(double), double (*der)(double), double (*dder)(double), double guess, double e, int ItLimit)
{
  double min = pow(10.0, e);
  double p0 = guess;
  double E = 1;
  int i = 0;
  while((ItLimit >i))
  {
    double f1 = (*f)(p0);
    double f2 = (*der)(p0);
    double f3 = (*dder)(p0);
    double p = p0 - ((f1*f2)/(pow(f2,2.0) - (f1*f3)));
    E = fabs(p-p0);
    if (!(E > min)) {break;}
    p0 = p;
    i++;
  }
  printf("Final p = %0.15f\n", p0);
  printf("# of steps = %0.d\n", i);
  return 0;
}

// Aitken's Method: plug in a linearly converging sequence, with an Alist array that
double Aitkens(double (*f)(double), double *list, double *Alist, double p0, int IntLimit)
{
  list[0] = p0;
  list[1] = (*f)(p0);
  list[2] = (*f)(list[1]);
  int i = 0;
  while(IntLimit > i)
  {
    Alist[i] = list[i] - (pow(list[i+1]-list[i],2.0)/(list[i+2] - (2.0*list[i+1]) + list[i]));
    printf("%0.15f\n", Alist[i]);
    list[i+3] = (*f)(list[i+2]);
    i++;
  }
  return 0;
}

// Steffensen's Method
double Steffensens(double (*f)(double), double guess, double e, int ItLimit)
{
  double min = pow(10.0, e);
  double p0 = guess;
  int i = 0;
  while(ItLimit > i)
  {
    double p1 = (*f)(p0);
    double p2 = (*f)(p1);
    double p = p0 - (pow(p1-p0, 2.0)/(p2-(2.0*p1) + p0));
    printf("%0.15f\n", p);
    if(fabs(p-p0) < min) {break;}
    i++;
    p0=p;
  }

  printf("%0.15f\n", p0);
  printf("%0.d\n", i);
  return 0;
}
