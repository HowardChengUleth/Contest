/* @JUDGE_ID: 1102NT 10006 C "" */

/* see p. 195 in Rosen, "Elementary number theory and its applications" */

#include <stdio.h>

int carmichael(int n)
{
  int fact, tempn;

  tempn = n;
  if (tempn % 2 == 0) {
    tempn /= 2;
    if (tempn % 2 == 0) {
      return 0;
    }
  }
  
  fact = 3;
  while (fact*fact <= tempn) {
    if (tempn % fact == 0) {
      tempn /= fact;
      if ((n-1) % (fact-1) != 0 || tempn % fact == 0) {
	return 0;
      }
    }
    fact += 2;
  }
  return (tempn != n && (n-1) % (tempn - 1) == 0);
}

int main(void)
{
  int n;

  while (scanf("%d", &n) == 1 && n > 0) {
    if (carmichael(n)) {
      printf("The number %d is a Carmichael number.\n", n);
    } else {
      printf("%d is normal.\n", n);
    }
  }
  return 0;
}
