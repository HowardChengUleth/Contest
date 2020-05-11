#include <stdio.h>
#include <string.h>

int value(char *p)
{
  int s = 0;
  
  while (*p) {
    s = s * 32 + (*p - 'a' + 1);
    p++;
  }
  return s;
}

long long getC(int *w, int n)
{
  long long C, newC;
  int done;
  int i, j, ti, tj, t;
  
  C = w[0];
  for (i = 1; i < n; i++) {
    if (w[i] < C) {
      C = w[i];
    }
  }

  while (1) {
    done = 1;
    newC = C;
    for (i = 0; i < n; i++) {
      for (j = i+1; j < n; j++) {
	if ((C/w[i]) % n == (C/w[j]) % n) {
	  done = 0;
	  ti = (C/w[i] + 1) * w[i];
	  tj = (C/w[j] + 1) * w[j];
	  t = (ti < tj) ? ti : tj;
	  if (t > newC) {
	    newC = t;
	  }
	}
      }
    }
    if (done) {
      return C;
    }
    C = newC;
  }
}

int main(void)
{
  char line[1024];
  int w[13];
  int n;
  char *p;

  while (fgets(line, 1024, stdin)) {
    printf("%s", line);
    n = 0;
    for (p = line; p = strtok(p, " \n"); p = NULL) {
      w[n++] = value(p);
    }
    printf("%lld\n\n", getC(w, n));
  }
  
  return 0;
}
