#include <stdio.h>

int min(int a, int b)
{
  return (a < b) ? a : b;
}

int knight(int m, int n)
{
  if (m > n) {
    return knight(n, m);
  }

  if (m == 1) {
    return n;
  }
  if (m == 2) {
    return 4*((n-1)/4) + 2*min(2, ((n-1) % 4)+1);
  }
  
  /* either all the white or all the black squares */
  return (m*n % 2 == 0) ? (m*n)/2 : (m*n+1)/2;
}

int main(void)
{
  int m, n;

  while (scanf("%d %d", &m, &n) == 2 && (m || n)) {
    printf("%d knights may be placed on a %d row %d column board.\n", knight(m, n), m, n);
  }
  
  return 0;
}
