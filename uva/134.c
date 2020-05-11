/* @JUDGE_ID: 1102NT 134 C "" */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>

/* token types */

enum {
  TOK_A, TOK_MOD, TOK_BA, TOK_DA, TOK_LA, TOK_NAM, TOK_PREDA, TOK_ERROR
} Token;

static char vowel[6] = "aeiou";
int printing = 0;

char tokens[40960];
int num;

int recognize(char *buffer, int len, int *eol)
{

  /* check eol */
  if (buffer[len-1] == '.') {
    *eol = 1;
    buffer[len-1] = 0;
    len--;
  } else {
    *eol = 0;
  }

  if (len <= 0) {
    return TOK_ERROR;
  }

  /* check A */
  if (len == 1 && strchr(vowel, buffer[0])) {
    return TOK_A;
  }

  /* check MOD, BA, DA, LA */
  if (len == 2 && strchr(vowel, buffer[1])) {
    switch (buffer[0]) {
    case 'g':
      return TOK_MOD;
    case 'b':
      return TOK_BA;
    case 'd':
      return TOK_DA;
    case 'l':
      return TOK_LA;
    default:
      return TOK_ERROR;
    }
  }


  /* check pred */
  if (len == 5 && !strchr(vowel, buffer[0]) && 
      !strchr(vowel, buffer[3]) && strchr(vowel, buffer[4])) {
    if ((!strchr(vowel, buffer[1]) && strchr(vowel, buffer[2])) ||
	(strchr(vowel, buffer[1]) && !strchr(vowel, buffer[2]))) {
      return TOK_PREDA;
    }
  }

  /* assume everything else is a name */
  if (!strchr(vowel, buffer[len-1])) {
    return TOK_NAM;
  }

  return TOK_ERROR;
}

/* get the next sentence into tokens */
int read_sentence(void) {
  char buffer[40960];
  int len, eol, t;

  num = 0;
  do {
    scanf("%s", buffer);
    len = strlen(buffer);
    if (!strcmp(buffer, "#")) {
      return 0;
    }
    t = recognize(buffer, len, &eol);

    tokens[num++] = t;
  } while (!eol);
  return 1;
}

int predstring(int start, int len)
{
  int i;

  for (i = 0; i < len; i++) {
    if (tokens[i+start] != TOK_PREDA) {
      return 0;
    }
  }
  return 1;
}

int verbpred(int start, int len)
{
  return (tokens[start] == TOK_MOD && predstring(start+1, len-1));
}

int statement(int start, int len)
{
  int found = 0;
  int i, j;

  /* look for first MOD */
  for (i = start; i < start+len && !found; i++) {
    if (tokens[i] == TOK_MOD) {
      found = 1;
    }
  }
  if (!found) {
    return 0;
  }
  i--;
  assert(tokens[i] == TOK_MOD);
  
  /* check first part is a predname */
  if (!predname(start, i-start)) {
    return 0;
  }
  
  /* look for LA or NAM */
  found = 0;
  for (j = i; j < start+len && !found; j++) {
    if (tokens[j] == TOK_LA || tokens[j] == TOK_NAM) {
      found = 1;
    }
  }
  j--;
  if (found) {
    return verbpred(i, j-i) && predname(j, start+len-j);
  } else {
    return verbpred(i, start+len-i);
  }
}

int preds(int start, int len)
{
  int i;

  if (predstring(start, len)) {
    return 1;
  }
  
  for (i = start+1; i < start+len-1; i++) {
    if (tokens[i] == TOK_A) {
      return (predstring(start, i-start) && preds(i+1, start+len-i-1));
    }
  }

  return 0;
}

int predname(int start, int len)
{
  if (len == 1 && tokens[start] == TOK_NAM) {
    return 1;
  }
  return (tokens[start] == TOK_LA && predstring(start+1, len-1));
}

int predclaim(int start, int len)
{
  int i;

  if (tokens[start] == TOK_DA) {
    return preds(start+1, len-1);
  }

  for (i = start+1; i < start+len-1; i++) {
    if (tokens[i] == TOK_BA) {
      if (predname(start, i-start) && preds(i+1, start+len-i-1)) {
	return 1;
      }
    }
  }

  return 0;
}

/* parse the sentence */
int sentence(int start, int len)
{
  int i;

  /* first, check for TOK_ERROR */
  for (i = 0; i < len; i++) {
    if (tokens[i+start] == TOK_ERROR) {
      return 0;
    }
  }

  return (statement(start, len) || predclaim(start, len));
}

int main(void)
{
  while (read_sentence()) {
    if (sentence(0, num)) {
      printf("Good\n");
    } else {
      printf("Bad!\n");
    }
  }
  return 0;
}  


