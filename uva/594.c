#include <stdio.h>

int main(void)
{
  long long n, to;
  int bytes[4];
  int i;

  while (scanf("%lld", &n) == 1) {
    printf("%lld converts to ", n);
    if (n < 0) {
      n = (1LL << 32) + n;
    }
    for (i = 0; i < 4; i++) {
      bytes[i] = n & 0xFF;
      n >>= 8;
    }

    to = 0;
    for (i = 0; i < 4; i++) {
      to = (to << 8) | bytes[i];
    }
    if (to >= (1LL << 31)) {
      to = -((1LL << 32) - to);
    }
    printf("%lld\n", to);
  }

  return 0;
}
