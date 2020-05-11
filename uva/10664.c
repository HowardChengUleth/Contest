#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char poss[20][201];
int w[20];
int total;
int n;

int main(void)
{
  int m;
  char line[1000], *p;
  int i, j;

  scanf("%d\n", &m);
  while (m-- > 0) {
    fgets(line, 1000, stdin);
    
    n = 0;
    total = 0;
    for (p = line; p = strtok(p, " \n"); p = NULL) {
      total += (w[n++] = atoi(p));
    }

    if (total % 2 != 0) {
      printf("NO\n");
      continue;
    }

    for (i = 0; i < n; i++) {
      for (j = 0; j <= total/2; j++) {
	poss[i][j] = 0;
      }
    }
    poss[0][0] = poss[0][w[0]] = 1;
    for (i = 1; i < n; i++) {
      for (j = 0; j <= total/2; j++) {
	if (!poss[i-1][j]) continue;
	poss[i][j] = 1;
	if (j + w[i] <= total/2) {
	  poss[i][j+w[i]] = 1;
	}
      }
    }
      
    printf("%s\n", (poss[n-1][total/2] ? "YES" : "NO"));
  }

  return 0;
}
