/* @JUDGE_ID: 1102NT 10142 C "" */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char name[20][100];
int votes[1001][20];
char elim[20];
int votefor[20];
int n, num_votes;

void solve_case(void)
{
  int i, j;
  int max_vote, min_vote;
  char buffer[1024];

  scanf("%d\n", &n);
  for (i = 0; i < n; i++) {
    fgets(name[i], 100, stdin);
  }
  memset(elim, 0, n);
  num_votes = 0;
  while (fgets(buffer, 1024, stdin) && buffer[0] != '\n') {
    votes[num_votes][0] = atoi(strtok(buffer, " \n"));
    for (i = 1; i < n; i++) {
      votes[num_votes][i] = atoi(strtok(0, " \n"));
    }
    num_votes++;
  }

  while (1) {
    /* get the votes for each candidate */
    for (i = 0; i < n; i++) {
      votefor[i] = 0;
    }
    for (i = 0; i < num_votes; i++) {
      for (j = 0; j < n; j++) {
	if (!elim[votes[i][j]-1]) {
	  votefor[votes[i][j]-1]++;
	  break;
	}
      }
    }

    /* now find the winner */
    max_vote = min_vote = -1;
    for (i = 0; i < n; i++) {
      if (elim[i]) continue;
      if (max_vote < votefor[i]) max_vote = votefor[i];
      if (min_vote == -1 || min_vote > votefor[i]) min_vote = votefor[i];
    }

    if (min_vote == max_vote || max_vote > num_votes/2) {
      for (i = 0; i < n; i++) {
	if (!elim[i] && votefor[i] == max_vote) {
	  printf("%s", name[i]);
	}
      }
      break;
    }
    
    /* eliminate */
    for (i = 0; i < n; i++) {
      if (elim[i]) continue;
      if (votefor[i] == min_vote) {
	elim[i] = 1;
      }
    }
  }
}

int main(void)
{
  int cases;

  scanf("%d", &cases);
  while (cases-- > 0) {
    solve_case();
    if (cases) {
      printf("\n");
    }
  }
  return 0;
}
