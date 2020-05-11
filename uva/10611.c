#include <stdio.h>

int h[50000];
int real_n;

void process(int x)
{
  int lo, hi, mid;

  if (x < h[0]) {
    printf("X %d\n", h[0]);
    return;
  } else if (x == h[0]) {
    if (real_n > 1) {
      printf("X %d\n", h[1]);
    } else {
      printf("X X\n");
    }
    return;
  } else if (x > h[real_n-1]) {
    printf("%d X\n", h[real_n-1]);
    return;
  } else if (x == h[real_n-1]) {
    printf("%d X\n", h[real_n-2]);
    return;
  }

  /* invariant: h[lo] < x < h[hi] */
  lo = 0;
  hi = real_n-1;
  while (hi-lo > 1) {
    mid = (hi+lo)/2;
    if (x == h[mid]) {
      printf("%d %d\n", h[mid-1], h[mid+1]);  /* we know it's in range because
						 of the checks initially */
      return;
    } else if (x < h[mid]) {
      hi = mid;
    } else {
      lo = mid;
    }
  }
  printf("%d %d\n", h[lo], h[hi]);

}

int main(void)
{
  int N, i, x;
  int Q;

  scanf("%d", &N);
  for (i = 0; i < N; i++) {
    scanf("%d", h+real_n);
    if (!real_n || h[real_n] != h[real_n-1]) {
      real_n++;
    }
  }

  scanf("%d", &Q);
  for (i = 0; i < Q; i++) {
    scanf("%d", &x);
    process(x);
  }
  return 0;
}
