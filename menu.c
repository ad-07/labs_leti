#include "sum_between.h"
#include "sum_before_and_after.h"
#include "index_first_zero.h"
#include "index_last_zero.h"

int main()
{
  int arr_size = 100;
  int num, code, id = 0;
  int arr[arr_size];
  scanf("%d", &num);
  code = num;
  while (scanf("%d", &num) == 1){
    arr[id] = num;
    id++;
  }

  int size = id; //количество элементов в массиве
  switch (code){
  case 0:
    printf("%d\n", index_first_zero(size, arr));
    break;
  case 1:
    printf("%d\n", index_last_zero(size, arr));  
    break;
  case 2:
    printf("%d\n", sum_between(size, arr));
    break;  
  case 3:
    printf("%d\n", sum_before_and_after(size, arr));
    break;
  default:
    printf("Данные некорректны\n");
}
}