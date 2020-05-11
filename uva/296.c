/* @JUDGE_ID: 1102NT 296 C "" */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int violate(char *guess1, char *guess2, int correct, int misplaced)
{
  int freq1[10], freq2[10];
  int i, c, m;

  c = m = 0;
  for (i = 0; i < 10; i++) {
    freq1[i] = freq2[i] = 0;
  }
  for (i = 0; i < 4; i++) {
    if (guess1[i] == guess2[i]) {
      c++;
    }
    freq1[guess1[i]-'0']++;
    freq2[guess2[i]-'0']++;
  }
  for (i = 0; i < 10; i++) {
    m += (freq1[i] < freq2[i]) ? freq1[i] : freq2[i];
  }
  m -= c;

  return !(c == correct && m == misplaced);
}

void tryall(int G, char guesses[10][5], int correct[10], int misplaced[10])
{
  int i;
  char guess[5], best_guess[5];
  int count = 0;

  guess[4] = 0;
  for (guess[0] = '0'; guess[0] <= '9'; guess[0]++) {
    for (guess[1] = '0'; guess[1] <= '9'; guess[1]++) {
      for (guess[2] = '0'; guess[2] <= '9'; guess[2]++) {
	for (guess[3] = '0'; guess[3] <= '9'; guess[3]++) {
	  for (i = 0; i < G; i++) {
	    if (violate(guess, guesses[i], correct[i], misplaced[i])) {
	      break;
	    }
	  }
	  if (i >= G) {
	    count++;
	    strcpy(best_guess, guess);
	    if (count > 1) {
	      printf("indeterminate\n");
	      return;
	    }
	  }
	}
      }
    }
  }
  if (count == 1) {
    printf("%s\n", best_guess);
  } else {
    printf("impossible\n");
  }
}

int main(void)
{
  int cases;
  int G, i, correct[10], misplaced[10];
  char guesses[10][5];

  scanf("%d", &cases);
  while (cases-- > 0) {
    scanf("%d\n", &G);
    for (i = 0; i < G; i++) {
      scanf("%s %d/%d", guesses[i], correct+i, misplaced+i);
    }
    tryall(G, guesses, correct, misplaced);
  }

  return 0;
}
