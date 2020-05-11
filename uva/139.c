/* @JUDGE_ID: 1102NT 139 C "" */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct {
  char code[7];
  int code_len;
  char name[26];
  int price;
} Record;

Record *rec = 0;
int num = 0;

void add(Record *record)
{
  if (!num) {
    rec = malloc(sizeof(*rec));
  } else {
    rec = realloc(rec, (num+1)*sizeof(*rec));
  }
  strcpy(rec[num].code, record->code);
  rec[num].code_len = record->code_len;
  strcpy(rec[num].name, record->name);
  rec[num++].price = record->price;
}

int find_record(char *number)
{
  int i;

  for (i = 0; i < num; i++) {
    int t = strlen(number) - rec[i].code_len;
    if (strstr(number, rec[i].code) == number &&
	((number[0] == '0' && number[1] == '0' &&
	 4 <= t && t <= 10) ||
	(number[0] == '0' && number[1] != '0' &&
	 4 <= t && t <= 7))) {
      return i;
    }
  }
  return -1;
}

void read_code(void)
{
  Record record;
  char buffer[1024], *ptr;

  
  while (fgets(buffer, 1024, stdin) && strcmp(buffer, "000000\n")) {
    ptr = buffer;
    ptr = strtok(buffer, " \n");
    strcpy(record.code, ptr);
    record.code_len = strlen(record.code);
    if (*(ptr + strlen(ptr) + 1) == '$') {
      strcpy(record.name, "");
      ptr = strtok(0, "$ \n");
      record.price = atoi(ptr);
    } else {
      ptr = strtok(0, "$");
      strcpy(record.name, ptr);
      ptr = strtok(0, " \n");
      record.price = atoi(ptr);
    }
    add(&record);
  }
}

void process(void)
{
  char buffer[1024];
  int minutes;
  int index;

  while (scanf("%s", buffer) == 1 && strcmp(buffer, "#")) {
    printf("%-18s", buffer);
    scanf("%d", &minutes);
    index = find_record(buffer);
    if (index >= 0) {
      printf("%-27s", rec[index].name);
      printf("%11s", buffer+rec[index].code_len);
      printf("%7d", minutes);
      printf("%8.2f", rec[index].price / 100.0);
      printf("%9.2f", (rec[index].price*minutes)/100.0);
    } else {
      if (buffer[0] == '0') {
	printf("%-27s", "Unknown");
	printf("%11s", "");
	printf("%7d", minutes);
	printf("%8s", "");
	printf("%9.2f", -1.00);
      } else {
	printf("%-27s", "Local");
	printf("%11s", buffer);
	printf("%7d", minutes);
	printf("%8.2f", 0.00);
	printf("%9.2f", 0.00);
      }
    }
    printf("\n");
  }
}


int main(void)
{
  read_code();
  process();

  return 0;
}
