/* @JUDGE_ID: 1102NT 10584 C "" */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>

int C, A;

typedef struct {
  char from[100], to[100];
  char used;
} Mapping;

Mapping *contractions, *acronyms;

void read_mapping(Mapping *mapping)
{
  char buffer[1024];
  char *p;
  int i;

  fgets(buffer, 1024, stdin);
  p = buffer;  assert(*p == '"');
  p++;
  for (i = 0; *p != '"'; i++, p++) {
    mapping->from[i] = *p;
  }
  mapping->from[i] = 0;
  p++;

  while (*p != '"') {
    p++;
  }
  p++;
  for (i = 0; *p != '"'; i++, p++) {
    mapping->to[i] = *p;
  }
  mapping->to[i] = 0;

  mapping->used = 0;
}

void clear_mappings(void)
{
  int i;
  for (i = 0; i < C; i++) {
    contractions[i].used = 0;
  }
  for (i = 0; i < A; i++) {
    acronyms[i].used = 0;
  }
}

void process_line(char *buffer)
{
  int best_ci, best_cstri;
  int best_ai, best_astri;
  char replaceC[1024], replaceA[1024], *p, temp[1024];
  int i, j, t;

  best_ci = best_ai = -1;

  /* look for contractions */
  for (i = 0; i < C; i++) {
    p = strstr(buffer, contractions[i].from);
    if (p && (best_ci < 0 || (p-buffer) < best_cstri)) {
      best_ci = i;
      best_cstri = p-buffer;
      strcpy(replaceC, contractions[i].to);
    }

    strcpy(temp, contractions[i].from);
    for (j = 0; temp[j]; j++) {
      temp[j] = toupper(temp[j]);
    }

    p = strstr(buffer, temp);
    if (p && (best_ci < 0 || (p-buffer) < best_cstri)) {
      best_ci = i;
      best_cstri = p-buffer;
      strcpy(replaceC, contractions[i].to);
      for (j = 0; replaceC[j]; j++) {
	replaceC[j] = toupper(replaceC[j]);
      }
    } 

    strcpy(temp, contractions[i].from);
    temp[0] = toupper(temp[0]);
    p = strstr(buffer, temp);
    if (p && (best_ci < 0 || (p-buffer) < best_cstri)) {
      best_ci = i;
      best_cstri = p-buffer;
      strcpy(replaceC, contractions[i].to);
      replaceC[0] = toupper(replaceC[0]);
    }
  }

  /* look for acronym matches */
  for (i = 0; i < A; i++) {
    if (acronyms[i].used) continue;
    p = strstr(buffer, acronyms[i].from);
    if (!p) continue;
    if (best_ai < 0 || (p-buffer) < best_astri) {
      best_ai = i;
      best_astri = p-buffer;
    }
  }
  if (best_ai >= 0) {
    sprintf(replaceA, "%s (%s)", acronyms[best_ai].to, acronyms[best_ai].from);
  }

  if (best_ci < 0 && best_ai < 0) {
    /* no more matches */
    printf("%s", buffer);
    return;
  }

  /* print all the way to the first match */
  t = (best_ci >= 0) ? best_cstri : 10000;
  if (best_ai >= 0 && best_astri < t) {
    t = best_astri;
  }
  for (i = 0; i < t; i++) {
    putchar(*buffer++);
  }

  if (best_ci >= 0 && best_ai >= 0) {
    if (best_cstri <= best_astri) {
      printf("%s", replaceC);
      process_line(buffer + strlen(contractions[best_ci].from));
    } else {
      printf("%s", replaceA);
      acronyms[best_ai].used = 1;
      process_line(buffer + strlen(acronyms[best_ai].from));
    }
  } else if (best_ci >= 0) {
    printf("%s", replaceC);
    process_line(buffer + strlen(contractions[best_ci].from));
  } else {
    assert(best_ai >= 0);
    printf("%s", replaceA);
    acronyms[best_ai].used = 1;
    process_line(buffer + strlen(acronyms[best_ai].from));
  }
}

int main(void)
{
  char buffer[1024];
  int i;

  scanf("%d %d\n", &C, &A);
  contractions = malloc(C*sizeof(Mapping));
  acronyms = malloc(A*sizeof(Mapping));

  for (i = 0; i < C; i++) {
    read_mapping(&(contractions[i]));
  }
  for (i = 0; i < A; i++) {
    read_mapping(&(acronyms[i]));
  }

  while (fgets(buffer, 1024, stdin)) {
    if (!strcmp(buffer, "#\n")) {
      printf(buffer);
      clear_mappings();
    } else {
      process_line(buffer);
    }
  }

  free(contractions);
  free(acronyms);
  return 0;
}
