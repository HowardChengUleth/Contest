/* @JUDGE_ID: 1102NT 517 C "" */

#include <stdio.h>
#include <string.h>
#include <assert.h>

int n, s;
char word[16];
char rule[8];

int toindex(char *a, int len)
{
  int t = 0;
  int i;

  for (i = 0; i < len; i++) {
    t = t * 2 + (a[i] - 'a');
  }
  return t;
}

int smallest_index(char *a, int len)
{
  int best, i, j;
  char t;

  best = toindex(a, len);
  for (i = 0; i < len; i++) {
    t = a[0];
    for (j = 0; j < len-1; j++) {
      a[j] = a[j+1];
    }
    a[len-1] = t;
    if (best > toindex(a, len)) {
      best = toindex(a, len);
    }
  }
  return best;
}

int read_case(void)
{
  char buffer[5];
  int i, t;

  if (scanf("%d", &n) != 1) {
    return 0;
  }

  scanf("%s", word);
  for (i = 0; i < 8; i++) {
    scanf("%s", buffer);
    t = toindex(buffer, 3);
    rule[t] = buffer[3];
  }
  scanf("%d", &s);

  return 1;
}

void print_word(int index, int n)
{
  char word[16];
  int i;

  word[n] = 0;
  for (i = n-1; i >= 0; i--) {
    word[i] = 'a' + index % 2;
    index /= 2;
  }
  printf("%s\n", word);
}

void apply_rules(char *word, int n)
{
  char word2[16];
  int i, t;

  word2[n] = 0;
  for (i = 0; i < n; i++) {
    t = (((i-2 < 0) ? word[i-2+n] : word[i-2]) - 'a') * 4;
    t += (word[i]-'a')*2;
    t += word[(i+1)%n] - 'a';
    word2[i] = rule[t];
  }
  strcpy(word, word2);
}

void solve_case(void)
{
  int seen[32768];
  int i, count, cycle_len, target;

  for (i = 0; i < (1 << n); i++) {
    seen[i] = 0;
  }

  i = smallest_index(word, n);
  for (count = 0; !seen[i]; count++) {
    seen[i] = count;
    if (s == count) {
      print_word(i, n);
      return;
    }
    apply_rules(word, n);
    i = smallest_index(word, n);
  }

  cycle_len = count - seen[i];
  target = seen[i] + (s - seen[i]) % cycle_len;
  for (i = 0; i < (1 << n); i++) {
    if (seen[i] == target) {
      print_word(i, n);
      return;
    }
  }
  assert(0);
}

int main(void)
{
  while (read_case()) {
    solve_case();
  }
  return 0;
}
