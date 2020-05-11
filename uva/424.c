/* @JUDGE_ID: 1102NT 424 C "" */


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
#define MAX_DIGIT 40
#define BASE 10000
#define LOG_BASE 4
#define FMT_STR "%04d"

typedef int BigNum[MAX_DIGIT];

/*
 * For all operations taking a "result" parameter, it cannot be the
 * same as one of the operands unless stated otherwise.
 *
 */

/* a = 0 */
static void clear(BigNum a);

/* a == 0 */
static int is_zero(BigNum a);

/* result = a + b,
 * result can be the same as one of the operands
 */
static void add(BigNum a, BigNum b, BigNum result);

/* read BigNum from stdin */
static void read_num(BigNum a);

/* write BigNum to stdout */
static void write_num(BigNum a);

int main(void)
{
  BigNum sum, a;

  clear(sum);
  for (read_num(a); !is_zero(a); read_num(a)) {
    add(sum, a, sum);
  }
  write_num(sum);
  printf("\n");
  return 0;
}

/* perform assignment a = 0 */
static void clear(BigNum a)
{
  int i;
  for (i = 0; i < MAX_DIGIT; i++) {
    a[i] = 0;
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

/* read BigNum from stdin */
static void read_num(BigNum a)
{
  char buffer[1024];     /* increase if necessary */
  int i, j, k, t, len, limit, mult;

  t = scanf("%s", buffer);
  assert(t == 1);
  len = strlen(buffer);
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
        a[i] += (buffer[j] - '0') * mult;
      }
      j--;
      mult *= 10;
    }
  }
}

/* write BigNum to stdout */
static void write_num(BigNum a)
{
  int i, k, writing;

  if (is_zero(a)) {
    printf("0");
  } else {
    k = 0;
    writing = 0;
    for (i = MAX_DIGIT-1; i >= 0; i--) {
      assert(0 <= a[i] && a[i] < BASE);
      if (writing) {
        printf(FMT_STR, a[i]);
      } else if (a[i]) {
        printf("%d", a[i]);
        writing = 1;
      }
    }
  }
  fflush(stdout);
}



