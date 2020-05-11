/* @JUDGE_ID: 1102NT 10821 C "" */

#include <stdio.h>
#include <math.h>
#include <assert.h>

int min_level(int N)
{
  return ceil(log(N+1)/log(2));
}

void solve_case(int start, int N, int H)
{
  int root;

  if (!N) {
    return;
  } else if (N == 1) {
    printf(" %d", start);
    return;
  }

  for (root = start; root < start+N; root++) {
    if (min_level(root-start) <= H-1 && min_level(start+N-root-1) <= H-1) {
      printf(" %d", root);
      
      /* note that doing left branch first means "smallest numbers 
       * come first" */
      solve_case(start, root-start, H-1);
      solve_case(root+1, start+N-root-1, H-1);
      return;
    }
  }
  assert(0);
}

int main(void)
{
  int N, H;
  int c = 0;

  while (scanf("%d %d", &N, &H) == 2 && (N || H)) {
    printf("Case %d:", ++c);
    if (min_level(N) > H) {
      printf(" Impossible.\n");
    } else {
      solve_case(1, N, H);
      printf("\n");
    }
  }
  
  return 0;
}
