#include <stdio.h>

int val[256];

int main(void)
{
  int i;
  char num[100000];
  int R, N, bad;

  for (i = '0'; i <= '9'; i++) {
    val[i] = i-'0';
  }
  for (i = 'A'; i <= 'Z'; i++) {
    val[i] = i-'A'+10;
  }
  for (i = 'a'; i <= 'z'; i++) {
    val[i] = i-'a'+36;
  }

  while (scanf("%s", num) == 1) {
    for (N = 2; N <= 62; N++) {
      bad = 0;
      R = 0;
      for (i = 0; num[i]; i++) {
	bad |= val[num[i]] >= N;
	R = (R + val[num[i]]) % (N-1);
      }
      if (bad) {
	continue;
      }
      if (R == 0) {
	printf("%d\n", N);
	break;
      }
    }
    if (N > 62) {
      printf("such number is impossible!\n");
    }
  }

  return 0;
}
