#include <stdio.h>
#include <stdlib.h>

int r, c;
int count;

int cmp(const void *a, const void *b)
{
  return *(int *)a - *(int *)b;
}

int check(int perm[], int start)
{
  int i;
  int vdiff, hdiff;

  for (i = 1; i < start; i++) {
    hdiff = start - i + (i < c && start >= c);
    vdiff = abs(perm[i] - perm[start]);
    if (hdiff == vdiff) {
      return 0;
    }
  }
  hdiff = abs(start + (start >= c) - c);
  vdiff = abs(perm[start] - r);
  return hdiff != vdiff;
}

void search(int perm[], int start, int n)
{
  int k;

  if (start > n) {
    printf("%2d     ", ++count);
    for (k = 1; k < c; k++) {
      printf("%2d", perm[k]);
    }
    printf("%2d", r);
    for (k = c; k <= n; k++) {
      printf("%2d", perm[k]);
    }
    printf("\n");
    return;
  }

  for (k = start; k <= n; k++) {
    int t = perm[k];
    perm[k] = perm[start];
    perm[start] = t;
    if (check(perm, start)) {
      search(perm, start+1, n);
    }
  }
  qsort(perm+start, (n-start+1), sizeof(*perm), cmp);
}

int main(void)
{
  int N, i, j;
  int perm[8];

  scanf("%d", &N);

  for (i = 0; i < N; i++) {
    printf("SOLN       COLUMN\n");
    printf(" #      1 2 3 4 5 6 7 8\n\n");

    scanf("%d %d", &r, &c);

    for (j = 1; j <= 7; j++) {
      perm[j] = (j < r) ? j : j+1;
    }

    count = 0;
    search(perm, 1, 7);
    
    if (i < N-1) {
      printf("\n");
    }
  }
  return 0;
}
