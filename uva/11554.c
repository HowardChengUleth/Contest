#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main() {
  long long nc, n, T;

  scanf("%lld",&nc);
  for(; nc>0; --nc) {
    scanf("%lld",&n);
    T = n/2;
    printf("%lld\n", (n-1-T)*(n*n - 2*n*T - 2*n + 4*T*T - T)/6);
  }

  return 0;
}
