#include <stdio.h>

typedef struct {
  long long a, b;
} Complex;

int main(void)
{
  int M, N;
  Complex x, y;
  long long ta, tb;

  scanf("%d", &M);

  while (M-- > 0) {
    scanf("%lld %lld", &x.a, &x.b);
    y = x;

    /* no need to worry about infinite loop: the only way x's magnitude
       does not increase is if the magnitude is 1, but those would stop
       quickly */
    for (N = 1; x.a*x.a+x.b+x.b <= (1LL << 60) && x.b; N++) {
      ta = x.a * y.a - x.b * y.b;
      tb = x.a * y.b + x.b * y.a;
      x.a = ta;
      x.b = tb;
    }
    if (x.b) {
      printf("TOO COMPLICATED\n");
    } else {
      printf("%d\n", N);
    }
  }
  
  return 0;
}
