#include <stdio.h>
#include <ctype.h>

int prime(int n)
{
  int k;
  
  /* beware: the definition of "prime" in this question includes 1 */
  if (n == 1) {
    return 1;
  }
  if (n > 2 && n % 2 == 0) {
    return 0;
  }

  for (k = 3; k*k <= n; k += 2) {
    if (n % k == 0) {
      return 0;
    }
  }
  return 1;

}

int main(void)
{
  char word[100];
  char *p;
  int sum;
  
  while (scanf("%s", word) == 1) {
    sum = 0;
    for (p = word; *p; p++) {
      if (islower(*p)) {
	sum += *p - 'a' + 1;
      } else {
	sum += *p - 'A' + 27;
      }
    }
    printf("It is %s prime word.\n", prime(sum) ? "a" : "not a");
  }

  return 0;
}
