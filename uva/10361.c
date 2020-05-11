#include <stdio.h>
#include <string.h>

int main(void)
{
  int n;
  char line1[102], line2[102], s[6][101];
  char *p, *p2;
  int i;

  scanf("%d", &n);
  fgets(line1, 102, stdin);
  while (n-- > 0) {
    fgets(line1, 102, stdin);
    fgets(line2, 102, stdin);

    i = 1;

    p = line1;
    p2 = strchr(p, '<');
    *p2 = 0;
    strcpy(s[i++], p);
    printf("%s", p);

    p = p2+1;
    p2 = strchr(p, '>');
    *p2 = 0;
    strcpy(s[i++], p);
    printf("%s", p);

    p = p2+1;
    p2 = strchr(p, '<');
    *p2 = 0;
    strcpy(s[i++], p);
    printf("%s", p);

    p = p2+1;
    p2 = strchr(p, '>');
    *p2 = 0;
    strcpy(s[i++], p);
    printf("%s", p);

    p = p2+1;
    p2 = strchr(p, '\n');
    *p2 = 0;
    strcpy(s[i++], p);
    printf("%s", p);

    printf("\n");

    p = strstr(line2, "...");
    *p = 0;
    printf("%s%s%s%s%s\n", line2, s[4], s[3], s[2], s[5]);
  }
  return 0;
}
