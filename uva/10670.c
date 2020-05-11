/* @JUDGE_ID: 1102NT 10670 C "" */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME (16+1)
#define MAX_AGENCY 100

typedef struct {
  char name[MAX_NAME];
  int A, B;
  int cost;
} Agency;

Agency agency[MAX_AGENCY];
int N, M, L;

int cmp(const void *a, const void *b)
{
  Agency *x = (Agency *)a, *y = (Agency *)b;

  if (x->cost != y->cost) {
    return x->cost - y->cost;
  } else {
    return strcmp(x->name, y->name);
  }
}

void read_case(void)
{
  char buffer[1024], *p;
  int i;

  scanf("%d %d %d\n", &N, &M, &L);
  for (i = 0; i < L; i++) {
    fgets(buffer, 1024, stdin);
    p = strtok(buffer, ":");
    strcpy(agency[i].name, p);
    p = strtok(0, ",");
    agency[i].A = atoi(p);
    p = strtok(0, "\n");
    agency[i].B = atoi(p);
  }
}

void compute_cost(int k)
{
  int NN = N, delta;

  agency[k].cost = 0;
  while (NN != M) {
    delta = NN - NN/2;
    if (NN/2 < M) {
      agency[k].cost += (NN-M)*agency[k].A;
      NN -= (NN - M);
    } else if (delta*agency[k].A <= agency[k].B) {
      agency[k].cost += delta*agency[k].A;
      NN -= delta;
    } else {
      agency[k].cost += agency[k].B;
      NN /= 2;
    }
  }
}

int main(void)
{
  int cases, i, j;

  scanf("%d", &cases);
  for (i = 1; i <= cases; i++) {
    printf("Case %d\n", i);
    read_case();
    for (j = 0; j < L; j++) {
      compute_cost(j);
    }
    qsort(agency, L, sizeof(*agency), cmp);
    for (j = 0; j < L; j++) {
      printf("%s %d\n", agency[j].name, agency[j].cost);
    }
  }
  return 0;
}
