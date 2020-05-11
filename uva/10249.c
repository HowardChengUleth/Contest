/* @JUDGE_ID: 1102NT 10249 C "" */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct {
    int index;
    int cap;
} Table;

int cmp(const void *x, const void *y)
{
  return ((Table *)y)->cap - ((Table *)x)->cap;
}

int main(void)
{
  int M, N;
  int m[70];
  Table n[50];
  int seat[70][100];
  int i, j, bad;

  while (scanf("%d %d", &M, &N) == 2 && (M || N)) {
    for (i = 0; i < M; i++) {
      scanf("%d", m+i);
    }
    for (i = 0; i < N; i++) {
      scanf("%d", &(n[i].cap));
      n[i].index = i+1;
    }
    bad = 0;
    for (i = 0; i < M && !bad; i++) {
      qsort(n, N, sizeof(Table), cmp);
      if (m[i] > N || n[m[i]-1].cap <= 0) {
	bad = 1;
	break;
      }
      for (j = 0; j < m[i]; j++) {
	seat[i][j] = n[j].index;
	n[j].cap--;
      }
    }

    if (bad) {
      printf("0\n");
    } else {
      printf("1\n");
      for (i = 0; i < M; i++) {
	for (j = 0; j < m[i]; j++) {
	  if (j) {
	    printf(" ");
	  }
	  printf("%d", seat[i][j]);
	}
	printf("\n");
      }
    }
  }
  
  return 0;
}


