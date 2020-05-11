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
#define MAX_DIGIT 30
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

/* result = a - b,
 * result can be the same as one of the operands
 * assumes a >= b
 */
static void subtract(BigNum a, BigNum b, BigNum result);

/* a <<= amount, or a = a*BASE^amount */
static void lshift(BigNum a, int amount);

/* result = a * b, where b is a single digit 
 * result can be the same as a.
 */
static void mult_digit(BigNum a, int b, BigNum result);

/* result = a * b */
static void mult(BigNum a, BigNum b, BigNum result);

/* write BigNum to stdout */
static void write_num(BigNum a);

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

/* perform result = a - b.  assumes a >= b */
static void subtract(BigNum a, BigNum b, BigNum result)
{
  int diff, borrow, i;
  borrow = 0;
  for (i = 0; i < MAX_DIGIT; i++) {
    diff = a[i] - b[i] - borrow;
    result[i] = (diff >= 0) ? diff : diff + BASE;
    borrow = (diff < 0);
  }
  assert(borrow == 0);
}

/* perform a *= BASE^amount */
static void lshift(BigNum a, int amount)
{
  int i;

  if (!amount) {
    return;
  }

  for (i = MAX_DIGIT-1; i >= amount; i--) {
    a[i] = a[i-amount];
  }
  for (i = 0; i < amount; i++) {
    a[i] = 0;
  }
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

/* result = a * b */
static void mult(BigNum a, BigNum b, BigNum result)
{
  int i;
  BigNum temp1;

  clear(result);

  for (i = 0; i < MAX_DIGIT; i++) {
    if (b[i] != 0) {
      copy(temp1, a);
      lshift(temp1, i);
      mult_digit(temp1, b[i], temp1);
      add(temp1, result, result);
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




/* f[n][d] = number of strings of length n and depth <= d */
BigNum f[301][151];
char init[301][151];

void calcf(int n, int d)
{
  if (!init[n][d]) {
    if (n == 0) {
      convert_from_int(f[n][d], 1);
    } else if (d == 0) {
      clear(f[n][d]);
    } else {
      /* S is a string of length n and depth <= d if it can be written as
	 S = (A)B  where A has depth at most d-1 and B has depth at most d. */
      BigNum prod;
      int k;
      clear(f[n][d]);
      for (k = 2; k <= n; k += 2) {  /* k = length of (A) */
	calcf(k-2, d-1);
	calcf(n-k, d);
	mult(f[k-2][d-1], f[n-k][d], prod);
	add(f[n][d], prod, f[n][d]);
      }
    }
    init[n][d] = 1;
  }
}

int main(void)
{
  int n, d;
  BigNum ans;

  for (n = 0; n <= 300; n += 2) {
    for (d = 0; d <= 150; d += 2) {
      calcf(n, d);
    }
  }

  while (scanf("%d %d", &n, &d) == 2) {
    calcf(n, d);
    calcf(n, d-1);
    subtract(f[n][d], f[n][d-1], ans);
    write_num(ans);  printf("\n");
  }

  return 0;
}


