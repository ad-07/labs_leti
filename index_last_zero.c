
int index_last_zero(int id, int arr[]){
    for(int i = id-1; i>=0;--i){
        if (arr[i] == 0 ){
          return i;
      }
    }
    return -1;
}