#include <stdio.h>
#include <string.h>
#include <assert.h>

const char *h_month_name[19] = {
  "pop", "no", "zip", "zotz", "tzec", "xul", "yoxkin", "mol", "chen", 
  "yax", "zac", "ceh", "mac", "kankin", "muan", "pax", "koyab", "cumhu", 
  "uayet"};
const char *t_day_name[20] = {
  "imix", "ik", "akbal", "kan", "chicchan", "cimi", "manik", "lamat", "muluk",
  "ok", "chuen", "eb", "ben", "ix", "mem", "cib", "caban", "eznab", "canac", 
  "ahau"};

int main(void)
{
  int n;
  char line[1000];

  int days;
  int h_day, h_month, h_year;
  int t_year, t_num, t_day_index;


  scanf("%d", &n);
  printf("%d\n", n);
  while (n-- > 0) {
    scanf("%d. %s %d", &h_day, line, &h_year);
    for (h_month = 0; h_month < 19 && strcmp(h_month_name[h_month], line); 
	 h_month++) 
      ;
    assert(h_month < 19);
    days = 365*h_year + 20*h_month + h_day;

    t_year = days / (13*20);
    days %= (13 * 20);
    t_num = days % 13 + 1;
    t_day_index = days % 20;
    
    printf("%d %s %d\n", t_num, t_day_name[t_day_index], t_year);
  }
  return 0;
}
