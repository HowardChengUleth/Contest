#include <stdio.h>
#include <ctype.h>
#include <string.h>

int check_int(char *line, int allow_sign)
{
  int len = 0;

  if (allow_sign && (*line == '+' || *line == '-')) {
    line++;
    len++;
  }

  while (*line) {
    if (!isdigit(*line)) {
      return 0;
    }
    line++;
    len++;
  }
  return len > 0;
}

int check_float(char *line)
{
  char *dot_index = strchr(line, '.');
  if (!dot_index) {
    return 0;
  }
  *dot_index = 0;
  
  return check_int(line, 1) && check_int(dot_index+1, 0);
}

int legal(char *line)
{
  int i;
  char *e_index;
  char line2[1024];

  strcpy(line2, line);

  /* find the e/E, if present */
  for (i = 0; line[i]; i++) {
    line2[i] = tolower(line2[i]);
  }
  e_index = strchr(line2, 'e');
  
  if (!e_index) {
    return check_float(line2);
  }

  *e_index = 0;
  return (check_int(line2, 1) || check_float(line2)) && 
    check_int(e_index+1, 1);
}

int main(void)
{
  char line[1024];
  int start;


  while (fgets(line, 1024, stdin) && line[0] != '*') {
    while (isspace(line[strlen(line)-1])) {
      line[strlen(line)-1] = 0;
    }

    /* skip past the spaces */
    for (start = 0; isspace(line[start]); start++)
      ;

    if (legal(line+start)) {
      printf("%s is legal.\n", line+start);
    } else {
      printf("%s is illegal.\n", line+start);
    }
  }
  return 0;
}
