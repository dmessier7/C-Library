#include <stdio.h>
#include <math.h>

int count;

int Hilbert(int rows, float b[rows], float mat[rows][rows])
{
  int n = rows;
  int m = rows+1;
  for(int i = 0; i<n; i++)
  {
    float a = 0;
    for (int j = 0; j<n; j++)
    {
      mat[i][j] = 1.0/((i+1)+(j+1)-1);
      a += mat[i][j];
    //  printf("%0.4f,\n", aug[i][j]);
    }
    b[i] = a;
  //  printf("%0.4f,\n", aug[i][n]);
  }
  return 0;
}

float DotProduct(int length, float v1[length], float v2[length])
{
  float sum = 0;
  for(int i =0; i<length; i++)
  {
    sum += (v1[i]*v2[i]);
  }
  return sum;
}

int MatrixApply(int length, float mat[length][length], float applied[length], float vec[length])
{
  for(int i = 0; i<length; i++)
  {
    float sum = 0;
    for(int k=0; k<length; k++)
    {
      sum += mat[i][k]*vec[k];
    }
    applied[i] = sum;
  }
  return 0;
}

int r2v(int length, float v[length], float r[length])
{
  for(int i=0; i<length; i++)
  {
    v[i] = -1.0*r[i];
  }
  return 0;
}

float infNorm(int length, float vec[length])
{
  float norm = 0.0;
  for(int i =0; i<length; i++)
  {
    if(fabs(vec[i]) > norm)
    {
      norm = fabs(vec[i]);
    }
  }
  return norm;
}

int zeroOut(int length, float vec[length])
{
  for(int j = 0; j<length ;j++)
  {
    vec[j] = 0.0;
  }
  return 0;
}

int conjugateMethod(int length, float H[length][length], float e, float guess[length], float b[length])
{
  int steps = 0;
  float acceptable = pow(10.0, e);
  float error = 100.0;
  float r[length];
  float v[length];
  float Hv[length];
  while (error > acceptable)
  {
    zeroOut(length, r);
    zeroOut(length, v);
    zeroOut(length, Hv);
    //Obtain Residual, r
    MatrixApply(length, H, r, guess);
    for(int i =0; i<length; i++)
    {
      r[i] -= b[i];
    }
    error = infNorm(length, r);
    if(error < acceptable)
      {
        printf("%f\n", error);
        break;
      }
    steps++;
    r2v(length, v, r); //Obtain v
    //Obtain t
    float numerator = DotProduct(length, r, v);
    MatrixApply(length, H, Hv, v);
    float denominator = DotProduct(length, Hv, v);
    float t = -1.0*(numerator/denominator);
    //Update guess
    for(int k=0; k<length;k++)
    {
      guess[k] += (t*v[k]);
    }
  }
  printf("steps: %d\n", steps);
  return 0;
}

int MatrixPrint(int rows, int columns, float aug[rows][columns])
{
  int n = rows;
  int m = columns;
  for(int i = 0; i<n; i++)
  {
    for (int j = 0; j<m; j++)
    {
      printf("%d,", i);
      printf("%d, ", j);
      printf("%0.10f,", aug[i][j]);
      printf("\n");
    }
  }
  return 0;
}

int VectorPrint(int size, float vec[size])
{
  printf("[");
  for(int i=0;i<size;i++)
  {
    printf("%0.10f, ", vec[i]);
  }
  printf("]\n");
  return 0;
}

int GaussianE(int rows, float aug[rows][rows+1])
{
  int n = rows;
  int m = rows+1;
  for(int i = 0; i<n-1; i++)
  {
    if(aug[i][i] == 0.0) //check if current pivot is 0
    {
      for(int k = i+1; k<n; k++) //go through each row below to check for first non zero
      {
        if(aug[k][i] != 0.0)
        {
          float vect[n-i+1]; //create vector to temporarily store current row
          for(int j = i; j<m; j++) //store current row in vector
          {
        //    printf("%d, ", j);
          //  printf("%d, ", j-i);
            vect[j-i] = aug[i][j];
          //  printf("%0.4f\n", vect[j-i]);
          }
          for(int j = i; j<m; j++) //put new row into current row's place
          {
             aug[i][j] = aug[k][j];
          }
          for(int j = i; j<m; j++) //put current row into the new row's place
          {
            aug[k][j] = vect[j-i];
          }
          k=n;
        }
      }
    }
    for(int j = i+1; j<n; j++)
    {
      if(aug[j][i] != 0.0) //skips rows if value below pivot is already zero
      {
      float ratio = aug[j][i]/aug[i][i];
      aug[j][i] = 0.0; // sets value below pivot equal to zero instead of doing actual calculaiton
      count++;
      for(int k= i+1; k<m; k++)
      {
      //  printf("%d,", i);
      //  printf("%d,", j);
      //  printf("%d,\n", k);
        aug[j][k] -= (ratio*aug[i][k]);
        count++;
        }
      }
    }

  }
  return 0;
}

