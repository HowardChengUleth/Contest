/* @JUDGE_ID: 1102NT 160 C "Brute force" */

int prime[101];
int freq[101];

void find_primes(void)
{
  int i, j;
  
  prime[0] = prime[1] = 0;
  for (i = 2; i <= 100; i++) {
    prime[i] = 1;
    for (j = 2; j * j <= i && prime[i]; j++) {
      if (i % j == 0) {
	prime[i] = 0;
      }
    }
  }
}

int power(int d, int n)
{
  int c = 0;

  while (n % d == 0) {
    c++;
    n /= d;
  }
  return c;
}

int main(void)
{
  int n, i, j;
  int count;

  find_primes();
  while (scanf("%d", &n) == 1 && n > 0) {
    count = 0;
    for (i = 0; i <= 100; i++) {
      freq[i] = 0;
    }
    printf("%3d! =", n);

    for (i = 2; i <= n; i++) {
      for (j = 2; j <= i; j++) {
	if (prime[j]) {
	  freq[j] += power(j, i);
	}
      }
    }

    for (i = 2; i <= 100; i++) {
      if (freq[i]) {
	if (count > 0 && count % 15 == 0) {
	  printf("\n      ");
	}
	printf("%3d", freq[i]);
	count++;
      }
    }
    printf("\n");
  }
  return 0;
}
