#include <stdio.h>

int A[10][10];
int n;

int main(void)
{
  int i, j, k;
  int sum[50];
  int case_num = 1;

  while (scanf("%d", &n) == 1 && n) {
    for (i = 0; i < n; i++) {
      for (j = 0; j < n; j++) {
	scanf("%d", &A[i][j]);
      }
    }
    for (i = 0; i < (n+1)/2; i++) {
      sum[i] = 0;
      for (j = i; j < n-i; j++) {
	for (k = i; k < n-i; k++) {
	  sum[i] += A[j][k];
	}
      }
    }
    for (i = 0; i < (n+1)/2-1; i++) {
      sum[i] -= sum[i+1];
    }

    printf("Case %d:", case_num++);
    for (i = 0; i < (n+1)/2; i++) {
      printf(" %d", sum[i]);
    }
    printf("\n");
  }
  return 0;
}
