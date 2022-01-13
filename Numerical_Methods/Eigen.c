#include <stdio.h>
#include <math.h>
#include </Users/danielmessier/Documents/C-Library/Numerical_Methods/LinearSystems.c>

float powerMethod(int n, float matrix[n][n], float est[n], int tol)
{
  int iter = 0;
  float eTol = pow(10,tol);
  float mu = 0.0;
  float temp = 0.0;
  float b[n];
  zeroOut(n, b);
  MatrixApply(n, matrix, b, est);
  mu = infNorm(n, b);
  while (abs(mu-temp)>eTol)
  for(int i = 0; i<n; i++)
  {
    b[i] = b[i]/mu;
  }
  VectorPrint(n, b);
  return 0;
}

int main()
{
  float a[2][2] = {{2.0,0.0},{0.0,1.0}};
  float guess[2] = {1.0,1.0};
  powerMethod(2, a, guess, 5.0);
}
