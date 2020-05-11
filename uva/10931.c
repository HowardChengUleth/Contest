#include <stdio.h>


int parity(int n)
{
  int bit;
  int p;

  if (!n) return 0;

  bit = n % 2;
  p = parity(n/2) + bit;
  printf("%d", bit);
  return p;
}

int main(void)
{
  int n;
  int p;
  
  while (scanf("%d", &n) == 1 && n) {
    printf("The parity of ");
    p = parity(n);
    printf(" is %d (mod 2).\n", p);
  }
  return 0;
}
