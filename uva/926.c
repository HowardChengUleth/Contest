#include <stdio.h>
#include <assert.h>

void solve(void)
{
  int N;
  char left[31][31], down[31][31];
  int i, j;
  int W;
  int Ax, Ay, Bx, By, Px, Py;
  char dir;
  unsigned long long ways[31][31];

  scanf("%d", &N);

  for (i = 1; i <= N; i++) {
    for (j = 1; j <= N; j++) {
      left[i][j] = down[i][j] = 1;
    }
  }

  scanf("%d %d %d %d", &Ax, &Ay, &Bx, &By);
  scanf("%d", &W);
  for (i = 0; i < W; i++) {
    scanf("%d %d %c", &Px, &Py, &dir);
    switch (dir) {
    case 'N':
      down[Px][Py+1] = 0;
      break;
    case 'S':
      down[Px][Py] = 0;
      break;
    case 'E':
      left[Px+1][Py] = 0;
      break;
    case 'W':
      left[Px][Py] = 0;
      break;
    default:
      assert(0);
    }
  }

  ways[Ax][Ay] = 1;
  for (i = Ax; i <= Bx; i++) {
    for (j = Ay; j <= By; j++) {
      if (i == Ax && j == Ay) continue;
      ways[i][j] = 0;
      if (i > Ax && left[i][j]) {
	ways[i][j] += ways[i-1][j];
      }
      if (j > Ay && down[i][j]) {
	ways[i][j] += ways[i][j-1];
      }
    }
  }
  printf("%llu\n", ways[Bx][By]);
}

int main(void)
{

  int C;
  
  scanf("%d", &C);
  while (C-- > 0) {
    solve();
  }

  return 0;
}
