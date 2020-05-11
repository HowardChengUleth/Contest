/* @JUDGE_ID: 1102NT 10026 C "" */

#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int t, s, index;
} Job;

Job job[1000];

int cmp(const void *a, const void *b)
{
  int fine1, fine2;

  Job *j1 = (Job *)a, *j2 = (Job *)b;
  fine1 = j1->t * j2->s;
  fine2 = j2->t * j1->s;
  if (fine1 == fine2) {
    return j1->index - j2->index;
  } else {
    return fine1 - fine2;
  }
}

int main(void)
{
  int cases, n, i;

  scanf("%d", &cases);
  while (cases-- > 0) {
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
      scanf("%d %d", &(job[i].t), &(job[i].s));
      job[i].index = i+1;
    }
    qsort(job, n, sizeof(Job), cmp);
    printf("%d", job[0].index);
    for (i = 1; i < n; i++) {
      printf(" %d", job[i].index);
    }
    printf("\n");
    if (cases > 0) {
      printf("\n");
    }
  }
  return 0;
}
