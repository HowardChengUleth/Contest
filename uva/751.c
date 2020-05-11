/* @JUDGE_ID: 1102NT 751 C "" */

/* Copyright Howard Cheng (ACM ICPC ECNA 1999) */

#include <stdio.h>
#include <assert.h>

int filled[9];         /* how many edges of triangle i is filled */

typedef struct {
  int to[3];
  int triangle[3][2];
} Triangle;

Triangle triangle[10] = {
  { {-1,-1,-1}, {{-1,-1}, {-1,-1}, {-1,-1}} },
  { {2,3,-1}, {{0,-1}, {0,-1}, {-1,-1}} },
  { {3,4,5}, {{0,2}, {1,-1}, {1,2}} },
  { {5,6,-1}, {{2,3}, {3,-1}, {-1,-1}} },
  { {5,7,8}, {{1,5}, {4,-1}, {4,5}} },
  { {6,8,9}, {{3,7}, {5,6}, {6,7}} },
  { {9,10,-1}, {{7,8}, {8,-1}, {-1,-1}} },
  { {8,-1,-1}, {{4,-1}, {-1,-1}, {-1,-1}} },
  { {9,-1,-1}, {{6,-1}, {-1,-1}, {-1,-1}} },
  { {10,-1,-1}, {{8,-1}, {-1,-1}, {-1,-1}} }
};

char line[11][11];
int edge[18][2];

void init_edge(void)
{
  int i, j, k, t;

  k = 0;
  for (i = 1; i < 10; i++) {
    for (j = 0; j < 3; j++) {
      if ((t = triangle[i].to[j]) != -1) {
	edge[k][0] = i;
	edge[k][1] = t;
	assert(i < t);
	k++;
      }
    }
  }
  assert(k == 18);
}

int fill_line(int n1, int n2, int fill)
{
  int d, i, t, r;

  r = 0;
  if (n1 > n2) {
    return fill_line(n2, n1, fill);
  }

  d = (fill) ? 1 : -1;

  if (fill) {
    assert(!line[n1][n2]);
    line[n1][n2] = 1;
  } else {
    assert(line[n1][n2]);
    line[n1][n2] = 0;
  }

  for (i = 0; i < 3 && triangle[n1].to[i] != n2; i++)
    ;
  assert(i < 3);

  if ((t = triangle[n1].triangle[i][0]) != -1) {
    filled[t] += d;
    assert(0 <= filled[t] && filled[t] <= 3);
    if ((filled[t] == 3 && fill) || (filled[t] == 2 && !fill)) {
      r++;
    }
  }
  if ((t = triangle[n1].triangle[i][1]) != -1) {
    filled[t] += d;
    assert(0 <= filled[t] && filled[t] <= 3);
    if ((filled[t] == 3 && fill) || (filled[t] == 2 && !fill)) {
      r++;
    }
  }

  return r;
}

int result(int turn, int move, int input_left, int Ascore, int Bscore)
{
  int res;        /* either 1 or 2 for A or B's victory */
  int r, n1, n2, i, next, t;

  /* done */
  if (Ascore >= 5 && input_left <= 0) {
    return 1;
  } else if (Bscore >= 5 && input_left <= 0) {
    return 2;
  } else if (move == 18) {
    assert(Ascore + Bscore == 9);
    return (Ascore >= 5) ? 1 : 2;
  }
  
  /* just read the input */
  if (input_left > 0) {
    t = scanf("%d %d", &n1, &n2);
    assert(t == 2 && n1 < n2);
    r = fill_line(n1, n2, 1);
    next = (r) ? turn : 3 - turn;
    return result(next, move+1, input_left-1, 
		  (turn == 1) ? Ascore + r : Ascore,
		  (turn == 2) ? Bscore + r : Bscore);
  }

  /* need to try */
  for (i = 0; i < 18; i++) {
    n1 = edge[i][0];
    n2 = edge[i][1];
    if (!line[n1][n2]) {
      r = fill_line(n1, n2, 1);
      next = (r) ? turn : 3 - turn;
      res = result(next, move+1, input_left, 
		   (turn == 1) ? Ascore + r : Ascore,
		   (turn == 2) ? Bscore + r : Bscore);
      fill_line(n1, n2, 0);

      if (res == turn) {
	/* current player wins by playing here, so just prune */
	/*	printf("move = %d, %c takes edge (%d, %d)\n", move, 
	       (turn == 1) ? 'A' : 'B', n1,n2);
	*/
	return turn;
      }
    }
  }
  return 3 - turn;
}

void solve_case(void)
{
  int games, m, i, j, k, t;

  init_edge();
  t = scanf("%d", &games);
  assert(t == 1 && games > 0);
  for (i = 1; i <= games; i++) {
    for (k = 0; k < 9; k++) {
      filled[k] = 0;
    }

    for (j = 0; j < 11; j++) {
      for (k = 0; k < 11; k++) {
	line[j][k] = 0;
      }
    }

    t = scanf("%d", &m);
    assert(t == 1 && 6 <= m && m <= 18);
    if (result(1, 0, m, 0, 0) == 1) {
      printf("Game %d: A wins.\n", i);
    } else {
      printf("Game %d: B wins.\n", i);
    }
  }
}

int main(void)
{
  solve_case();
  return 0;
}
