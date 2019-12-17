#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

void main()
{
    int m,n, i,j;
    printf("Enter size of matrix");
    scanf("%d", &m);
    n=m;
    int mat[m][m], vec[n], res[m];
    for(i=0;i<m;i++)
    {for(j=0;j<m;j++)
     { mat[i][j]= rand()%100;
     }
     res[i]=0;
    }
    for(i=0;i<m;i++)
      vec[i]=rand()%100;
    printf("The matrix is: \n");
    for(i=0;i<m;i++)
    {    for(j=0;j<m;j++)
            printf("%d  ",mat[i][j]);
     printf("\n");
    }
    printf("\nThe vector is:  \n");
    for(i=0;i<n;i++)
    { printf("%d  ", vec[i]);
    }
    printf("\n");
    #pragma omp parallel for num_threads(8)
    for(i=0;i<m;i++)
    {  for(j=0;j<n;j++)
       { res[i]= res[i] + mat[i][j]*vec[i];
       }
    }
    printf("Result after multiplication:  ");
    for(i=0;i<m;i++)
    {printf("%d  ", res[i]);
    }

}
