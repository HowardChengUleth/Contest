/* @JUDGE_ID: 1102NT 10731 C "" */

#include <stdio.h>
#include <stdlib.h>

int graph[26][26];
char seen[26];

int read_case(void)
{
  int n, i, j;
  char c[6][2];

  scanf("%d", &n);
  for (i = 0; i < 26; i++) {
    seen[i] = 0;
    for (j = 0; j < 26; j++) {
      graph[i][j] = 0;
    }
  }

  for (i = 0; i < n; i++) {
    for (j = 0; j < 6; j++) {
      scanf("%s", c[j]);
      seen[c[j][0]-'A'] = 1;
    }
    for (j = 0; j < 5; j++) {
      if (c[5][0] != c[j][0]) {
	graph[c[5][0]-'A'][c[j][0]-'A'] = 1;
      }
    }
  }
  return n;
}

int main(void)
{
  int n, i, j, k;
  char mark[26];
  int first = 1, printed;

  while (n = read_case()) {
    if (!first) {
      printf("\n");
    }
    first = 0;

    for (k = 0; k < 26; k++) {
      for (i = 0; i < 26; i++) {
	for (j = 0; j < 26; j++) {
	  graph[i][j] |= graph[i][k] && graph[k][j];
	}
      }
      mark[k] = 0;
    }

    for (i = 0; i < 26; i++) {
      if (seen[i] && !mark[i]) {
	printf("%c", 'A'+i);
	for (j = i+1; j < 26; j++) {
	  if (graph[i][j] && graph[j][i]) {
	    printf(" %c", 'A'+j);
	    mark[j] = 1;
	    printed = 1;
	  }
	}
	printf("\n");
      }
    }

  }
  return 0;
}
