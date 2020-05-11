#include <stdio.h>
#include <ctype.h>

int check_sol(char *sol, char *guess)
{
  int i;

  for (i = 0; i < 26; i++) {
    if (sol[i] && !guess[i]) {
      return 0;
    }
  }
  return 1;
}

void eat_EOL(void)
{
  int c;

  while ((c = getchar()) != '\n')
    ;
}

void solve(void)
{
  char sol[26], guess[26];
  int i;
  int bad = 0;
  int c;
  
  for (i = 0; i < 26; i++) {
    sol[i] = guess[i] = 0;
  }
  
  while ((c = getchar()) != '\n') {
    if (islower(c)) {
      sol[c-'a'] = 1;
    }
  }
  

  while ((c = getchar()) != '\n') {
    if (!islower(c) || guess[c-'a']) continue;
    guess[c-'a'] = 1;
    if (check_sol(sol, guess)) {
      printf("You win.\n");
      eat_EOL();
      return;
    } else if (!sol[c-'a']) {
      if (++bad == 7) {
	printf("You lose.\n");
	eat_EOL();
	return;
      }
    }
  }
  printf("You chickened out.\n");
}

int main(void)
{
  int round;

  while (scanf("%d\n", &round) == 1 && round != -1) {
    printf("Round %d\n", round);
    solve();
  }
  return 0;
}
