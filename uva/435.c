/* @JUDGE_ID: 1102NT 435 C "" */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_P 20
#define MAX_SUBSET (1 << MAX_P)

#define GETBIT(x) (used[(x)>>3] & (1 << ((x) & 7)))
#define SETBIT(x) used[(x)>>3] |= (1 << ((x) & 7))

int P;
int pindex[MAX_P];
int votes[MAX_P];
short number[MAX_SUBSET];
int sum;
int queue[MAX_SUBSET];

void solve(void)
{
  int head, tail;
  int s, t, i;
  int half = sum/2;
  short temp;

  memset(pindex, 0, P*sizeof(*pindex));
  memset(number, 0, (1 << P)*sizeof(*number));

  queue[0] = 0;
  head = 0;
  tail = 1;

  while (head != tail) {
    s = queue[head++];
    for (i = 0; i < P; i++) {
      if ((t = (s | (1 << i))) == s) continue;
      temp = number[s] + votes[i];
      if (temp > half) {
	pindex[i]++;
      } else if (!number[t]) {
	queue[tail++] = t;
	number[t] = temp;
      }
    }
  }

}

int main(void)
{
  int cases;
  int i;

  scanf("%d", &cases);
  while (cases-- > 0) {
    sum = 0;
    scanf("%d", &P);
    for (i = 0; i < P; i++) {
      scanf("%d", votes+i);
      sum += votes[i];
    }
    
    solve();
    for (i = 0; i < P; i++) {
      printf("party %d has power index %d\n", i+1, pindex[i]);
    }
    printf("\n");

  }
  return 0;
}
