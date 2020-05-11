#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define G 34943

int get_crc(char *buffer)
{
  int len = strlen(buffer);
  int i, res;
  unsigned int rem;

  rem = 0;
  for (i = 0; i < len; i++) {
    rem = ((rem << 8) + buffer[i]) % G;
  }
  rem = (rem << 16) % G;
  res = (G - rem) % G;
  assert(0 <= res && res < G);
  return res;
}

int main(void)
{
  char buffer[2048];
  int crc;

  while (fgets(buffer, 2048, stdin) && buffer[0] != '#') {
    assert(buffer[strlen(buffer)-1] == '\n');
    buffer[strlen(buffer)-1] = 0;
    crc = get_crc(buffer);
    printf("%02X %02X \n", crc >> 8, crc & 0xFF);
  }
  return 0;
}
