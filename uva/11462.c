#include <stdio.h>

int freq[101];

int main(void)
{
  int n, i, age;

  while (scanf("%d", &n) == 1 && n) {
    while (n-- > 0) {
      scanf("%d", &age);
      freq[age]++;
    }
    
    /* unrolled to make it faster */
    for (i = 1; !freq[i]; i++)
      ;
    printf("%d", i);
    freq[i]--;
    
    for (; i < 100; i++) {
      while (freq[i] > 0) {
	printf(" %d", i);
	freq[i]--;
      }
    }
    printf("\n");
  }
  return 0;
}
