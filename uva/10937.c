#include <stdio.h>

#define MAX_DIM 50
#define MAX_T 10

char map[MAX_DIM+2][MAX_DIM+2];
int spotr[MAX_T+1], spotc[MAX_T+1];  /* 0 = landing spot */
int h, w, t;
int nbr_r[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
int nbr_c[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

int D[MAX_T+1][MAX_T+1];
int bad;

int read_map(void)
{
  int i, j, k;
  char line[MAX_DIM+2];

  scanf("%d %d\n", &h, &w);
  if (!h && !w) {
    return 0;
  }
  for (i = 0; i < h+2; i++) {
    for (j = 0; j < w+2; j++) {
      map[i][j] = '#';
    }
  }
  t = 0;
  for (i = 1; i <= h; i++) {
    fgets(line, MAX_DIM+2, stdin);
    for (j = 1; j <= w; j++) {
      map[i][j] = line[j-1];
      if (map[i][j] == '@') {
	spotr[0] = i;    spotc[0] = j;
	map[i][j] = 0;
      } else if (map[i][j] == '!') {
	spotr[++t] = i;  spotc[t] = j;
	map[i][j] = t;
	/*
	printf("%d: (%d, %d)\n", t, i, j);
	*/
      }
    }
  }
  /*
  printf("====================\n");
  */

  bad = 0;
  for (i = 1; i <= h; i++) {
    for (j = 1; j <= w; j++) {
      if (map[i][j] == '*') {
	for (k = 0; k < 8; k++) {
	  if (map[i+nbr_r[k]][j+nbr_c[k]] <= t) {
	    /* can't get there because of natives */
	    bad = 1;
	  }
	}

	for (k = 0; k < 8; k++) {
	  if (map[i+nbr_r[k]][j+nbr_c[k]] != '*') {
	    map[i+nbr_r[k]][j+nbr_c[k]] = '#';
	  }
	}
      }
    }
  }

  return 1;
}

void calc_D(void)
{
  int i, j, k;
  char tmap[MAX_DIM+2][MAX_DIM+2];
  int dist[MAX_DIM+2][MAX_DIM+2];
  int qr[(MAX_DIM+2)*(MAX_DIM+2)], qc[(MAX_DIM+2)*(MAX_DIM+2)];
  int qh, qt;
  int r, c;

  for (i = 0; i < t+1; i++) {
    for (j = 0; j < t+1; j++) {
      D[i][j] = -1;
    }
  }

  for (k = 0; k < t+1; k++) {
    for (i = 0; i <= h+1; i++) {
      for (j = 0; j <= w+1; j++) {
	tmap[i][j] = map[i][j];
	dist[i][j] = -1;
      }
    }
    qh = qt = 0;
    qr[qt] = spotr[k];
    qc[qt++] = spotc[k];
    dist[spotr[k]][spotc[k]] = 0;
    while (qh < qt) {
      r = qr[qh];
      c = qc[qh++];
      if (map[r][c] <= t) {
	D[k][map[r][c]] = dist[r][c];
      }
      tmap[r][c] = '#';
      if (dist[r-1][c] < 0 && (tmap[r-1][c] == '.' || tmap[r-1][c] <= t)) {
	dist[r-1][c] = dist[r][c] + 1;
	qr[qt] = r-1; qc[qt++] = c;
      }
      if (dist[r+1][c] < 0 && (tmap[r+1][c] == '.' || tmap[r+1][c] <= t)) {
	dist[r+1][c] = dist[r][c] + 1;
	qr[qt] = r+1; qc[qt++] = c;
      }
      if (dist[r][c-1] < 0 && (tmap[r][c-1] == '.' || tmap[r][c-1] <= t)) {
	dist[r][c-1] = dist[r][c] + 1;
	qr[qt] = r; qc[qt++] = c-1;
      }
      if (dist[r][c+1] < 0 && (tmap[r][c+1] == '.' || tmap[r][c+1] <= t)) {
	dist[r][c+1] = dist[r][c] + 1;
	qr[qt] = r; qc[qt++] = c+1;
      }
    }
    /*
    printf("k = %d:\n", k);
    for (i = 1; i <= h; i++) {
      for (j = 1; j <= w; j++) {
	printf("%3d", dist[i][j]);
      }
      printf("\n");
    }
    */
  }

  /*
  for (i = 0; i <= t; i++) {
    for (j = 0; j <= t; j++) {
      printf("%4d", D[i][j]);
    }
    printf("\n");
  }

  printf("========================\n");
  */
}

int try(int *perm, int start)
{
  int sum, i, temp, val;

  if (start == t) {
    if (D[perm[t-1]][0] < 0) {
      return -1;
    }
    sum = D[0][perm[0]] + D[perm[t-1]][0];
    for (i = 0; i < t-1; i++) {
      sum += D[perm[i]][perm[i+1]];
    }
    return sum;
  } else {
    sum = -1;
    for (i = start; i < t; i++) {
      temp = perm[start];
      perm[start] = perm[i];
      perm[i] = temp;
      if ((!i && D[0][perm[i]] >= 0) ||
	  (i && D[perm[i-1]][perm[i]] >= 0)) {
	val = try(perm, start+1);
	if (val != -1 && (sum == -1 || val < sum)) {
	  sum = val;
	}
      }
      temp = perm[start];
      perm[start] = perm[i];
      perm[i] = temp;
    }
    return sum;
  }
}

int solve(void)
{
  int perm[MAX_T];
  int i;

  if (bad) {
    return -1;
  }
  if (t == 0) {
    return 0;
  }
  for (i = 0; i < t; i++) {
    perm[i] = i+1;
  }
  return try(perm, 0);
}

int main(void)
{
  while (read_map()) {
    calc_D();
    printf("%d\n", solve());
  }
  return 0;
}
