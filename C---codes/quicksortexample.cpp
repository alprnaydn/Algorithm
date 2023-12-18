/*Problem

In this exam, you are asked to complete the quickSort() function definition to sort the given array arr in descending order. 

int quickSort(unsigned short* arr, long &swap, double & avg_dist, double & max_dist, bool hoare, bool median_of_3, int size);

You are expected to implement three variants of quickSort() in one function definition as follows:

Quicksort with Lomuto Partitioning is called using the function quickSort() with hoare=false. You should use the Lomuto partitioning algorithm in the partition step. You can find the relevant pseudocode below.
Quicksort with Hoare Partitioning is called using the function quickSort() with hoare=true. You should use the Hoare partitioning algorithm in the partition step. You can find the relevant pseudocode below.
Quicksort with Median of 3 Pivot Selection is called using the function quickSort() with median_of_3=true. Before partitioning, you should select and arrange a better pivot according to the median of 3 pivot selection algorithm. It should work with the above two partitioning algorithms. It is a simple algorithm: First, find the median of the first, last, and middle (same as Hoare's middle, meaning the index floor((size-1)/2)) elements. Then, swap this median with the element in the pivot position before calling the partition function. According to the partitioning algorithm, the pivot position may differ. If a swap occurs, update relevant control variables (swap, avg_dist etc.). Clarification: You are not expected to perform any swap operations if there is no strict median.

For all 3 tasks:
You should sort the array in descending order, count the number of swaps executed during the sorting process, calculate the average distance between swap positions as avg_dist, find the max distance between swap positions as max_dist (both of which are 0 if no swap occurs). Finally, the quickSort() function should return the number of recursive calls.

You may notice that there will be swaps in which both sides are pointed by the same indexes during partitioning. You do not need to handle anything. Just like other swaps, apply the swap, increment your swap variable, and update your average distance.*/


//Code

#include <iostream>

int recursiveCalls = 0;
int axs(int a,int b){
    if(a>b){
        return a-b; 
    }
    else{ 
        return b-a;
    }
}

void Swap(unsigned short* arr,int a,int b,long& swap,double& avg_dist, double& max_dist){
    double tmp;
    int temp=arr[a];
    arr[a]=arr[b]; 
    arr[b]=temp;
    tmp=avg_dist*swap;
    swap++;
    tmp+=axs(a,b);
    avg_dist=double(tmp/swap);
    if(max_dist<axs(a,b)){
        max_dist=axs(a,b);
    } 
    
 
    
}


int lomutoPartition(unsigned short* arr, int low, int high, long& swap, double& avg_dist, double& max_dist,int size) {
    unsigned short pivot = arr[high];
    int i=-1;
    for(int j=0; j<size - 1;j++){
        if(arr[j]>=pivot){
            i++;
            Swap(arr,i,j,swap,avg_dist,max_dist);
            
            
        }
    }
    Swap(arr,i+1,size-1,swap,avg_dist,max_dist);
   
    return i+1;
    
}


int hoarePartition(unsigned short* arr, int low, int high, long& swap, double& avg_dist, double& max_dist,int size) {
    unsigned short pivot = arr[(size-1)/2];
    int i=-1;
    int j=size;
    while(true){
        do{
            j-=1;
        }while(arr[j]<pivot);
        do{
            i+=1;
        }while(arr[i]>pivot);
        
        if(i<j){
            Swap(arr,i,j,swap,avg_dist,max_dist);
        }
        else{
            return j;
        }
    }
    
}


void medianOf3Pivot(unsigned short* arr, long& swap, double& avg_dist, double& max_dist,int x,int size) {
    int first=arr[0];
    int last=arr[size-1];
    int middle=arr[(size-1)/2];
    if((first>last && first < middle )|| (first>middle && first<last)){
        if(x==1){
            Swap(arr,0,(size-1)/2,swap,avg_dist,max_dist);
        }
        else{
            Swap(arr,0,size-1,swap,avg_dist,max_dist);
        }
    }
    
    else if((middle>first && middle<last) || (middle>last && middle<first)){
        if(x==0){
            Swap(arr,(size-1)/2,size-1,swap,avg_dist,max_dist);
        }
    }
    else if((last>middle && last<first) || (last<middle && last>first)){
        if(x==1){
            Swap(arr,size-1,(size-1)/2,swap,avg_dist,max_dist);
        }
    }
}


int quickSort(unsigned short* arr, long& swap, double& avg_dist, double& max_dist, bool hoare, bool median_of_3, int size) {
    int x=0;
    
    if (size <= 1) {
        return recursiveCalls;
    }
    
    if(median_of_3){
        if(hoare)
        {
            x=1;
            medianOf3Pivot(arr,swap,avg_dist,max_dist,x,size);
            
        }
        else{
            medianOf3Pivot(arr,swap,avg_dist,max_dist,x,size);
            
        }
        
    }
    if (hoare) {
        
        int p = hoarePartition(arr, 0, size - 1, swap, avg_dist, max_dist,size);
        quickSort(arr, swap, avg_dist, max_dist, hoare, median_of_3, p + 1);
        recursiveCalls+=1;
        
        quickSort(arr + p + 1, swap, avg_dist, max_dist, hoare, median_of_3, size - p - 1);
        recursiveCalls+=1;
    } else {
        int p = lomutoPartition(arr, 0, size - 1, swap, avg_dist, max_dist,size);
        quickSort(arr, swap, avg_dist, max_dist, hoare, median_of_3, p);
        recursiveCalls+=1;
        quickSort(arr + p + 1, swap, avg_dist, max_dist, hoare, median_of_3, size - p - 1);
        recursiveCalls+=1;
        
    }
   
    return recursiveCalls+1;
}