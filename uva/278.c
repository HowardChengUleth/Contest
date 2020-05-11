#include <stdio.h>

int rook(int m, int n)
{
  return (m < n) ? m : n;
}

int king(int m, int n)
{
  return ((m+1)/2) * ((n+1)/2);
}

int queen(int m, int n)
{
  return (m < n) ? m : n;
}

int knight(int m, int n)
{
  /* either all the white or all the black squares */
  
  return (m*n % 2 == 0) ? (m*n)/2 : (m*n+1)/2;

}

int main(void)
{
  char type;
  int m, n;
  int N;

  scanf("%d", &N);
  while (N-- > 0) {
    scanf(" %c %d %d", &type, &m, &n);
    switch (type) {
    case 'r':
      printf("%d\n", rook(m, n));
      break;
    case 'k':
      printf("%d\n", knight(m, n));
      break;
    case 'Q':
      printf("%d\n", queen(m, n));
      break;
    case 'K':
      printf("%d\n", king(m, n));
      break;
    }
  }
  
  return 0;
}
