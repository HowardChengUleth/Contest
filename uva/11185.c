#include <stdio.h>

void print_base3(int N)
{
  if (!N) return;
  print_base3(N / 3);
  printf("%d", N % 3);
}

int main(void)
{
  int N;

  while (scanf("%d", &N) == 1 && N >= 0) {
    if (!N) {
      printf("0\n");
    } else {
      print_base3(N);
      printf("\n");
    }
  }
  return 0;
}
