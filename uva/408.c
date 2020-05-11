/* @JUDGE_ID: 1102NT 408 C "" */

#include <stdio.h>
#include <string.h>

int good(int step, int mod)
{
  char hit[100000];
  int count = 0;
  int curr;

  memset(hit, 0, mod);
  curr = 0;
  while (!hit[curr]) {
    hit[curr] = 1;
    count++;
    curr = (curr + step) % mod;
  }
  return count == mod;
}

int main(void)
{
  int step, mod;
  
  while (scanf("%d %d", &step, &mod) == 2) {
    printf("%10d%10d    %s Choice\n", step, mod, 
	   good(step, mod) ? "Good" : "Bad");
    printf("\n");
  }
  return 0;
}
