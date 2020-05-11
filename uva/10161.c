#include <stdio.h>
#include <math.h>

void solve(int N)
{
  int shell, into, row, col;

  /* first find the "shell" that it is in */
  shell = floor(ceil(sqrt(N))+0.5);

  /* how many are we into this shell */
  into = N - (shell-1)*(shell-1);
  
  /* next determine which direction */
  if (shell % 2) {
    /* start from bottom */
    if (into <= shell) {
      col = shell;
      row = into;
    } else {
      row = shell;
      col = shell - (into - shell);
    }
  } else {
    /* start from the left */
    if (into <= shell) {
      row = shell;
      col = into;
    } else {
      col = shell;
      row = shell - (into - shell);
    }
  }
  printf("%d %d\n", col, row);

}

int main(void)
{
  int N;

  while (scanf("%d", &N) == 1 && N) {
    solve(N);
  }
  return 0;
}
