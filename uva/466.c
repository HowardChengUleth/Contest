#include <stdio.h>
#include <string.h>

typedef char Pattern[10][11];

void read_pattern(int N, Pattern orig, Pattern final)
{
  int i;
  char line[1024];

  for (i = 0; i < N; i++) {
    fgets(line, 1024, stdin);
    strncpy(orig[i], line, N);
    strncpy(final[i], line+N+1, N);
    orig[i][N] = final[i][N] = 0;
  }
}

int equal(int N, Pattern orig, Pattern final)
{
  int i;
  for (i = 0; i < N; i++) {
    if (strcmp(orig[i], final[i])) {
      return 0;
    }
  }
  return 1;
}

void rotate90(int N, Pattern orig, Pattern final)
{
  int i, j;

  for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++) {
      final[j][N-1-i] = orig[i][j];
    }
    final[i][N] = 0;
  }
  
}

void reflect(int N, Pattern orig, Pattern final)
{
  int i;

  for (i = 0; i < N; i++) {
    strcpy(final[N-1-i], orig[i]);
  }
}

void solve(int N, Pattern orig, Pattern final)
{
  Pattern temp, temp2;

  /* preserved */
  if (equal(N, orig, final)) {
    printf("preserved.\n");
    return;
  }

  /* rotate 90 */
  rotate90(N, orig, temp);
  if (equal(N, temp, final)) {
    printf("rotated 90 degrees.\n");
    return;
  }

  /* rotate 180 */
  rotate90(N, temp, temp2);
  if (equal(N, temp2, final)) {
    printf("rotated 180 degrees.\n");
    return;
  }

  /* rotate 270 */
  rotate90(N, temp2, temp);
  if (equal(N, temp, final)) {
    printf("rotated 270 degrees.\n");
    return;
  }

  /* reflect vertical */
  reflect(N, orig, temp);
  if (equal(N, temp, final)) {
    printf("reflected vertically.\n");
    return;
  }

  /* rotate 90 */
  rotate90(N, temp, temp2);
  if (equal(N, temp2, final)) {
    printf("reflected vertically and rotated 90 degrees.\n");
    return;
  }

  /* rotate 180 */
  rotate90(N, temp2, temp);
  if (equal(N, temp, final)) {
    printf("reflected vertically and rotated 180 degrees.\n");
    return;
  }

  rotate90(N, temp, temp2);
  if (equal(N, temp2, final)) {
    printf("reflected vertically and rotated 270 degrees.\n");
    return;
  }

  printf("improperly transformed.\n");
}

int main(void)
{
  Pattern orig, final;
  int N;
  int ID = 1;

  while (scanf("%d\n", &N) == 1) {
    read_pattern(N, orig, final);
    printf("Pattern %d was ", ID++);
    solve(N, orig, final);
  }

  return 0;
}
