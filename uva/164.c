/* @JUDGE_ID: 1102NT 164 C "" */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_LEN 20

int dist[MAX_LEN+1][MAX_LEN+1];
int soln[MAX_LEN+1][MAX_LEN+1];

enum { INSERT, DELETE, CHANGE, NONE };

void calc_dist(char *word1, char *word2)
{
  int n1, n2;
  int i, j, best;
  
  n1 = strlen(word1);
  n2 = strlen(word2);
  assert(n1 <= MAX_LEN && n2 <= MAX_LEN);
  
  for (i = 0; i <= n1; i++) {
    for (j = 0; j <= n2; j++) {
      dist[i][j] = -1;
    }
  }
  dist[0][0] = 0;
  soln[0][0] = NONE;
  for (j = 1; j <= n2; j++) {
    dist[0][j] = j;
    soln[0][j] = INSERT;
  }
  for (i = 1; i <= n1; i++) {
    dist[i][0] = i;
    soln[i][0] = DELETE;
  }
  
  for (i = 1; i <= n1; i++) {
    for (j = 1; j <= n2; j++) {
      if (word1[i-1] == word2[j-1]) {
	dist[i][j] = dist[i-1][j-1];
	soln[i][j] = NONE;
      } else {
	/* NOTE: the online judge doesn't accept all valid solutions... */
	/*       you need to break ties by using inserts last           */
	best = dist[i][j-1];            /* insert */
	soln[i][j] = INSERT;
	if (dist[i-1][j-1] <= best) {
	  best = dist[i-1][j-1];        /* change */
	  soln[i][j] = CHANGE;
	}
	if (dist[i-1][j] <= best) {
	  best = dist[i-1][j];          /* delete */
	  soln[i][j] = DELETE;
	}
	dist[i][j] = best+1;
      }
    }
  }

  i = n1; j = n2;
  while (i >= 0 && j >= 0) {
    if (soln[i][j] == NONE) {
      i--; j--;
    } else if (soln[i][j] == INSERT) {
      printf("I%c%02d", word2[j-1], i+1);
      j--;
    } else if (soln[i][j] == CHANGE) {
      printf("C%c%02d", word2[j-1], i);
      i--; j--;
    } else {
      assert(soln[i][j] == DELETE);
      printf("D%c%02d", word1[i-1], i);
      i--;
    }
  }
  printf("E\n");
}

int main(void)
{
  char word1[MAX_LEN+1], word2[MAX_LEN+1];
  char line[1024];

  while (fgets(line, 1024, stdin) && strcmp(line, "#\n")) {
    assert(sscanf(line, "%s %s", word1, word2) == 2);
    calc_dist(word1, word2);
  }
  return 0;
}
