#include <stdio.h>

#define INDEX(n) ((n)+32000)
#define VALUE(n) ((n)-32000)

int inrange(int n)
{
  return (-32000 <= n && n <= 32000);
}

void print(int pred[101][64001], char op[101][64001], int p, int *num, int t)
{
  if (p > 1) {
    print(pred, op, p-1, num, pred[p][t]);
    putchar(op[p][t]);
  }
  
  printf("%d", num[p-1]);
}

int pred[101][64001];
char op[101][64001];

void solve(int p, int *num, int t)
{
  int i, j;

  for (i = 0; i <= p; i++) {
    for (j = -32000; j <= 32000; j++) {
      pred[i][INDEX(j)] = -1;
    }
  }

  pred[1][INDEX(num[0])] = INDEX(0);
  for (i = 1; i <= p-1; i++) {
    for (j = -32000; j <= 32000; j++) {
      if (pred[i][INDEX(j)] == -1) continue;
      if (inrange(j + num[i])) {
	pred[i+1][INDEX(j+num[i])] = INDEX(j);
	op[i+1][INDEX(j+num[i])] = '+';
      }
      if (inrange(j - num[i])) {
	pred[i+1][INDEX(j-num[i])] = INDEX(j);
	op[i+1][INDEX(j-num[i])] = '-';
      }
      if (inrange(j * num[i])) {
	pred[i+1][INDEX(j*num[i])] = INDEX(j);
	op[i+1][INDEX(j*num[i])] = '*';
      }
      if (j % num[i] == 0 && inrange(j / num[i])) {
	pred[i+1][INDEX(j/num[i])] = INDEX(j);
	op[i+1][INDEX(j/num[i])] = '/';
      }
    }
  }

  if (pred[p][INDEX(t)] == -1) {
    printf("NO EXPRESSION\n");
  } else {
    print(pred, op, p, num, INDEX(t));
    printf("=%d\n", t);
  }
}

int main(void)
{
  int T;
  int p, t, i;;
  int num[100];

  scanf("%d", &T);
  while (T-- > 0) {
    scanf("%d", &p);
    for (i = 0; i < p; i++) {
      scanf("%d", num+i);
    }
    scanf("%d", &t);
    solve(p, num, t);
  }
  
  return 0;
}
