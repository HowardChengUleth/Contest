/* @JUDGE_ID: 1102NT 612 C "" */

#include <stdio.h>7
#include <string.h>

typedef struct {
  char s[51];
  int inv, index;
} str;

str A[100];
int m, n;

int cmp(const void *a, const void *b)
{
  const str *s1 = (str *)a, *s2 = (str *)b;

  if (s1->inv != s2->inv) {
    return s1->inv - s2->inv;
  } else {
    return s1->index - s2->index;
  }
}

int main(void)
{
  int T, i, j, k;

  scanf("%d", &T);
  while (T-- > 0) {
    scanf("%d %d", &n, &m);
    for (i = 0; i < m; i++) {
      scanf("%s", &(A[i].s));
      A[i].index = i;
      A[i].inv = 0;
      for (j = 0; j < n; j++) {
	for (k = j+1; k < n; k++) {
	  if (A[i].s[j] > A[i].s[k]) {
	    A[i].inv++;
	  }
	}
      }
    }

    qsort(A, m, sizeof(str), cmp);
    for (i = 0; i < m; i++) {
      printf("%s\n", A[i].s);
    }
    
    if (T > 0) {
      printf("\n");
    }
  }
  return 0;
}
