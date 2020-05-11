#include <stdio.h>
#include <assert.h>

char grid[32][32][32];

int L, R, C;

int valid(int l, int r, int c)
{
  return grid[l][r][c] != '#';
}

int dist(int sl, int sr, int sc)
{
  int ql[30*30*30+1], qr[30*30*30+1], qc[30*30*30+1];
  int d[32][32][32];
  int qhead, qtail;
  int l, r, c;
  int old_d;

  for (l = 1; l <= L; l++) {
    for (r = 1; r <= R; r++) {
      for (c = 1; c <= C; c++) {
	d[l][r][c] = -1;
      }
    }
  }

  qhead = qtail = 0;
  ql[qtail] = sl; qr[qtail] = sr;  qc[qtail++] = sc;
  d[sl][sr][sc] = 0;

  while (qhead != qtail) {
    sl = ql[qhead]; sr = qr[qhead]; sc = qc[qhead++];
    old_d = d[sl][sr][sc];
    if (grid[sl][sr][sc] == 'E') {
      return old_d;
    }

    l = sl+1;  r = sr;  c = sc;
    if (valid(l, r, c) && d[l][r][c] < 0) {
      d[l][r][c] = old_d+1;
      ql[qtail] = l; qr[qtail] = r; qc[qtail++] = c;
    }

    l = sl-1;  r = sr;  c = sc;
    if (valid(l, r, c) && d[l][r][c] < 0) {
      d[l][r][c] = old_d+1;
      ql[qtail] = l; qr[qtail] = r; qc[qtail++] = c;
    }

    l = sl;  r = sr+1;  c = sc;
    if (valid(l, r, c) && d[l][r][c] < 0) {
      d[l][r][c] = old_d+1;
      ql[qtail] = l; qr[qtail] = r; qc[qtail++] = c;
    }

    l = sl;  r = sr-1;  c = sc;
    if (valid(l, r, c) && d[l][r][c] < 0) {
      d[l][r][c] = old_d+1;
      ql[qtail] = l; qr[qtail] = r; qc[qtail++] = c;
    }

    l = sl;  r = sr;  c = sc+1;
    if (valid(l, r, c) && d[l][r][c] < 0) {
      d[l][r][c] = old_d+1;
      ql[qtail] = l; qr[qtail] = r; qc[qtail++] = c;
    }

    l = sl;  r = sr;  c = sc-1;
    if (valid(l, r, c) && d[l][r][c] < 0) {
      d[l][r][c] = old_d+1;
      ql[qtail] = l; qr[qtail] = r; qc[qtail++] = c;
    }
  }
  return -1;
}

int main(void)
{
  int l, r, c;
  int sl, sr, sc;
  int d;
  
  for (l = 0; l < 32; l++) {
    for (r = 0; r < 32; r++) {
      for (c = 0; c < 32; c++) {
	grid[l][r][c] = '#';
      }
    }
  }

  while (scanf("%d %d %d\n", &L, &R, &C) == 3 && (L || R || C)) {
    for (l = 1; l <= L; l++) {
      for (r = 1; r <= R; r++) {
	for (c = 1; c <= C; c++) {
	  /* safe to use char for getchar() because it is not EOF) */
	  if ((grid[l][r][c] = getchar()) == 'S') {
	    sl = l; sr = r; sc = c;
	  }
	}
	assert(getchar() == '\n');
      }
      assert(getchar() == '\n');
    }

    if ((d = dist(sl, sr, sc)) > 0) {
      printf("Escaped in %d minute(s).\n", d);
    } else {
      printf("Trapped!\n");
    }
  }
  return 0;
}
