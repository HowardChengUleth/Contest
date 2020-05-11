#include <stdio.h>
#include <string.h>

char dict[100][257];
int len[100];
int n;

int read_dict(void)
{
  int i;

  if (scanf("%d", &n) != 1) {
    return 0;
  }
  for (i = 0; i < n; i++) {
    scanf("%s", dict[i]);
    len[i] = strlen(dict[i]);
  }
  return 1;
}

void process(char *rule, int r_i, char *pw, int p_i)
{
  int i;

  if (!rule[r_i]) {
    printf("%s\n", pw);
    return;
  }
  
  if (rule[r_i] == '#') {
    for (i = 0; i < n; i++) {
      strcpy(pw+p_i, dict[i]);
      process(rule, r_i+1, pw, p_i+len[i]);
    }
  } else if (rule[r_i] == '0') {
    for (i = 0; i < 10; i++) {
      pw[p_i] = '0'+i;
      pw[p_i+1] = 0;
      process(rule, r_i+1, pw, p_i+1);
    }
  } else {
    pw[p_i] = rule[r_i];
    pw[p_i+1] = 0;
    process(rule, r_i+1, pw, p_i+1);
  }
}

int main(void)
{
  int num_rules;
  char rule[257];
  char pw[256*256+1];
  int i;
  
  while (read_dict()) {
    scanf("%d", &num_rules);
    printf("--\n");
    for (i = 0; i < num_rules; i++) {
      scanf("%s", rule);
      pw[0] = 0;
      process(rule, 0, pw, 0);
    }
  }


  return 0;
}
