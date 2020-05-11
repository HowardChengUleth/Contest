#include <stdio.h>

int gcd(int a, int b)
{
  if (!a) return b;
  if (!b) return a;
  return gcd(b, a % b);
}

int main(void)
{
  int i, j, k, index, n, g;
  long long ans;
  char word[21];
  int freq[26];
  int len;
  int numer[20];
  int denom[20];
  
  scanf("%d", &n);
  for (i = 1; i <= n; i++) {
    scanf("%s", word);
    len = 0;
    for (j = 0; j < 26; j++) {
      freq[j] = 0;
    }
    for (j = 0; word[j]; j++) {
      freq[word[j]-'A']++;
      len++;
    }

    for (j = 0; j < len; j++) {
      numer[j] = j+1;
    }      

    index = 0;
    for (j = 0; j < 26; j++) {
      for (k = 0; k < freq[j]; k++) {
	denom[index+k] = k+1;
      }
      index += freq[j];
    }
    
    for (j = 0; j < len; j++) {
      for (k = 0; k < len; k++) {
	g = gcd(numer[j], denom[k]);
	numer[j] /= g;
	denom[k] /= g;
      }
    }

    ans = 1;
    for (j = 0; j < len; j++) {
      ans *= numer[j];
    }
    printf("Data set %d: %lld\n", i, ans);
  }
  return 0;
}
