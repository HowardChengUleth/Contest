#include <stdio.h>

int isprime(int n)
{
  int i;

  if (n < 2) {
    return 0;
  }
  if (n == 2) {
    return 1;
  }
  if (n % 2 == 0) {
    return 0;
  }
  for (i = 3; i*i <= n; i += 2) {
    if (n % i == 0) {
      return 0;
    }
  }
  return 1;
}

int main(void)
{
  int T;
  int i, j;
  char line[2001];
  int freq[256];
  int printed;

  scanf("%d", &T);
  for (i = 1; i <= T; i++) {
    printf("Case %d: ", i);
    scanf("%s", line);
    for (j = 0; j < 256; j++) {
      freq[j] = 0;
    }
    for (j = 0; line[j]; j++) {
      freq[line[j]]++;
    }
    printed = 0;
    for (j = 0; j < 256; j++) {
      if (isprime(freq[j])) {
	putchar(j);
	printed = 1;
      }
    }
    if (!printed) {
      printf("empty");
    }
    printf("\n");
  }
  return 0;
}
