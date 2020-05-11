/* @JUDGE_ID: 1102NT 516 C "" */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_factors(int n)
{
  int prime[10000], exponent[10000];
  int num_factors = 0;
  int p;

  if (n % 2 == 0) {
    prime[num_factors] = 2;
    exponent[num_factors] = 0;
    do {
      exponent[num_factors]++;
      n /= 2;
    } while (n % 2 == 0);
    num_factors++;
  }

  for (p = 3; p*p <= n; p += 2) {
    if (n % p == 0) {
      prime[num_factors] = p;
      exponent[num_factors] = 0;
      do {
	exponent[num_factors]++;
	n /= p;
      } while (n % p == 0);
      num_factors++;
    }
  }
  if (n != 1) {
    prime[num_factors] = n;
    exponent[num_factors++] = 1;
  }

  for (num_factors--; num_factors >= 0; num_factors--) {
    printf("%d %d%s", prime[num_factors], exponent[num_factors],
	   num_factors ? " " : "\n");
  }
}

int main(void)
{
  char buffer[1024], *ptr;
  int num, p, e;

  while (fgets(buffer, 1024, stdin) && buffer[0] != '0') {
    num = 1;
    ptr = strtok(buffer, " \n");
    while (ptr) {
      sscanf(ptr, "%d", &p);
      ptr = strtok(0, " \n");
      sscanf(ptr, "%d", &e);
      ptr = strtok(0, " \n");
      while (e-- > 0) {
	num *= p;
      }
    }
    print_factors(num-1);
  }
  return 0;
}
