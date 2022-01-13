#include <stdio.h>
#include <math.h>


double Linter(double x[], double y[], int NumElements, double xin)
{
  int i = 0;
  double k = 0.0;
  for(i=0; i<NumElements; i++)
  {
    double s=1.0;
    double t=1.0;
    for(int j=0; j<NumElements; j++)
    {
        if(j!=i)
        {
            s=s*(xin-x[j]);
            t=t*(x[i]-x[j]);
        };
    };
    k=k+((s/t)*y[i]);
  };
  return k;
}

/*
double LinterV(double x[], double y[], int NumElements, double PolyVector[])
{
  int i = 0;
  double k = 0.0;
  for(i=0; i<n; i++)
  {
    double s=1.0;
    double t=1.0;
    for(int j=0; j<n; j++)
    {
        if(j!=i)
        {
            s=s*(xin-x[j]);
            t=t*(x[i]-x[j]);
        };
    };
    k=k+((s/t)*y[i]);
  };
  return k;
}
*/

//// UGHGGHGHGHGHGHGH
double Vieta(double roots[], double coeff[], int NumElements)
{
  for(int i=0; i<NumElements; i++)
  {
    coeff[i] = 0.0;
  }
  coeff[NumElements] = 1;

  return 0;
}

double PolyEvaluate(double PolyVec[], int NumElements, double xin)
{
  int i = 0;
  double out = 0;
  while (NumElements > i)
  {
    out += PolyVec[i]*pow(xin, i);
    //printf("%0.d\n", i);
    i++;
  }
  return out;
}
/*
int main()
{
//  double x[] = {0.0, 0.6, 0.9};
//  double y[] = {1.0, sqrt(1.6), sqrt(1.9)};
//  double k = Linter(x, y, 3,  0.45);
//  double Poly[] = {0.0, 1.0, 2.0};
//  printf("%0.lu\n", sizeof(Poly)/sizeof(Poly[0]));
//  double xin = 2.0;
//  double k = PolyEvaluate(Poly, 3, xin);
//  printf("%f", k);
  double roots[] = {-1.0, 2.0, 3.0};
  double coeff[4];
  Vieta(roots, coeff, 3);
  printf("%0.15f\n", coeff[0]);
  printf("%0.15f\n", coeff[1]);
  printf("%0.15f\n", coeff[2]);
  printf("%0.15f\n", coeff[3]);
}
*/
