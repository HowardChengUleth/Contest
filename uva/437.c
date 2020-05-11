#include <stdio.h>

/* there are 30 types, but 3 rotations */
int blocks[90][3];
int num_blocks;

int read_case(void)
{
  int n, i, j;
  
  scanf("%d", &n);
  if (!n) {
    return 0;
  }

  num_blocks = 0;
  while (n-- > 0) {
    scanf("%d %d %d", blocks[num_blocks], blocks[num_blocks]+1, 
	  blocks[num_blocks]+2);
    num_blocks++;
    for (i = 0; i < 2; i++) {
      for (j = 0; j < 3; j++) {
	blocks[num_blocks][j] = blocks[num_blocks-1][(j+1)%3];
      }
      num_blocks++;
    }
  }

  return 1;
}

int fit(int i, int j)
{
  return (blocks[i][0] < blocks[j][0] && blocks[i][1] < blocks[j][1]) ||
    (blocks[i][1] < blocks[j][0] && blocks[i][0] < blocks[j][1]);
}

void compute_height(int *max_height, int i)
{
  int j, t;

  if (max_height[i] >= 0) {
    return;
  }

  max_height[i] = blocks[i][2];
  for (j = 0; j < num_blocks; j++) {
    if (!fit(i, j)) continue;
    compute_height(max_height, j);
    t = blocks[i][2] + max_height[j];
    if (t > max_height[i]) {
      max_height[i] = t;
    }
  }
}

int solve_case(void)
{
  int max_height[90];
  int best;
  int i;

  for (i = 0; i < num_blocks; i++) {
    max_height[i] = -1;
  }

  for (i = 0; i < num_blocks; i++) {
    compute_height(max_height, i);
  }

  best = max_height[0];
  for (i = 1; i < num_blocks; i++) {
    if (max_height[i] > best) {
      best = max_height[i];
    }
  }

  return best;
}

int main(void)
{
  int case_num = 1;
  while (read_case()) {
    printf("Case %d: maximum height = %d\n", case_num++, solve_case());
  }

  return 0;
}
