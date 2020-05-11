/* @JUDGE_ID: 1102NT 607 C "" */


/*
 * Solution to "Scheduling Lectures"
 *
 * Author: Howard Cheng
 * Date: Nov 8, 1998
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_TOPICS 1000
#define MAX_LECLEN 500

typedef struct {
  int DI;                    /* Total DI up to previous lecture */
  short int lec_no;          /* current lecture number          */
} Record;

/* only need up to MAX_LECLEN-1 since t_i >= 1 */
/* we could have limited ourselves to only a few rows of this matrix since */
/* we don't care about the actual lecture schedule                         */
Record rec[MAX_TOPICS][MAX_LECLEN];  
int n, L, C;
int topic[MAX_TOPICS];

int read_case(void)
{
  int i, t;
  
  t = scanf("%d", &n);
  assert(t == 1);
  if (n == 0) {
    return 0;
  }
  assert(1 <= n && n <= MAX_TOPICS);
  scanf("%d %d", &L, &C);
  assert(1 <= L && L <= MAX_LECLEN);
  assert(0 < C);
  for (i = 0; i < n; i++) {
    scanf("%d", topic+i);
    assert(1 <= topic[i] && topic[i] <= L);
  }
  return 1;
}

void do_case(void)
{
  int i, j, i2, j2, best_j, best_DI, best_lec_no;
  int newDI, lec_no;
  int DI[MAX_LECLEN];
  
  /* initialize matrix */
  for (i = 0; i < n; i++) {
    for (j = 0; j < L; j++) {       /* only needs up to L-1 */
      rec[i][j].lec_no = -1;
    }
  }
  
  /* precompute dissatisfaction index */
  DI[0] = 0;
  for (j = 1; j < L; j++) {
    if (j <= 10) {
      DI[j] = -C;
    } else {
      DI[j] = (j-10)*(j-10);
    }
  }

  /* seed first row */
  j = L - topic[0];
  rec[0][j].DI = 0;
  rec[0][j].lec_no = 1;

  /* do all the rows */
  for (i = 0; i < n-1; i++) {
    i2 = i+1;
    for (j = 0; j < L; j++) {
      if (rec[i][j].lec_no != -1) {
	/* fit in current lecture */
	if (topic[i2] <= j) {
	  j2 = j - topic[i2];
	  assert(rec[i2][j2].lec_no == -1);
	  rec[i2][j2].DI = rec[i][j].DI;
	  rec[i2][j2].lec_no = rec[i][j].lec_no;
	}

	/* fit in a new lecture */
	j2 = L - topic[i2];
	newDI = rec[i][j].DI + DI[j];
	lec_no = rec[i][j].lec_no + 1;
	if ((rec[i2][j2].lec_no == -1) ||
	    (lec_no < rec[i2][j2].lec_no) ||
	    (lec_no == rec[i2][j2].lec_no && newDI < rec[i2][j2].DI)) {
	  rec[i2][j2].DI = newDI;
	  rec[i2][j2].lec_no = lec_no;
	}
      }
    }
  }

  /* now find the last lecture with the smallest lecture number, and */
  /* and also the smallest DI if there is a tie                      */
  best_j = -1;
  for (j = 0; j < L; j++) {
    if (rec[n-1][j].lec_no != -1) {
      newDI = rec[n-1][j].DI + DI[j];
      if (best_j == -1 ||
	  rec[n-1][j].lec_no < best_lec_no || 
	  (rec[n-1][j].lec_no == best_lec_no && newDI < best_DI)) {
	best_j = j;
	best_DI = newDI;
	best_lec_no = rec[n-1][j].lec_no;
      }
    }
  }

  /* print output */
  printf("Minimum number of lectures: %d\n", best_lec_no);
  printf("Total dissatisfaction index: %d\n", best_DI);
}

void main(void)
{
  int case_no = 0;

  while (read_case()) {
    if (case_no > 0) {
      printf("\n");
    }
    printf("Case %d:\n", ++case_no);
    do_case();
  }
}
