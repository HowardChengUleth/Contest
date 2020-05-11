#include <stdio.h>
#include <string.h>
#include <assert.h>

char *code[7] = {
  "AEIOUYWH",
  "BPFV",
  "CSKGJQXZ",
  "DT",
  "L",
  "MN",
  "R"
};

int get_code(char c)
{
  int i;

  for (i = 0; i < 7; i++) {
    if (strchr(code[i], c)) {
      return i;
    }
  }
  assert(0);
}

void soundex(const char *name, char *out)
{
  int prev, curr;
  int written = 0;
  int i;

  out[written++] = name[0];
  prev = get_code(name[0]);

  for (i = 1; name[i] && written < 4; i++) {
    curr = get_code(name[i]);
    if (curr > 0 && curr != prev) {
      out[written++] = curr + '0';
    }
    prev = curr;
  }
  while (written < 4) {
    out[written++] = '0';
  }
  out[written] = 0;
}

int main(void)
{
  char name[30], out[30];
  int i;

  printf("%9sNAME%21sSOUNDEX CODE\n", "", "");

  while (scanf("%s", name) == 1) {
    soundex(name, out);
    printf("%9s%s", "", name);
    for (i = 0; i < 25-strlen(name); i++) {
      putchar(' ');
    }
    printf("%s\n", out);
  }
  printf("%19sEND OF OUTPUT\n", "");
  return 0;
}
