/* @JUDGE_ID: 1102NT 10549 C "" */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct {
  int h, d, w;
} Doll;

Doll doll[201];
int n;

int cmp(const void *a, const void *b)
{
  Doll *x = (Doll *)a, *y = (Doll *)b;

  if (x->h == y->h) {
    return x->d - y->d;
  } else {
    return x->h - y->h;
  }
}

int fit(int i, int j)
{
  return (doll[i].h <= doll[j].h - 2*doll[j].w) &&
    (doll[i].d <= doll[j].d - 2*doll[j].w);
}

/* table[k][i][j] means there is a way to have k dolls in pile 1,
   with doll i at the top of pile 1 and doll j at the top of pile 2
*/

unsigned char table[201][201][201];

void compute(int k, int i, int j)
{
  int a;
  
  if (k < 0 || table[k][i][j]) return;
  if (i < j) {
    compute(j-k, j, i);
    table[k][i][j] = table[j-k][j][i];
    return;
  }
  
  for (a = 0; a < i && k > 0; a++) {
    if (a != i-1 && j != i-1) continue;
    if (!fit(a, i)) continue;
    compute(k-1, a, j);
    if (table[k-1][a][j] >= 2) {
      table[k][i][j] = a+2;
      return;
    }
  }

  table[k][i][j] = 1;
}

int set1[200], set2[200];

int main(void)
{
  int i, j, k, i1, i2;
  int a, b;
  int first = 1;
  
  while (scanf("%d", &n) == 1 && n > 0) {
    if (first) {
      first = 0;
    } else {
      printf("\n");
    }
    doll[0].h = doll[0].w = doll[0].d = 0; /* dummy doll */
    for (i = 1; i <= 2*n; i++) {
      scanf("%d %d %d", &(doll[i].h), &(doll[i].d), &(doll[i].w));
    }
    qsort(doll, 2*n+1, sizeof(Doll), cmp);

    memset(table,0,sizeof(table));

    table[0][0][0] = 2;
    for (i = 0; i < 2*n; i++) {
      compute(n, 2*n, i);
      if (table[n][2*n][i] >= 2) {
	break;
      }
    }

    a = 2*n;
    b = i;
    k = n;
    i1 = i2 = 0;
    while (i1 < n || i2 < n) {
      if (a > b) {
	set1[i1++] = a;
	assert(table[k][a][b] >= 2 || table[a-k][b][a] >= 2);
	if (!table[k][a][b]) {
	  table[k][a][b] = table[a-k][b][a];
	}
	a = table[k--][a][b]-2;
      } else {
	set2[i2++] = b;
	assert(table[k][a][b] >= 2 || table[b-k][b][a] >= 2);
	if (!table[k][a][b]) {
	  table[k][a][b] = table[b-k][b][a];
	}
	b = table[k][a][b]-2;
      }
    }
    for (i = 0; i < n; i++) {
      printf("%d %d %d\n", doll[set1[i]].h, doll[set1[i]].d, doll[set1[i]].w);
    }
    printf("-\n");
    for (i = 0; i < n; i++) {
      printf("%d %d %d\n", doll[set2[i]].h, doll[set2[i]].d, doll[set2[i]].w);
    }
    
  }

  return 0;
}
