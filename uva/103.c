/* @JUDGE_ID: 1102NT 103 C "Dynamic Programming" */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_DIM 10
#define MAX_NUM 30

int dim_cmp(const void *a, const void *b);
int box_cmp(const void *a, const void *b);
int fit(int box1, int box2);
void process(void);

typedef struct {
  int label;
  int dim[MAX_DIM];
} Box;

Box box[MAX_NUM];
int n, k;

int main(void)
{
  int i, j;

  while (scanf("%d %d", &k, &n) == 2) {
    for (i = 0; i < k; i++) {
      box[i].label = i+1;
      for (j = 0; j < n; j++) {
	scanf("%d", &(box[i].dim[j]));
      }
      qsort(box[i].dim, n, sizeof(int), dim_cmp);
    }
    qsort(box, k, sizeof(Box), box_cmp);
    process();
  }

  return 0;
}

int dim_cmp(const void *a, const void *b)
{
  int *pa = (int *)a;
  int *pb = (int *)b;
  return (*pb) - (*pa);
}

int box_cmp(const void *a, const void *b)
{
  int i;
  Box box1 = *((Box *)a);
  Box box2 = *((Box *)b);
  
  for (i = 0; i < n; i++) {
    if (box1.dim[i] != box2.dim[i]) {
      return box1.dim[i] - box2.dim[i];
    }
  }
  return 0;
}

int fit(int box1, int box2)
{
  int i;

  for (i = 0; i < n; i++) {
    if (box[box1].dim[i] >= box[box2].dim[i]) {
      return 0;
    }
  }
  return 1;
}

void process(void)
{
  int best[MAX_NUM];
  int prev[MAX_NUM];
  int max_index, max_len;
  int sequence[MAX_NUM];

  int i, j;

  for (i = 0; i < k; i++) {
    prev[i] = -1;
    best[i] = 0;
  }

  for (i = 0; i < k; i++) {
    for (j = 0; j < i; j++) {
      if (fit(j, i) && best[j] > best[i]) {
	best[i] = best[j];
	prev[i] = j;
      }
    }
    best[i]++;
  }
  
  max_len = best[0];
  max_index = 0;
  for (i = 1; i < k; i++) {
    if (best[i] > max_len) {
      max_len = best[i];
      max_index = i;
    }
  }

  /* print out the sequence */
  j = 0;
  i = max_index;
  while (i != -1) {
    sequence[j++] = box[i].label;
    i = prev[i];
  }
  printf("%d\n", max_len);
  for (j--; j >= 0; j--) {
    printf("%d", sequence[j]);
/*    if (j > 0) { */
      printf(" ");
/*    } */
  }
  printf("\n");

}
