/* @JUDGE_ID: 1102NT 277 C "" */

/* modified I/O to make online judge happy */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_token(char *ptr, char *res)
{
  while (*ptr != ',' && *ptr != '\n') {
    *res++ = *ptr++;
  }
  *res = 0;
  if (*ptr == ',') {
    return ptr+1;
  } else {
    return 0;
  }

}

int do_case(void)
{
  char buffer[1024], *ptr, curr_desc[1024];
  char field[5][1024];
  int curr_id = -1;
  int i;

  while (fgets(buffer, 1024, stdin)) {
    if (buffer[0] == '\n') {
      return 1;
    }
    if (curr_id == -1) {
      printf("Item Id,Item Desc,Item Price\n");
    }
    for (i = 0; i < 5; i++) {
      field[i][0] = 0;
    }
    ptr = buffer;
    i = 0;
    while (ptr = get_token(ptr, field[i++]))
      ;

    if (curr_id != atoi(field[0])) {
      curr_id = atoi(field[0]);
      strcpy(curr_desc, field[1]);
    }

    if (strlen(field[2]) > 10) {
      continue;
    }
    if (strlen(field[1]) == 0 && strlen(curr_desc) == 0) {
      continue;
    }
    for (i = 0; i < 3-strlen(field[0]); i++) {
      printf("0");
    }
    printf("%s%s,", field[0], field[2]);
    
    if (strlen(field[1]) > 0) {
      sprintf(buffer, "%s", field[1]);
    } else {
      sprintf(buffer, "%s", curr_desc);
    }
    if (strlen(field[3]) > 0) {
      strcat(buffer, "-");
      strcat(buffer, field[3]);
    }
    for (i = 0; i < 30 && buffer[i]; i++) {
      printf("%c", buffer[i]);
    }
    printf(",");

    if (strlen(field[4]) == 0) {
      printf("0.00");
    } else {
      printf("%.2f", (double)atoi(field[4])/100.0);
    }
    printf("\n");
  }
  return 0;
}

int main(void)
{
  int cases;
  scanf("%d\n", &cases);
  while (cases-- > 0) {
    do_case();
    if (cases) {
      printf("\n");
    }
  }
  return 0;
}



