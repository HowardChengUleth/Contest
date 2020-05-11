#include <stdio.h>
#include <string.h>

int main(void)
{
  int T, N;
  char word[1001];
  int G[26][26];
  int in_deg[26], out_deg[26];
  int i, j, k, n;
  int start, end;
  int good;
  

  scanf("%d", &T);
  while (T-- > 0) {
    for (i = 0; i < 26; i++) {
      in_deg[i] = out_deg[i] = 0;
      for (j = 0; j < 26; j++) {
	G[i][j] = 0;
      }
      G[i][i] = 1;
    }

    scanf("%d", &N);
    while (N-- > 0) {
      scanf("%s", word);
      n = strlen(word);
      G[word[0]-'a'][word[n-1]-'a'] = 1;
      out_deg[word[0]-'a']++;
      in_deg[word[n-1]-'a']++;
    }

    for (k = 0; k < 26; k++) {
      for (i = 0; i < 26; i++) {
	for (j = 0; j < 26; j++) {
	  G[i][j] |= (G[i][k] & G[k][j]);
	}
      }
    }

    start = -1;
    end = -1;
    good = 1;
    for (k = 0; k < 26; k++) {
      if (!in_deg[k] && !out_deg[k]) continue;
      if (out_deg[k] == in_deg[k]+1) {
	if (start == -1) {
	  start = k;
	} else {
	  good = 0;
	}
      } else if (out_deg[k]+1 == in_deg[k]) {
	if (end == -1) {
	  end = k;
	} else {
	  good = 0;
	}
      } else {
	good &= (out_deg[k] == in_deg[k]);
      }
    }

    /* eulerian cycle instead of path */
    if (start == -1 && good) {
      start = 0;
    }

    for (k = 0; k < 26 && good; k++) {
      if (!in_deg[k] && !out_deg[k]) continue;
      good &= G[start][k];
    }

    if (good) {
      printf("Ordering is possible.\n");
    } else {
      printf("The door cannot be opened.\n");
    }

  }
  return 0;
}
