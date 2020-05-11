/* @JUDGE_ID: 1102NT 619 C "" */

/*
 * Big integer implementation
 *
 * Author: Howard Cheng
 *
 * Each digit in our representation represents LOG_BASE decimal digits
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#include <assert.h>
#include <time.h>

/* MAX_DIGIT should be defined to ensure that there is no overflow      */
/* it should be one digit more than the specified bound (for division), */
/* or a few more for safety.                                            */
#define MAX_DIGIT 60
#define BASE 10000
#define LOG_BASE 4
#define FMT_STR "%04d"

typedef int BigNum[MAX_DIGIT];

/*
 * For all operations taking a "result" parameter, it cannot be the
 * same as one of the operands unless stated otherwise.
 *
 */

/* a = b */
static void copy(BigNum a, BigNum b);

/* a = 0 */
static void clear(BigNum a);

/* a = b (a: BigNum, b: int) */
static void convert_from_int(BigNum a, int b);

/* a == 0 */
static int is_zero(BigNum a);

/* result = a + b,
 * result can be the same as one of the operands
 */
static void add(BigNum a, BigNum b, BigNum result);

/* result = a * b, where b is a single digit 
 * result can be the same as a.
 */
static void mult_digit(BigNum a, int b, BigNum result);

/* q = a / b, r = a % b, where b is a single digit 
 * q can be the same as a
 */
static void short_divide(BigNum a, int b, BigNum q, int *r);

/* read BigNum from stdin */
static void read_num(BigNum a, char *str);

/* write BigNum to stdout */
static void write_num(BigNum a, char *str);

void convert_to_str(char *from, char *to)
{
  BigNum a, q;
  char buffer[1024];
  int r, i, j;

  read_num(a, from);
  i = 0;
  while (!is_zero(a)) {
    short_divide(a, 26, q, &r);
    buffer[i++] = r ? ('a' + r - 1) : 'z';
    copy(a, q);
  }
  buffer[i] = 0;
  j = 0;
  while (--i >= 0) {
    to[j++] = buffer[i];
  }
  to[j] = 0;
}

void convert_to_num(char *from, char *to)
{
  BigNum a, b;
  int i;
  
  clear(a);
  for (i = 0; from[i]; i++) {
    mult_digit(a, 26, a);
    convert_from_int(b, from[i]-'a'+1);
    add(a, b, a);
  }
  write_num(a, to);
}

void print_num(char *str)
{
  int n = strlen(str);
  int i;
  int j;

  j = n % 3;
  if (!j) j = 3;

  for (i = 0; i < n; i++) {
    printf("%c", str[i]);
    if (--j == 0) {
      if (i < n-1) {
	printf(",");
      } else {
	printf("\n");
      }
      j = 3;
    }
  }
}

int main(void)
{
  char buffer[1024], buffer2[1024];

  while (scanf("%s", buffer) == 1 && buffer[0] != '*') {
    if (isdigit(buffer[0])) {
      convert_to_str(buffer, buffer2);
    } else {
      strcpy(buffer2, buffer);
      convert_to_num(buffer2, buffer);
    }
    printf("%-22s", buffer2);
    print_num(buffer);
  }

  return 0;
}

/* perform assignment a = b */
static void copy(BigNum a, BigNum b)
{
  int i;
  for (i = 0; i < MAX_DIGIT; i++) {
    a[i] = b[i];
  }
}

/* perform assignment a = 0 */
static void clear(BigNum a)
{
  int i;
  for (i = 0; i < MAX_DIGIT; i++) {
    a[i] = 0;
  }
}

/* a = b (a: BigNum, b: int) */
static void convert_from_int(BigNum a, int b)
{
  int i = 0;
  clear(a);
  while (b > 0) {
    a[i++] = b % BASE;
    b /= BASE;
  }
}

/* perform comparison a == 0 */
static int is_zero(BigNum a)
{
  int i;
  for (i = 0; i < MAX_DIGIT; i++) {
    if (a[i]) {
      return 0;
    }
  }
  return 1;
}

/* performs result = a + b */
static void add(BigNum a, BigNum b, BigNum result)
{
  int sum, carry, i;
  carry = 0;
  for (i = 0; i < MAX_DIGIT; i++) {
    sum = a[i] + b[i] + carry;
    result[i] = (sum < BASE) ? sum : sum - BASE;
    carry = (sum >= BASE);
  }
  assert(carry == 0);       /* assert no overflow */
}

/* result = a * b, where b is a single digit 
 * result can be the same as a.
 */
static void mult_digit(BigNum a, int b, BigNum result)
{
  int i, carry;
  int prod;

  assert(0 <= b && b < BASE);
  carry = 0;
  for (i = 0; i < MAX_DIGIT; i++) {
    prod = b * a[i];
    result[i] = (carry + prod) % BASE;
    carry = (carry + prod) / BASE;
  }
  assert(carry == 0);
}

/* q = a / b, r = a % b, where b is a single digit 
 * q can be the same as a
 */
static void short_divide(BigNum a, int b, BigNum q, int *r)
{
  int i, t;

  assert(0 < b && b < BASE);
  *r = 0;
  for (i = MAX_DIGIT-1; i >= 0; i--) {
    t = (*r) * BASE + a[i];
    q[i] = t / b;
    *r = t - q[i] * b;
  }
}

/* read BigNum from stdin */
static void read_num(BigNum a, char *str)
{
  int i, j, k, len, limit, mult;

  len = strlen(str);
  clear(a);

  if (len % LOG_BASE == 0) {
    limit = len / LOG_BASE;
  } else {
    limit = len / LOG_BASE + 1;
  }

  j = len-1;
  for (i = 0; i < limit; i++) {
    mult = 1;
    for (k = 0; k < LOG_BASE; k++) {
      if (j >= 0) {
        a[i] += (str[j] - '0') * mult;
      }
      j--;
      mult *= 10;
    }
  }
}

/* write BigNum to stdout */
static void write_num(BigNum a, char *str)
{
  char temp[10];
  int i, k, writing;

  if (is_zero(a)) {
    strcpy(str, "0");
  } else {
    str[0] = 0;
    k = 0;
    writing = 0;
    for (i = MAX_DIGIT-1; i >= 0; i--) {
      assert(0 <= a[i] && a[i] < BASE);
      if (writing) {
        sprintf(temp, FMT_STR, a[i]);
	strcat(str, temp);
      } else if (a[i]) {
        sprintf(temp, "%d", a[i]);
	strcat(str, temp);
        writing = 1;
      }
    }
  }
}



