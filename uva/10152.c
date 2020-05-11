/* @JUDGE_ID: 1102NT 10152 C "" */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

char names[200][100];
int orig[200], new[200];

void doit(int n)
{
   char misplaced[200];
   int i, j;

   for (i = 0; i < n; i++) {
      misplaced[i] = 0;
   }
   for (i = j = n-1; i >= 0; i--) {
      if (orig[i] == new[j]) {
	 j--;
      } else {
	 misplaced[orig[i]] = 1;
      }
   }
   for (i = n-1; i >= 0; i--) {
      if (misplaced[new[i]]) {
	 printf(names[new[i]]);
      }
   }
}

int main(void)
{
   int K, n, i, j;
   char buffer[100];

   scanf("%d", &K);
   while (K-- > 0) {
      scanf("%d\n", &n);
      for (i = 0; i < n; i++) {
	 fgets(names[i], 100, stdin);
	 orig[i] = i;
      }
      for (i = 0; i < n; i++) {
	 fgets(buffer, 100, stdin);
	 new[i] = -1;
	 for (j = 0; j < n && new[i] < 0; j++) {
	    if (!strcmp(names[j], buffer)) {
	       new[i] = j;
	    }
	 }
	 assert(new[i] >= 0);
      }

      doit(n);
      printf("\n");
   }
   return 0;

}
