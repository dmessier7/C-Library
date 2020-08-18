#include <stdio.h>
#include <math.h>


double FDiff(double (*f)(double), double step, double t0)
{
  double j = ((*f)(t0 + step) - (*f)(t0));
  double Iprime = j/(step);
  return Iprime;
}

double CDiff(double (*f)(double), double step, double t0)
{
  double j = ((*f)(t0 + step) - (*f)(t0-step));
  double Iprime = j/(2.0*step);
  return Iprime;
}

double BDiff(double (*f)(double), double step, double t0)
{
  double j = ((*f)(t0) - (*f)(t0-step));
  double Iprime = j/(step);
  return Iprime;
}

double FiveDiff(double (*f)(double), double step, double t0)
{
  double a = (*f)(t0 - 2.0*step) - 8.0*(*f)(t0 - step);
  double b = 8.0*(*f)(t0 + step) -(*f)(t0 + 2.0*step);
  double Iprime = (a+b)/(12.0*step);
  return Iprime;
}

double MidSecDiff(double (*f)(double), double step, double t0)
{
  double a = (*f)(t0 - step) - 2.0*(*f)(t0) + (*f)(t0 + step);
  double Iprime = a/(step*step);
  return Iprime;
}

int main()
{
  double k = MidSecDiff(func, 0.000000001, 0.0);
  double g = fabs(k);
  printf("approx: %0.10f\n", k);
  printf("error: %0.10f\n", g);

}
