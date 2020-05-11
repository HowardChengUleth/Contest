#include <stdio.h>

void solve(int N)
{
  int ring;
  int start_x, start_y, i, j, times;

  /* directions for SW, NW, N, NE, SE, S */
  int dx[6] = { -1, -1,  0,  1, 1, 0};
  int dy[6] = {  1,  0, -1, -1, 0, 1};
  
  for (ring = 0; N > 1 + 3*ring*(ring+1); ring++)
    ;

  if (!ring) {
    printf("0 0\n");
    return;
  }
  N -= 1 + 3*ring*(ring-1) + 1;
  start_x = ring-1;
  start_y = 1;

  for (j = 0; j < 6 && N > 0; j++) {
    times = (j) ? ring : ring-1;
    for (i = 0; N > 0 && i < times; i++) {
      start_x += dx[j];
      start_y += dy[j];
      N--;
    }
  }
  
  printf("%d %d\n", start_x, start_y);

}

int main(void)
{
  int N;

  while (scanf("%d", &N) == 1) {
    solve(N);
  }
  return 0;
}
