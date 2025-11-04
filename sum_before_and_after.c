#include <stdlib.h>
#include "index_first_zero.h"
#include "index_last_zero.h"


int sum_before_and_after(int size, int arr[]){
    int summ;
    int index_first = index_first_zero(size, arr);
    int index_last = index_last_zero(size, arr);
    for(int i=0; i<index_first; i++){
        summ += abs(arr[i]);
    }
    for(int i=index_last; i<size; i++){
        summ += abs(arr[i]);
    }
    return summ;
}