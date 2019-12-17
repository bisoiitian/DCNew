#include<stdio.h>
#include<omp.h>
#include<stdlib.h>

void mergeSort(int [], int, int, int);
void partition(int [],int, int);

int main()
{
    int list[50];
    int i, size;
    double t1, t2;
    printf("Enter total number of elements:");
    scanf("%d", &size);
    for(i = 0; i < size; i++)
    {
         list[i]=rand()%100;
    }
    omp_set_num_threads(5);
    t1= omp_get_wtime();
    partition(list, 0, size - 1);
    t2= omp_get_wtime();
    printf("After merge sort:\n");
    for(i = 0;i < size; i++)
    {
         printf("%d   ",list[i]);
    }
   printf("Total wait time : %lf", t2-t1);
   return 0;
}

void partition(int list[],int low,int high)
{
    int mid;

    if(low < high)
    {
        mid = (low + high) / 2;
        partition(list, low, mid);
        partition(list, mid + 1, high);
        mergeSort(list, low, mid, high);
    }
}

void mergeSort(int list[],int low,int mid,int high)
{
    int i, mi, k, lo, temp[50];

    lo = low;
    i = low;
    mi = mid + 1;
    #pragma omp sections
    {

     #pragma omp section
     {while ((lo <= mid) && (mi <= high))
      {
        if (list[lo] <= list[mi])
        {
            temp[i] = list[lo];
            lo++;
        }
        else
        {
            temp[i] = list[mi];
            mi++;
        }
        i++;
      }
     }
     #pragma omp section
     {if (lo > mid)
      {
        for (k = mi; k <= high; k++)
        {
            temp[i] = list[k];
            i++;
        }
      }
      else
      {
        for (k = lo; k <= mid; k++)
        {
             temp[i] = list[k];
             i++;
        }
      }
     }
     #pragma omp section
     {for (k = low; k <= high; k++)
      {
        list[k] = temp[k];
      }
     }
    }
}
