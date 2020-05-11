/* @JUDGE_ID: 1102NT 200 C "Transitive closure" */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

void clear(char rel[26][26], int n)
{
  int i, j;
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      rel[i][j] = 0;
    }
  }
}

void trans_closure(char rel[26][26], int n)
{
  int i, j, k;
  for (k = 0; k < n; k++) {
    for (i = 0; i < n; i++) {
      for (j = 0; j < n; j++) {
        if (rel[i][k] && rel[k][j]) {
          rel[i][j] = 1;
        }
      }
    }
  }
}

void output(char rel[26][26], int used[26])
{
    int index[26], i, j, k, count;

    count = 0;
    for (i = 0; i < 26; i++) {
	index[i] = -1;
	if (used[i]) {
	    count++;
	}
    }
    for (i = 0; i < 26; i++) {
	if (!used[i]) 
	    continue;
	k = 0;
	for (j = 0; j < 26; j++) {
	    if (rel[i][j]) {
		k++;
	    }
	}
	assert(k < count);
	assert(index[k] == -1);
	index[k] = i;
    }
    for (i = count-1; i >= 0; i--) {
       
	printf("%c", 'A'+index[i]);
    }
    printf("\n");
}

void main(void)
{
    char rel[26][26];
    char prev[21], new[21];
    int used[26], i;

    clear(rel, 26);
    for (i = 0; i < 26; i++) {
	used[i] = 0;
    }
    
    scanf("%s", prev);
    for (i = 0; i < strlen(prev); i++) {
	used[prev[i]-'A'] = 1;
    }

    while (scanf("%s", new) == 1 && strcmp(new, "#")) {
	for (i = 0; i < strlen(new); i++) {
	    used[new[i]-'A'] = 1;
	}

	for (i = 0; i < strlen(prev) && i < strlen(new) &&
		    prev[i] == new[i]; i++)
	    ;
	if (i < strlen(prev) && i < strlen(new)) {
	    rel[prev[i]-'A'][new[i]-'A'] = 1;
	}
	strcpy(prev, new);
    }
    trans_closure(rel, 26);
    output(rel, used);
}
