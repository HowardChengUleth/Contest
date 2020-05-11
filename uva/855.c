/* @JUDGE_ID: 1102NT 855 C "" */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int cmp(const void *a, const void *b)
{
  return *(int *)a - *(int *)b;
}

int main(void)
{
  int T, F;
  int s[50000], a[50000];
  int i;
  int meds, meda;

  scanf("%d\n", &T);
  while (T-- > 0) {
    scanf("%*d %*d %d", &F);
    assert(0 < F && F <= 50000);
    for (i = 0; i < F; i++) {
      scanf("%d %d", s+i, a+i);
      assert(1 <= s[i] && s[i] <= 1000 && 1 <= a[i] && a[i] <= 1000);
    }
    qsort(s, F, sizeof(int), cmp);
    qsort(a, F, sizeof(int), cmp);
    if (F % 2) {
      meds = s[F/2];
      meda = a[F/2];
    } else {
      /* when F is even, any number between [F/2-1] and [F/2] would do, so */
      /* pick the smaller one                                              */
      meds = s[F/2-1];
      meda = a[F/2-1];
    }
    printf("(Street: %d, Avenue: %d)\n", meds, meda);
  }
  return 0;

}
