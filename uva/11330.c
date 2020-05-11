/*
 * I used cycle decomposition: a completely sorted array has n 1-cycles.
 * If two elements in a cycle is swapped, the cycle is broken into 2.
 * So each swap can increase the number of cycles by 1, and we need to
 * increase it to n: the number of swaps needed is n - number of cycles
 * in the original matrix
 */

#include <stdio.h>

int list1[10000], list2[10000];
int labels[10001];
char marked[10001];
int n;

int main(void)
{
  int k;
  int i, j;
  int cycles;

  scanf("%d", &k);
  while (k-- > 0) {
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
      scanf("%d %d", list1+i, list2+i);
    }
    
    /* relabel the ones in list 2, using the ordering implied in list1 */
    for (i = 0; i < n; i++) {
      labels[list1[i]] = i;
    }
    for (i = 0; i < n; i++) {
      list2[i] = labels[list2[i]];
      marked[i] = 0;
    }
    
    /* count the number of cycles in cycle decomposition */
    cycles = 0;
    for (i = 0; i < n; i++) {
      if (!marked[i]) {
	marked[i] = 1;
	j = list2[i];
	while (!marked[j]) {
	  marked[j] = 1;
	  j = list2[j];
	}
	cycles++;
      }
    }

    /* completely sorted means you have n cycles.  Each swap increases
       cycles by 1 */
    printf("%d\n", n - cycles);
  }

  return 0;
}
