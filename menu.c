#include "sum_between.h"
#include "sum_before_and_after.h"
#include "index_first_zero.h"
#include "index_last_zero.h"

int main()
{
  int s1, code, index_first = -1, index_last, id = 0;
  int arr[100];
  scanf("%d", &s1);
  code = s1;
  while (scanf("%d", &s1) == 1){
    arr[id] = s1;
    id++;
  }
  switch (code){
  case 0:
    printf("%d\n", index_first_zero(id, arr));
    break;
  case 1:
    printf("%d\n", index_last_zero(id, arr));  
    break;
  case 2:
    printf("%d\n", sum_between(id, arr));
    break;  
  case 3:
    printf("%d\n", sum_before_and_after(id, arr));
    break;
  default:
    printf("Данные некорректны\n");
}
}