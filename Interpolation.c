#include <stdio.h>
#include <math.h>


float Linter(float x[], float y[], float xin)
{
  int n = sizeof(x)/sizeof(x[0]) +1;
  int i = 0;
  float k = 0;
  for(i=0; i<n; i++)
  {
    float s=1;
    float t=1;
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

int main()
{
  float x[] = {0.0, 0.6, 0.9};
  float y[] = {1.0, sqrt(1.6), sqrt(1.9)};
  float k = Linter(x, y, 0.45);
  printf("%f", k);
}
