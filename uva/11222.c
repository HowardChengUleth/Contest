#include <stdio.h>

int main(void)
{
  int T;
  int i, j, k, n;
  int probs[10001];
  int count[4];
  int M;
  

  scanf("%d", &T);
  for (i = 0; i < T; i++) {
    printf("Case #%d:\n", i+1);
    for (j = 0; j < 10001; j++) {
      probs[j] = 0;
    }

    for (k = 1; k <= 3; k++) {
      count[k] = 0;
      scanf("%d", &n);
      while (n-- > 0) {
	scanf("%d", &j);
	if (!probs[j]) {
	  probs[j] = k;
	  count[k]++;
	} else {
	  count[probs[j]]--;
	  probs[j] = -1;
	}
      }
    }
    M = (count[1] > count[2]) ? count[1] : count[2];
    M = (M > count[3]) ? M : count[3];
    for (k = 1; k <= 3; k++) {
      if (count[k] == M) {
	printf("%d %d", k, count[k]);
	for (j = 1; j <= 10000; j++) {
	  if (probs[j] == k) {
	    printf(" %d", j);
	  }
	}
	printf("\n");
      }
    }
    

  }

  return 0;
}
