#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* left[n] = index of unsafe position with n people if we start counting
             to the left.
   right[n] = same thing start counting to the right.
*/

int left[1000001], right[1000001];

void init(void)
{
  int n;

  left[1] = right[1] = 0;

  for (n = 2; n <= 1000000; n++) {
    /* first try counting to the right */
    right[n] = (15+right[n-1])%n;

    /* count to the left */
    left[n] = (n - right[n]) % n;
  }
}

int main(void)
{
  int L, U;
  char map[1000001];
  int i;

  init();
  while (scanf("%d %d", &L, &U) == 2 && (L || U)) {
    if (U < L) {
      i = U;
      U = L;
      L = i;
    }

    memset(map, 0, U);
    for (i = L; i <= U; i++) {
      map[left[i]] = map[right[i]] = 1;
    }
    for (i = 1; i < L/2; i++) {
      if (!map[i]) {
	printf("%d\n", i);
	break;
      }
    }
    if (i >= L/2) {
      printf("Better estimate needed\n");
    }
  }
  
  return 0;
}
