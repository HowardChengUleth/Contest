/* @JUDGE_ID: 1102NT 499 C "" */

#include <stdio.h>
#include <string.h>

int main(void)
{
  char buffer[20480];
  int ufreq[26], lfreq[26];
  int i, best;

  while (fgets(buffer, 20480, stdin)) {
    for (i = 0; i < 26; i++) {
      ufreq[i] = lfreq[i] = 0;
    }
    for (i = 0; i < strlen(buffer); i++) {
      if ('A' <= buffer[i] && buffer[i] <= 'Z') {
	ufreq[buffer[i]-'A']++;
      } else if ('a' <= buffer[i] && buffer[i] <= 'z') {
	lfreq[buffer[i]-'a']++;
      }
    }
    best = 0;
    for (i = 0; i < 26; i++) {
      if (ufreq[i] > best) {
	best = ufreq[i];
      }
      if (lfreq[i] > best) {
	best = lfreq[i];
      }
    }
    for (i = 0; i < 26; i++) {
      if (ufreq[i] == best) {
	putchar('A'+i);
      }
    }
    for (i = 0; i < 26; i++) {
      if (lfreq[i] == best) {
	putchar('a'+i);
      }
    }
    printf(" %d\n", best);
  }
  return 0;
}
