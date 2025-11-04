#include <stdlib.h>
#include "index_first_zero.h"
#include "index_last_zero.h"

int sum_between(int size, int arr[]){
    int index_first = index_first_zero(size, arr);
    int index_last = index_last_zero(size, arr);
    int summ=0;
    for(int i=index_first+1; i<=index_last; i++){
        summ += abs(arr[i]);
    }
    return summ;
}