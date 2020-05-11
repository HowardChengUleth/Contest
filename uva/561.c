/* @JUDGE_ID: 1102NT 561 C "Counting" */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int freq[26][3];

int main(void)
{
  int s, n1, n2, n3, i, j, sum;
  char buffer[2];

  scanf("%d", &s);
  while (s-- > 0) {
    for (i = 0; i < 26; i++) {
      for (j = 0; j < 3; j++) {
	freq[i][j] = 0;
      }
    }

    scanf("%d %d %d", &n1, &n2, &n3);
    for (i = 0; i < n1; i++) {
      scanf("%1s", buffer);
      freq[buffer[0]-'A'][0]++;
    }
    for (i = 0; i < n2; i++) {
      scanf("%1s", buffer);
      freq[buffer[0]-'A'][1]++;
    }
    for (i = 0; i < n3; i++) {
      scanf("%1s", buffer);
      freq[buffer[0]-'A'][2]++;
    }

    sum = 0;
    for (i = 0; i < 26; i++) {
      sum += freq[i][0] * freq[i][1] * freq[i][2];
    }
    printf("%.4f\n", (double)sum * 34.0 / (n1*n2*n3));

  }
  return 0;
}


