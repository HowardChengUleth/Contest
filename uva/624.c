/* @JUDGE_ID: 1102NT 624 C "" */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int track[20];
int num_tracks;
int N;

int read_case(void)
{
  int i;
  if (scanf("%d %d", &N, &num_tracks) != 2) {
    return 0;
  }
  for (i = 0; i < num_tracks; i++) {
    scanf("%d", track+i);
  }
  return 1;
}

void solve_case(void)
{
  char *sum;
  int *pred;
  int i, j, s;

  sum = calloc(N+1, sizeof(*sum));
  pred = calloc(N+1, sizeof(*pred));
  assert(sum && pred);

  sum[0] = 1;
  pred[0] = -1;
  
  for (i = num_tracks-1; i >= 0; i--) {
    for (j = 0; j <= N - track[i]; j++) {
      if (sum[j] && pred[j] != i && !sum[j+track[i]]) {
	sum[j+track[i]] = 1;
	pred[j+track[i]] = i;
      }
    }
  }
  
  for (s = N; s >= 0 && !sum[s]; s--) 
    ;
  
  for (i = s; i > 0; i -= track[pred[i]]) {
    printf("%d ", track[pred[i]]);
  }

  printf("sum:%d\n", s);

  free(sum);
  free(pred);
}

int main(void)
{
  while (read_case()) {
    solve_case();
  }
  return 0;
}
