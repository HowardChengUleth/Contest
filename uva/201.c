#include <stdio.h>
#include <assert.h>

char H[9][9], V[9][9];
int n;

int read_case(void)
{
  int m;
  char c;
  int i, j;

  if (scanf("%d", &n) != 1) {
    return 0;
  }
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      H[i][j] = V[i][j] = 0;
    }
  }

  scanf("%d ", &m);
  while (m-- > 0) {
    scanf("%c %d %d ", &c, &i, &j);
    i--; j--;
    if (c == 'H') {
      H[i][j] = 1;
    } else if (c == 'V') {
      V[j][i] = 1;
    } else {
      assert(0);
    }
  }

  return 1;
}

int check_square(int r, int c, int size)
{
  int i;

  if (r+size >= n || c+size >= n) return 0;
  for (i = 0; i < size; i++) {
    if (!H[r][c+i] || !H[r+size][c+i] || !V[r+i][c] || !V[r+i][c+size]) {
      return 0;
    }
  }
  return 1;
}

void solve_case(void)
{
  int size;
  int r, c;
  int count, found;

  found = 0;
  for (size = 1; size <= n-1; size++) {
    count = 0;
    for (r = 0; r < n; r++) {
      for (c = 0; c < n; c++) {
	if (check_square(r, c, size)) {
	  count++;
	}
      }
    }
    if (count) {
      printf("%d square (s) of size %d\n", count, size);
      found = 1;
    }
  }
  if (!found) {
    printf("No completed squares can be found.\n");
  }
}

int main(void)
{
  int prob = 1;

  while (read_case()) {
    if (prob > 1) {
      printf("\n**********************************\n\n");
    }
    printf("Problem #%d\n\n", prob++);
    solve_case();
  }
  
  return 0;
}
