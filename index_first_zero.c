
int index_first_zero(int id, int arr[]){
    
    for(int i = 0; i<id;++i){
        if (arr[i] == 0 ){
          return i;
      }
    }
    return -1;
}