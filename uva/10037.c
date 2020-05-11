/* @JUDGE_ID: 1102NT 10037 C "" */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int T[1001];

int cmp(const void *a, const void *b)
{
   return *(int *)a - *(int *)b;
}

int doit(int n, int *t, int print)
{
   int t1, t2;

   if (T[n] >= 0 && !print) {
      return T[n];
   }
   
   if (n == 1) {
      if (print) {
	 printf("%d\n", t[0]);
      }
      return T[n] = t[0];
   }
   if (n == 2) {
      if (print) {
	 printf("%d %d\n", t[0], t[1]);
      }
      return T[n] = t[1];
   }
   
   /*  -> t[0], t[1]
       <- t[0]
       -> t[n-2], t[n-1]
       <- t[1] */
   t1 = doit(n-2, t, 0) + t[0] + 2*t[1] + t[n-1];

   /*  -> t[0], t[n-1]
       <- t[0] */
   t2 = doit(n-1, t, 0) + t[0] + t[n-1];

   if (t1 < t2) {
      if (print) {
	 printf("%d %d\n", t[0], t[1]);
	 printf("%d\n", t[0]);
	 printf("%d %d\n", t[n-2], t[n-1]);
	 printf("%d\n", t[1]);
	 doit(n-2, t, 1);
      }
      return T[n] = t1;
   } else {
      if (print) {
	 printf("%d %d\n", t[0], t[n-1]);
	 printf("%d\n", t[0]);
	 doit(n-1, t, 1);
      }
      return T[n] = t2;
   }
}

int main(void)
{
   int cases, n, i, t[1000];
   
   scanf("%d", &cases);
   while (cases-- > 0) {
      scanf("%d", &n);
      for (i = 0; i < n; i++) {
	 scanf("%d", t+i);
      }
      qsort(t, n, sizeof(int), cmp);

      for (i = 0; i <= n; i++) {
	 T[i] = -1;
      }
      doit(n, t, 0);
      printf("%d\n", T[n]);
      doit(n, t, 1);

      if (cases > 0) {
	 printf("\n");
      }
   }
	 
   
   return 0;
}
