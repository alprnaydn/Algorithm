/*Your librarian friend is planning to digitize the catalog of the local library and needs your help. He gives a list of strings to be shown in the online catalog and asks you to sort them in a dictionary-like order. You decide to help him by writing a program that uses the Radix Sort algorithm to sort the given strings.

Problem

In this exam, you are asked to sort the given string array arr with Radix Sort in ascending or descending order depending on the boolean variable ascending and return the number of iterations done in the loops of the Counting Sort algorithm (you need to use Counting Sort as a subroutine in the Radix Sort). size is the number of elements in the string array.


int radix_string_sort(std::string *arr, int size, bool ascending);

 



Constraints and Hints:
Array elements will be strings each of which can contain only the characters as uppercase English letters (i.e. from 'A' to 'Z').
It will be easier to follow the iteration count if you implement your solution by modifying the pseudocodes given in your book.
Different from the Radix Sort algorithm in your book, it is not guaranteed that the strings in the array will always have the same length. (Hint: You can use an extra bucket during Counting Sort to handle strings with different lengths.)
Different than the algorithm for Counting Sort in your book, initialize the count array as int* C = new int[k] and use the fourth loop for copying the array back. That means, you shouldn't count iterations during initialization, but you should count iterations during copying array back. Otherwise, the return value of the function (as the number of iterations) will not be evaluated as correct.
You should count loop iterations in four different loops.
Ascending order means dictionary order. For example, when ascending=true, OGUZ must reside in the result array before OGUZHAN. If ascending=false, it is the other way around.*/




#include <iostream>
#include <fstream>


int counting_sort(std::string* arr, int size, int exp, bool ascending, int* iterations) {
    int k = 27; 

   
    int* C = new int[k];
    
    for(int i=0;i<k;i++){
        C[i]=0;
        
    }
    for(int j=0;j<size;j++){
        if(arr[j].size()<=exp){
            C[0]++;
        }
        else{
            C[arr[j][exp]-64]=C[arr[j][exp]-64]+1;
        }
        
        (*iterations)++;
    }
    for(int i=1;i<k;i++){
        C[i]=C[i]+C[i-1];
        (*iterations)++;
    }
    
    std::string* B = new std::string[size];
    int l=0;
    for(int k=size-1;k>=0;k--,l++){
        B[l]=arr[k];
    }
    
    
    for(int j=size-1;j>=0;j--){
        
        if(arr[j].size()<=exp){
            B[C[0]-1]=arr[j];
            C[0]--;
        }
        else{
            B[C[arr[j][exp]-64]-1]=arr[j];
            C[arr[j][exp]-64]=C[arr[j][exp]-64]-1;
        }
        
        
         
        (*iterations)++;
    }

    
    
    
    for(int i=0;i<size;i++){
        
        arr[i]=B[i];
        (*iterations)++;
        
        
    }
    
    return *iterations;
}


int radix_string_sort(std::string* arr, int size, bool ascending) {
    int max_length = 0;

    
    for (int i = 0; i < size; ++i) {
        max_length = std::max(max_length, static_cast<int>(arr[i].length()));
    }

    int total_iterations = 0;

   
    for (int exp = max_length-1; exp >=0; exp--) {
        counting_sort(arr, size, exp, ascending, &total_iterations);
    }
    
    int s=size-1;
    std::string* M = new std::string[size];
    
    
    for(int k=0;k<size;k++){
        M[k]=arr[k];
    }
    
    if(!ascending){
        for(int i=0;i<size;i++,s--){
            arr[s]=M[i];
        }
    }


    return total_iterations;
}