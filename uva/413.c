#include <stdio.h>

int read_seq(int *seq)
{
  int i, x;

  i = 0;
  while (scanf("%d", &x) == 1 && x) {
    seq[i++] = x;
  }
  return i;
}

void solve(int *seq, int n, double *up, double *down)
{
  int u_count, d_count;
  int curr_up = 0;
  int i;

  u_count = d_count = 0;
  *up = *down = 0.0;

  for (i = 0; i < n-1 && seq[i] == seq[i+1]; i++)
    ;
  if (i >= n-1) return;
  curr_up = (seq[i] < seq[i+1]);
  if (curr_up) {
    u_count++;
  } else {
    d_count++;
  }
  
  for (i = 0; i+1 < n; i++) {
    if (curr_up) {
      if (seq[i] <= seq[i+1]) {
	*up += 1.0;
      } else {
	*down += 1.0;
	d_count++;
	curr_up = 0;
      }
    } else {
      if (seq[i] >= seq[i+1]) {
	*down += 1.0;
      } else {
	*up += 1.0;
	u_count++;
	curr_up = 1;
      }
    }
  }

  if (u_count) {
    *up /= u_count;
  } else {
    *up = 0.0;
  }
  if (d_count) {
    *down /= d_count;
  } else {
    *down = 0.0;
  }
}

int main(void)
{
  int seq[30];
  int n;
  double up, down;

  while (n = read_seq(seq)) {
    solve(seq, n, &up, &down);
    printf("Nr values = %d:  %.6f %.6f\n", n, up, down);
  }

  return 0;
}
