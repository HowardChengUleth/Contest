#include <stdio.h>
#include <string.h>
#include <assert.h>

char *weekday_name[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday",
			"Friday", "Saturday" };
char *month_name[] = {"January", "February", "March", "April", "May",
		      "June", "July", "August", "September", "October",
		      "November", "December"};

int days_in_month[2][12] = {
  {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
  {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int is_new_leap(int year)
{
  return ((year % 4 == 0 && year % 100 != 0) ||
	  (year % 400 == 0));
}

int is_old_leap(int year)
{
  return year % 4 == 0;
}

/* we count Friday 15 Oct 1582 to be day 0 */
int input_to_new_cal(int day, char *month, int year)
{
  int m, y, i;
  int ans = 17+30+31;  /* day number of 1 Jan 1583 */

  for (m = 0; m < 12 && strcmp(month_name[m], month); m++)
    ;
  assert(m < 12);

  for (y = 1583; y < year; y++) {
    ans += (is_new_leap(y)) ? 366 : 365;
  }
  
  for (i = 0; i < m; i++) {
    ans += days_in_month[is_new_leap(year)][i];
  }
  ans += day - 1;
	   
  return ans;
}

/* we count Friday 5 Oct 1582 to be day 0 */
int input_to_old_cal(int day, char *month, int year)
{
  int m, y, i;
  int ans = 27+30+31;  /* day number of 1 Jan 1583 */

  for (m = 0; m < 12 && strcmp(month_name[m], month); m++)
    ;
  assert(m < 12);

  for (y = 1583; y < year; y++) {
    ans += (is_old_leap(y)) ? 366 : 365;
  }
  
  for (i = 0; i < m; i++) {
    ans += days_in_month[is_old_leap(year)][i];
  }
  ans += day - 1;
	   
  return ans;
}

void day_to_new_cal(int day_from_start)
{
  int year;
  int days_in_year;
  int month;
  int day_of_week;

  day_of_week = (5 + day_from_start) % 7;

  day_from_start -= 17+30+31;       /* day from 1 Jan 1583 */
  year = 1583;
  days_in_year = (is_new_leap(year)) ? 366 : 365;
  while (day_from_start >= days_in_year) {
    day_from_start -= days_in_year;
    year++;
    days_in_year = (is_new_leap(year)) ? 366 : 365;
  }
  
  month = 0;
  while (day_from_start >= days_in_month[is_new_leap(year)][month]) {
    day_from_start -= days_in_month[is_new_leap(year)][month];
    month++;
  }
  
  printf("%s %d %s %d\n", weekday_name[day_of_week], day_from_start+1,
	 month_name[month], year);
}

void day_to_old_cal(int day_from_start)
{
  int year;
  int days_in_year;
  int month;
  int day_of_week;

  day_of_week = (5 + day_from_start) % 7;

  day_from_start -= 27+30+31;       /* day from 1 Jan 1583 */
  year = 1583;
  days_in_year = (is_old_leap(year)) ? 366 : 365;
  while (day_from_start >= days_in_year) {
    day_from_start -= days_in_year;
    year++;
    days_in_year = (is_old_leap(year)) ? 366 : 365;
  }
  
  month = 0;
  while (day_from_start >= days_in_month[is_old_leap(year)][month]) {
    day_from_start -= days_in_month[is_old_leap(year)][month];
    month++;
  }
  
  printf("%s %d* %s %d\n", weekday_name[day_of_week], day_from_start+1,
	 month_name[month], year);
}



int main(void)
{
  char weekday[100], month[100];
  int day, year;
  int day_from_start;

  while (scanf("%s", weekday) == 1 && weekday[0] != '#') {
    scanf("%d %s %d", &day, month, &year);

    /* assume that it is the new calendar first */
    day_from_start = input_to_new_cal(day, month, year);

    if (!strcmp(weekday_name[(5 + day_from_start) % 7], weekday)) {
      day_to_old_cal(day_from_start);
    } else {
      /* adjust day_from_start to do old calendar */
      day_from_start = input_to_old_cal(day, month, year);
      assert(!strcmp(weekday_name[(5 + day_from_start) % 7], weekday));
      day_to_new_cal(day_from_start);
    }
  }

  return 0;
}
