#include <stdio.h>
#include <math.h>

int main(void)
{
  long long n;
  long long root;

  while (scanf("%lld", &n) == 1 && n) {
    root = (int)floor(sqrt(n));
    if (n == (root-1)*(root-1) || n == root*root || n == (root+1)*(root+1)) {
      printf("yes\n");
    } else {
      printf("no\n");
    }
  }

  return 0;

}
