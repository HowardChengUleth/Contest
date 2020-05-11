#include <stdio.h>

void print_base(int x)
{
  if (!x) {
    return;
  } else if (x == 1) {
    printf("1");
    return;
  } 

  if (x % 2 == 0) {
    print_base(x / (-2));
    printf("0");
  } else {
    print_base((x-1) / (-2));
    printf("1");
  }

}

int main(void)
{
  int N;
  int x, i;

  scanf("%d", &N);
  for (i = 1; i <= N; i++) {
    printf("Case #%d: ", i);
    scanf("%d", &x);
    if (!x) {
      printf("0");
    } else {
      print_base(x);
    }
    printf("\n");
  }
  return 0;
} 
