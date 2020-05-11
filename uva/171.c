#include <stdio.h>
#include <string.h>
#include <ctype.h>

int nnn(char list[100][100], int start, int end)
{
  int i;

  if (start+1 != end) return 0;
  for (i = 0; list[start][i]; i++) {
    if (!isdigit(list[start][i]))
      return 0;
  }
  return 1;
}

int cas(char list[100][100], int start, int end)
{
  return ((start+1 == end && !strcmp(list[start], "CAS")) ||
	  (start+3 == end && !strcmp(list[start], "CHANGE") &&
	   !strcmp(list[start+1], "AVERAGE") &&
	   !strcmp(list[start+2], "SPEED")));
}

int change(char list[100][100], int start, int end)
{
  return (start+3 <= end && !strcmp(list[end-1], "KMH") &&
	  !strcmp(list[end-3], "TO") && cas(list, start, end-3) &&
	  nnn(list, end-2, end-1));
}

int record(char list[100][100], int start, int end)
{
  return (start+2 == end) && !strcmp(list[start], "RECORD") &&
    !strcmp(list[start+1], "TIME");
}

int timekeeping(char list[100][100], int start, int end)
{
  return record(list, start, end) || change(list, start, end);
}

int sign(char list[100][100], int start, int end)
{
  int n;
  int i;

  if (start+1 != end) return 0;
  n = strlen(list[start]);
  if (n <= 2 || list[start][0] != '"' || list[start][n-1] != '"' ||
      list[start][1] == ' ') return 0;
  for (i = 1; i < n-1; i++) {
    if (!isupper(list[start][i]) && list[start][i] != '.' &&
	list[start][i] != ' ') {
      return 0;
    }
  }
  return 1;
}

int where(char list[100][100], int start, int end)
{
  return start < end && !strcmp(list[start], "AT") &&
    sign(list, start+1, end);
}
  
int when(char list[100][100], int start, int end)
{
  return (start+1 == end) && (!strcmp(list[start], "FIRST") ||
			      !strcmp(list[start], "SECOND") ||
			      !strcmp(list[start], "THIRD"));
}

int direction(char list[100][100], int start, int end)
{
  return (start+1 == end) && (!strcmp(list[start], "RIGHT") ||
			      !strcmp(list[start], "LEFT"));
}

int how(char list[100][100], int start, int end)
{
  if (start+1 == end) {
    return (!strcmp(list[start], "GO") || !strcmp(list[start], "KEEP"));
  }
  return start < end && !strcmp(list[start], "GO") 
    && when(list, start+1, end);
}

int directional(char list[100][100], int start, int end)
{
  int i, j;

  for (i = start; i <= end; i++) {
    if (how(list, start, i) && direction(list, i, end)) {
      return 1;
    }
    for (j = i; j <= end; j++) {
      if (how(list, start, i) && direction(list, i, j) &&
	  where(list, j, end)) {
	return 1;
      }
    }
  }
  return 0;
}

int navigational(char list[100][100], int start, int end)
{
  int i;

  if (directional(list, start, end)) {
    return 1;
  }

  for (i = start; i < end-1; i++) {
    if (!strcmp(list[i], "AND") && !strcmp(list[i+1], "THEN") &&
	navigational(list, start, i) && directional(list, i+2, end)) {
      return 1;
    }
  }
  return 0;
}

int instruction(char list[100][100], int start, int end)
{
  int i;

  if (navigational(list, start, end) ||
      timekeeping(list, start, end)) {
    return 1;
  }

  for (i = start; i < end; i++) {
    if (!strcmp(list[i], "AND") &&
	navigational(list, start, i) && timekeeping(list, i+1, end)) {
      return 1;
    }
  }

  return 0;
}

int main(void)
{
  char line[1000];
  char list[100][100];
  int num, case_num = 1;
  int i, k;
  int n;

  while (fgets(line, 1000, stdin) && strcmp(line, "#\n")) {
    printf("%3d.", case_num++);
    num = 0;
    

    i = 0; 
    n = strlen(line);
    line[--n] = 0;
    while (i < n && isspace(line[i])) 
      i++;
    while (i < n) {
      k = 0;
      if (line[i] == '"') {
	list[num][k++] = line[i++];
	while (i < n && line[i] != '"') {
	  if (line[i] != ' ' || line[i-1] != ' ') {
	    list[num][k++] = line[i];
	  }
	  i++;
	}
	if (i < n) {
	  list[num][k++] = line[i++];
	}
      } else {
	while (i < n && !isspace(line[i])) {
	  list[num][k++] = line[i++];
	}
      }
      list[num++][k] = 0;
      while (i < n && isspace(line[i])) 
	i++;
    }

    if (instruction(list, 0, num)) {
      for (i = 0; i < num; i++) {
	printf(" %s", list[i]);
      }
      printf("\n");
    } else {
      printf(" Trap!\n");
    }

  }
  return 0;
}
