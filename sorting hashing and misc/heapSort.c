#include<stdio.h>
#define SIZE 10

void scanArray(int a[])
{
    int i;
    printf("\n Enter %d values ", SIZE);
    
    for(i =0 ; i< SIZE; i++)
        scanf("%d", &a[i]);
}

void printArray(int a[])
{
    int i;
    printf("\n ");
    
    for(i =0 ; i< SIZE; i++)
        printf(" %d ", a[i]);
}

void reHeapUp(int arr[], int n)
{
    int temp;
    int parent;

    if(n>0)
    {
      parent = (n-1)/2;
      if(arr[n] > arr[parent])
      {//swap
        temp = arr[n];
        arr[n] = arr[parent];
        arr[parent] = temp;
        
        //recursion
        reHeapUp(arr, parent);
      }
    }//if(n > 0)
}

void makeHeap(int arr[])
{
    int i;
    
    for(i = SIZE-1 ; i> 0; i--)
    {
        reHeapUp(arr, i);
    }//for
}

void reHeapDown(int arr[], int n, int max)
{
    int lc, rc, c;
    int temp;
    
    //select the child with greater value
    
    lc = 2*n+1;
    rc = 2*n+2;

    if(rc >= max && lc >= max)
        c = -1;//no child    
    else if(rc >= max)
        c = lc;//left child to be use in comparison
    else if( arr[rc] > arr[lc])
        c = rc;//right child to be use in comparison
    else
        c = lc;//left child to be use in comparison
    
    if(c != -1)
    {
        if(arr[n] < arr[c]) 
        {
            temp = arr[c];
            arr[c] = arr[n];
            arr[n] = temp;
            
            reHeapDown(arr, c, max);
        }
    }
}

void heapSort(int arr[])
{
    int i, temp;
    //convert the array into a heap
    makeHeap(arr);
    
    for(i = SIZE-1; i > 0; i--)
    {
        //exchange arr[i] and arr[0]
        temp = arr[i];
        arr[i] = arr[0];
        arr[0] = temp;
        
        reHeapDown(arr, 0, i);
    }
    
}

int main()
{
   int arr[SIZE]; 
   scanArray(arr);
   printArray(arr);
   heapSort(arr);
   printArray(arr);
   return 0;
}