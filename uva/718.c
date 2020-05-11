/* @JUDGE_ID: 1102NT 718 C "" */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

int F, E, A, B;
char graph[100][100];
int X[100], Y[100];

void read_case(void)
{
  int i;
  scanf("%d %d %d %d", &F, &E, &A, &B);
  for (i = 0; i < E; i++) {
    scanf("%d %d", X+i, Y+i);
  }
}

long long gcd(long long a, long long b, long long *s, long long *t)
{
  long long r, r1, r2, a1, a2, b1, b2, q;

  a1 = b2 = 1;
  a2 = b1 = 0;

  while (b) {
    q = a / b;
    r = a % b;
    r1 = a1 - q*b1;
    r2 = a2 - q*b2;
    a = b;
    a1 = b1;
    a2 = b2;
    b = r;
    b1 = r1;
    b2 = r2;
  }

  *s = a1;
  *t = a2;
  return a;
}

int connected(int i, int j)
{
  long long s, t, g, f;
  long long k, k1, k2;

  g = gcd(X[i], X[j], &s, &t);
  if ((Y[j]-Y[i]) % g != 0) {
    return 0;
  }
  s *= (Y[j]-Y[i])/g;
  t *= (Y[j]-Y[i])/g;
  
  k1 = ceil(-s*g/(double)X[j]);
  k2 = ceil(t*g/(double)X[i]);
  k = (k1 > k2) ? k1 : k2;
  s = s + k * X[j]/g;
  t = t - k * X[i]/g;
  while (Y[i] + s*X[i] < F) {
    f = Y[j] - t*X[j];
    if (s >= 0 && Y[j] <= f && f < F) {
      return 1;
    }
    s += X[j]/g;
    t -= X[i]/g;
  }

  return 0;
}


void build_graph(void)
{
  int i, j;

  for (i = 0; i < E; i++) {
    graph[i][i] = 1;
    for (j = i+1; j < E; j++) {
      graph[i][j] = graph[j][i] = connected(i, j);
    }
  }
}

void trans_closure(void)
{
  int i, j, k;

  for (k = 0; k < E; k++) {
    for (i = 0; i < E; i++) {
      for (j = 0; j < E; j++) {
	graph[i][j] |= graph[i][k] && graph[k][j];
      }
    }
  }
}

int reach_floor(int i, int floor)
{
  return (floor >= Y[i] && (floor - Y[i]) % X[i] == 0);
}

int reachable(int A, int B)
{
  int i, j;

  if (A == B) {
    return 1;
  }
  for (i = 0; i < E; i++) {
    if (reach_floor(i, A)) {
      for (j = 0; j < E; j++) {
	if (reach_floor(j, B) && graph[i][j]) {
	  return 1;
	}
      }
    }
  }
  return 0;
}

int main(void)
{
  int N;

  scanf("%d", &N);
  while (N-- > 0) {
    read_case();
    build_graph();
    trans_closure();
    if (reachable(A, B)) {
      printf("It is possible to move the furniture.\n");
    } else {
      printf("The furniture cannot be moved.\n");
    }
  }
  return 0;
}
