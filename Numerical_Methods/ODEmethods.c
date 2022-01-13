#include <stdio.h>
#include <math.h>

double RK4(double (*f2v)(double, double), double a, double b, int N, double alpha)
{
  double h = (b-a)/N;
  double t = a;
  double w = alpha;
  int i = 1;
  while (i< N+1)
  {
    double k1 = h*(*f2v)(t,w);
    double k2 =  h*(*f2v)(t+(h/2.0), w+(k1/2));
    double k3 =  h*(*f2v)(t+(h/2.0), w+(k2/2));
    double k4 = h*(*f2v)(t+h, w+k3);
    w = w + (k1 + (2.0*k2) + (2.0*k3)+ k4)/6.0;
    if(fmod(t,180.0) == 0.0){printf("w%0.0f: %0.15f\n", t, w);}
    t = a + (i*h);
    i++;
  }
  printf("t: %0.15f\n", t);
  printf("w: %0.15f\n", w);
  return 0;
}
