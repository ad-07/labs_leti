
int index_last_zero(int size, int arr[]){
    for(int i = size-1; i>=0;--i){
        if (arr[i] == 0 ){
          return i;
      }
    }
    return -1;
}