int GaussianPartial(int rows, float aug[rows][rows+1])
{
  int n = rows;
  int m = rows+1;
  for(int i = 0; i<n-1; i++)
  {
    float h = aug[i][i];
    int g = i;
    for(int j=i+1; j<n; j++) //find row with largest possible pivot
    {
      if(aug[j][i]>h)
      {
        g = j;
        h = aug[j][i];
      }
    }
    float vect[m-i]; //create vector to temporarily store current row
    for(int j = i; j<m; j++) //store current row in vector
    {
      vect[j-i] = aug[i][j];
    }
    for(int j = i; j<m; j++) //put new row into current row's place
    {
       aug[i][j] = aug[g][j];
    }
    for(int j = i; j<m; j++) //put current row into the new row's place
    {
      aug[g][j] = vect[j-i];
    }

    for(int j = i+1; j<n; j++)
    {
      if(aug[j][i] != 0.0) //skips rows if value below pivot is already zero
      {
        float ratio = aug[j][i]/aug[i][i];
      //  printf("%.10f\n", aug[i][i]);
        aug[j][i] = 0.0; // sets value below pivot equal to zero instead of doing actual calculaiton
        count++;
        for(int k= i+1; k<m; k++)
        {
      //  printf("%d,", i);
      //  printf("%d,", j);
      //  printf("%d,\n", k);
          aug[j][k] -= (ratio*aug[i][k]);
          count++;
          }
      }
    }

  }
  return 0;
}



int Backsub(int rows, float aug[rows][rows+1], float sol[rows])
{
  int n = rows;
  sol[n-1] = aug[n-1][n]/aug[n-1][n-1];
  count++;
  //printf("%0.4f,\n", sol[n-1]);
  for(int i = n-2; i >=0; i-=1)
  {
    float x = aug[i][n];
    float sum = 0;
    for(int j=i+1; j<n; j++)
    {
      sum+= aug[i][j]*sol[j];
      count++;
    }
    x -= sum;
    x = x/aug[i][i];
    count++;
    sol[i] = x;
  //  printf("%0.4f,\n", sol[i]);
  }
  return 0;
}


float Error(int size, float vec[size], float vec2[size])
{
  //Error Vector
  float error[size];
//  printf("Error Vector for n = %d: [", size);
  for (int i = 0; i<size; i++)
  {
    error[i] = vec[i] - vec2[i];
//    printf("%0.4f, ", error[i]);
  }
//  printf("]\n");
  // Norms
  float in = 0;
  float euc = 0;
  for (int k = 0; k<size; k++)
  {
    if(fabsf(error[k])>in){in = fabsf(error[k]);}
    euc += pow(error[k], 2.0);
  }
  euc = sqrt(euc);
//  printf("Infinity Norm of Error Vector for n = %d: %0.4f \n", size, in);
//  printf("Euclidian Norm of Error Vector for n = %d: %0.4f \n", size, euc);
  return euc;
}

int Jacobi(int rows, float tole, int N, float aug[rows][rows+1], float x[rows])
{
  int k = 0;
  double min = pow(10.0, tole);
  float xa[rows];
  float xb[rows];
  for(int l = 0; l<rows; l++)
  {
    xa[l] = x[l];
  }
  for(int g = 0; g<rows; g++)
  {
    xb[g] = x[g];
  }
  while (k<N)
  {
    for(int g = 0; g<rows; g++)
    {
      xa[g] = xb[g];
    }
    for(int i=0; i < rows; i++)
    {
      float sum = 0;
      for(int j=0; j<rows; j++)
      {
        if(j != i){sum -= aug[i][j]*xa[j];}
      }
      xb[i] = (sum + aug[i][rows+1])/aug[i][i];
    }
    if(Error(rows, xa, xb)<min){break;}
    k++;
  }
  for(int g = 0; g<rows; g++)
  {
    x[g] = xb[g];
  }
  printf("Computated Solution ");
  VectorPrint(rows, x);
  return 0;
}
/*
int main()
{
  int n = 5;
  float aa[5][6] =
  {
    {4.0,1.0,1.0,0.0,1.0,6.0},
    {-1.0,3.0,1.0,1.0,0.0,6.0},
    {2.0,1.0,5.0,-1.0,-1.0,6.0},
    {-1.0,-1.0,-1.0,4.0,0.0,6.0},
    {0.0,2.0,-1.0,1.0,4.0,6.0}
  };
  float ab[3][4] =
  {
    {4.0, -1.0, 1.0, 8.0},
    {2.0,5.0,2.0,3.0},
    {1.0,2.0,4.0,11.0}
  };
  float abb[3][4] =
  {
    {1.0, 1.0, -1.0,1.0},
    {1.0,1.0,4.0,2.0},
    {2.0,-1.0,2.0,3.0}
  };
//  float sol[3] = {0.0};
//  GaussianE(3, abb);
//  GaussianPartial(3, abb);
//  MatrixPrint(3, abb);
//  Backsub(3, abb, sol);
//  VectorPrint(3, sol);
  int l = 20;
  float hil[20][20] = {0};
  float b[20] = {0};
  Hilbert(20, b, hil);
  float guess[20] = {0};
  guess[0] = 1.0;
  conjugateMethod(20, hil, -3.0, guess, b);

  VectorPrint(20,guess);


//  float guess[5] = {0};
//  Jacobi(n, -2.0, 100, aa, guess);
  //HilbertSolve(n);

};*/
