#include <stdio.h>
#include <string.h>

int main(void)
{
  char G[26][26];
  int deg[26];
  char lit[26];
  char str[256], M, T, *p;
  char u;
  int k, i, step, done, printed;

  while (scanf("%s", str) == 1 && *str != '#') {
    for (i = 0; i < 26; i++) {
      deg[i] = 0;
      lit[i] = 0;
    }
    for (p = str; p = strtok(p, ";."); p = NULL) {
      u = *p-'A';
      p++; p++;
      while (*p) {
	G[u][deg[u]++] = *p-'A';
	p++;
      }
    }

    scanf("%s", str);
    M = str[0]-'A';
    scanf("%s", str);
    T = str[0]-'A';
    scanf("%d", &k);
    
    step = 0;
    done = printed = 0;
    while (!done) {
      for (i = 0; i < deg[M] && (lit[G[M][i]] || G[M][i] == T); i++) 
	;
      if (i >= deg[M]) {
	done = 1;
      } else {
	T = M;
	M = G[M][i];
	if (++step == k) {
	  step = 0;
	  lit[T] = 1;
	  if (printed) {
	    putchar(' ');
	  }
	  putchar(T+'A');
	  printed = 1;
	}
      }
    }
    if (printed) {
      putchar(' ');
    }
    putchar('/');
    putchar(M+'A');
    putchar('\n');
    
  }
  return 0;
}
