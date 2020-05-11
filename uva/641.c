#include <stdio.h>
#include <string.h>

int read_case(char *msg)
{
  int k;
  scanf("%d", &k);
  if (k) {
    scanf("%s", msg);
  }
  return k;
}

void decode(char *msg, int k)
{
  int ciphercode[100], plaincode[100];
  int i, n;
  char *table = "_abcdefghijklmnopqrstuvwxyz.";

  n = 0;
  for (i = 0; msg[i]; i++) {
    ciphercode[i] = strchr(table, msg[i]) - table;
    n++;
  }
  
  for (i = 0; i < n; i++) {
    plaincode[(k*i) % n] = (ciphercode[i] + i) % 28;
  }

  for (i = 0; i < n; i++) {
    putchar(table[plaincode[i]]);
  }
  printf("\n");
}

int main(void)
{
  char msg[100];
  int k;

  while (k = read_case(msg)) {
    decode(msg, k);
  }
  return 0;
}
