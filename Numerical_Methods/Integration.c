#include <stdio.h>
#include <math.h>
#include <stdlib.h>


double STrapInt(double (*f)(double), double a, double b)
{
  double h = b - a;
  double sum = (*f)(a) + (*f)(b);
  double I = (h/2.0)*sum;
  return I;
}

double SSimpInt(double (*f)(double), double a, double b)
{
  double h = (b - a)/2.0;
  double sum = (*f)(a) + 4.0*(*f)(a+h)+ (*f)(b);
  double I = (h/3.0)*sum;
  return I;
}

double CTrapInt(double (*f)(double), double a, double b, int evenN)
{
  double h = (b-a)/evenN;
  double sum = 0;
  int i = 1;
  while (i < evenN)
  {
    int xi = a + (i*h);
    sum += (*f)(xi);
    i ++;
  }
  double ssum = (*f)(a) + (*f)(b) + 2.0*sum;
  double I = (h/2.0)*ssum;
  return I;
}

double CMidInt(double (*f)(double), double a, double b, int evenN)
{
  double h = (b-a)/(evenN+2);
  double sum = 0;
  double j = 0;
  while (j< (evenN/2)+1)
  {
    double x2j = a + ((2.0*j)+1.0)*h;
    sum += (*f)(x2j);
    j ++;
  }
  double I = 2.0*h*sum;
  return I;
}

double CSimpInt(double (*f)(double), double a, double b, int evenN)
{
  double h = (b-a)/evenN;
  double sum1 = 0;
  int i = 1;
  while (i<(evenN/2))
  {
    double x2i = a + (2.0*i)*h;
    sum1 += (*f)(x2i);
    i ++;
  }
  double sum2 = 0;
  int j = 1;
  while (j<((evenN/2)+1))
  {
    double x2j1 = a + (2.0*j-1.0)*h;
    sum2 += (*f)(x2j1);
    j ++;
  }
  double ssum = (*f)(a) + (*f)(b) + 2.0*sum1 + 4.0*sum2;
  double I = (h/3.0)*ssum;
  return I;
}

double H(double a, double b, double k)
{
  double h = (b-a)/(pow(2.0,(k-1)));
  return h;
}

double RKadd(double (*f)(double), double a, double b, int k, double R)
{
  double sum = 0;
  int i = 1;
  while (i<(pow(2.0,(k-2))+1))
  {
    double x = a + ((2*i)-1)*H(a,b,k);
    sum += (*f)(x);
    i ++;
  }
  double RR = 0.5*(R + H(a,b,(k-1))*sum);
  return RR;
}

double RJadd(double j, double RJminus, double RKminusKminus)
{
  double denom = pow(4.0, j-1) - 1.0;
  double RR = (RJminus - RKminusKminus)/denom;
  RR += RJminus;
  return RR;
}

double Romberg(double (*f)(double), double a, double b, int maxk, int maxj)
{
  double h = b-a;
  double R[maxk+1][maxj+1];
  //double **R = malloc(sizeof(int[maxk][maxj]));
  R[1][1] = (h/2)*((*f)(a)+(*f)(b));
  int i = 2;
 while (i< maxk+1)
  {
    R[i][1] = RKadd((*f),a, b, i, R[i-1][1]);
    int j = 2;
    while (j<i+1)
    {
      R[i][j] = RJadd(j, R[i][j-1],R[i-1][j-1]);
      j ++;
    }
    i ++;
  }
  return R[9][5];
}
