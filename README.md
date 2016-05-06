# Majority
Find Majority Element Using Min Comparisons and return an index of the majority element or 0 if none.
Given an array of 0's and 1's determine the majority element 
using the fewest calls to the comparison function QCOUNT. The function takes as parameters four elements at a time
and returns the following. 

  0 -> 0's 1's have equal counts. ex. 1100, 0101, 0011

  2 -> 0's 1's have unequal counts, 3-1 ex 0001, 1110, 1101

  4 -> 0's or 1's have 4 elements, ex 1111, 0000

## My Solution

##### Identify Indices
I first attempt to identify two indicies of either 0 or 1 and one index of the other 0 or 1.
Unless the array holds more than 5 consecutive elements from the start then I can indentify the 
elements using two queries. 

##### 1st solution 
Assuming I was able to indentify indices. 
I will refer to class ( 0 or 1 ) in which I identified two as X and the class in which I identified one element Y. 

So X1, X2, Y1 are the indicies that I have saved. 


For the remaining elements I query two at a time with X1 X2. Since X1 & X2 are known it is easy to determine
which class the two elements are. 

This solution uses the following comparisons:

    n=   20,   max=    13,   avg=   11.28
  
    n=  200,   max=   103,   avg=   97.73
  
    n= 2000,   max=  1005,   avg=  985.66


##### 2nd Solution

After identifying the indicies of X1, X2, & Y1 this version queries the remaining elements 4 at a time. 
Based off the result of the comparison I do the following:

  0 -> Increment counters for both X & Y by 2. 
    
    
  2 -> Store Element indicies in an array.
    
  
  4 -> Store Element indicies in an array.
  

After iterating over the entire array, the subarrays of 2's and 4's are processed. 

This solution uses the following comparisons:

    n=    20,   max=    15,   avg=   10.44
  
    n=   200,   max=   105,   avg=   84.47
  
    n=  2000,   max=   894,   avg=  837.90
    

##### Future Improvements
Currently my implementation only splits once from the initial comparison on the entire array. The sub arrays are
quered two elements at a time and classified from one or more additional queries. By writing the functions that process the 
2's & 4's arrays to work recursively and adding a parameter to scale the scoring I would have been able to reduce the number
of comparison further. 






