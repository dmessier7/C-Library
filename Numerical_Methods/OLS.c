#include <stdio.h>
#include <math.h>
#include </Users/danielmessier/Documents/C-Library/Numerical_Methods/LinearSystems.c>


// input data, a degree, and a guess vec. change the guess vec to the Solution
int olsLinear(int dataSize, float data[dataSize][2], int polyOrder, float sol[polyOrder+1])
{
  //prep matrix and sol elements
  int j = 0;
  float matrixElements[(2*polyOrder)+1];
  zeroOut((2*polyOrder)+1, matrixElements);
  float b[polyOrder+1];
  zeroOut(polyOrder+1, b);
  while(j<dataSize)
  {
    float x2n = 1;
    float x = data[j][0];
    float y = data[j][1];
    matrixElements[0] += x2n;
    b[0] += y;
    int k = 1;
    while(k<(2*polyOrder+1))
    {
      x2n *= x;
      matrixElements[k] += x2n;
      if(k<(polyOrder+1)){b[k] += (y*x2n);}
      k++;
    }
    j++;
  }
//  VectorPrint((2*polyOrder)+1, matrixElements);
//  VectorPrint(polyOrder+1, b);
  //prep the augmented matrix
  float aug[polyOrder+1][polyOrder+2];
  for(int i = 0; i<polyOrder+1; i++) // row
  {
    for(int j = 0; j<polyOrder+2; j++) // column
    {
      int n = i+j;
      if(j != polyOrder+1)
      {
       aug[i][j] = matrixElements[n];
      }
      else {aug[i][j] = b[i];}
    }
  }
//  MatrixPrint(polyOrder+1, aug);
  //solve matrix
  GaussianPartial(polyOrder+1, aug);
  Backsub(polyOrder+1, aug, sol);
  return 0;
}

int olsPoly(int dataSize, float data[dataSize][2], int polyOrder, float sol[polyOrder+1])
{
  //prep matrix and sol elements
  int j = 0;
  float matrixElements[(2*polyOrder)+1];
  zeroOut((2*polyOrder)+1, matrixElements);
  float b[polyOrder+1];
  zeroOut(polyOrder+1, b);
  while(j<dataSize)
  {
    float x2n = 1;
    float x = data[j][0];
    float y = data[j][1];
    matrixElements[0] += x2n;
    b[0] += y;
    int k = 1;
    while(k<(2*polyOrder+1))
    {
      x2n *= x;
      matrixElements[k] += x2n;
      if(k<(polyOrder+1)){b[k] += (y*x2n);}
      k++;
    }
    j++;
  }
//  VectorPrint((2*polyOrder)+1, matrixElements);
//  VectorPrint(polyOrder+1, b);
  //prep the augmented matrix
  float aug[polyOrder+1][polyOrder+2];
  for(int i = 0; i<polyOrder+1; i++) // row
  {
    for(int j = 0; j<polyOrder+2; j++) // column
    {
      int n = i+j;
      if(j != polyOrder+1)
      {
       aug[i][j] = matrixElements[n];
      }
      else {aug[i][j] = b[i];}
    }
  }
//  MatrixPrint(polyOrder+1, aug);
  //solve matrix
  GaussianPartial(polyOrder+1, aug);
  Backsub(polyOrder+1, aug, sol);
  return 0;
}

int olsTrig(int dataSize, float data[dataSize][2], int order, float sol[order+1][2]) //sol must already be 0s
{
  float m = dataSize/2.0;
  int j = 0;
  while(j<(dataSize))
  {
    float x = data[j][0];
    float y = data[j][1];
    for(int k = 0; k<(order+1); k++)
    {
      sol[k][0] += y*cos(k*x);
      if(k==1 || k==order){sol[k][1] = 0.0;}
      else
      {
        sol[k][1] = y*sin(k*x);
      }
    }
    j++;
  }
  for(int h = 0; h<(order+1);h++)
  {
    sol[h][0] /= m;
    sol[h][1] /= m;
  }
  //scale each term down by m
  return 0;
}

int main()
{
  float data[20][2] =
  {
    {-3.14159265358979, 0.00000000000000},
    {-2.81089869005402, -0.43702230525987},
    {-2.48020472651826, -0.78170987707147},
    {-2.14951076298249, -0.85207605602719},
    {-1.81881679944672, -0.52335935447908},
    {-1.48812283591095, 0.22121102681686},
    {-1.15742887237519, 1.27130734031775},
    {-0.82673490883942, 2.41089249371528},
    {-0.49604094530365, 3.37539264122665},
    {-0.16534698176788, 3.92749194128624},
    {0.16534698176788, 3.92749194128624},
    {0.49604094530365, 3.37539264122665},
    {0.82673490883942, 2.41089249371528},
    {1.15742887237519,1.27130734031775},
    {1.48812283591095, 0.22121102681686},
    {1.81881679944672, -0.52335935447908},
    {2.14951076298249, -0.85207605602719},
    {2.48020472651826, -0.78170987707147},
    {2.81089869005402, -0.43702230525987},
    {3.14159265358979, 0.00000000000000}
  };
  //float sol[5] = {0.0};
//  olsPoly(20, data, 4, sol);
//  VectorPrint(5, sol);
  float sol[4][2] = {0};
  olsTrig(20, data, 3, sol);
  MatrixPrint(4, 2, sol);
}
