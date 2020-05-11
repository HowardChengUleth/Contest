/* @JUDGE_ID: 1102NT 10606 C "" */

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
#define MAX_DIGIT 12
#define BASE 1000000000
#define LOG_BASE 9
#define FMT_STR "%09lld"

typedef long long BigNum[MAX_DIGIT];

/*
 * For all operations taking a "result" parameter, it cannot be the
 * same as one of the operands unless stated otherwise.
 *
 */

/* a = b */
static void copy(BigNum a, BigNum b);

/* a = 0 */
static void clear(BigNum a);

/* a == 0 */
static int is_zero(BigNum a);

/*
 * return   1 if a > b
 *          0 if a = b
 *         -1 if a < b	
 */
static int compare(BigNum a, BigNum b);

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
static void mult_digit(BigNum a, long long b, BigNum result);

/* result = a * b */
static void mult(BigNum a, BigNum b, BigNum result);

/* read BigNum from stdin */
static void read_num(BigNum a);

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

/* perform comparison between a and b.
   Returns -1 if a < b
            0 if a == b
           +1 if a > b */
static int compare(BigNum a, BigNum b)
{
  int i;
  for (i = MAX_DIGIT-1; i >= 0; i--) {
    if (a[i] < b[i]) {
      return -1;
    } else if (a[i] > b[i]) {
      return 1;
    }
  }
  return 0;
}

/* performs result = a + b */
static void add(BigNum a, BigNum b, BigNum result)
{
  long long sum, carry;
  int i;
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
  long long diff, borrow;
  int i;
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
static void mult_digit(BigNum a, long long b, BigNum result)
{
  int i;
  long long carry, prod;

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

/* read BigNum from stdin */
static void read_num(BigNum a)
{
  char buffer[1024];     /* increase if necessary */
  int i, j, k, t, len, limit;
  long long mult;

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
        printf("%lld", a[i]);
        writing = 1;
      }
    }
  }
  fflush(stdout);
}




int digits(BigNum N)
{
  int i;

  for (i = MAX_DIGIT; i > 0; i--) {
    if (N[i-1]) {
      return i;
    }
  }
  return 1;
}

void square_root(BigNum N, BigNum root)
{
  int d, root_d;
  int k;
  BigNum x, r, t, t2;
  long long lo, hi, mid;

  /* figure out how many digits there are */
  d = digits(N);
  assert(MAX_DIGIT % 2 == 0);
  if (d % 2) d++;
  root_d = d / 2;

  clear(root);
  clear(x);

  clear(r);
  r[1] = N[--d];
  r[0] = N[--d];

  /* figure out one digit at a time */
  for (k = root_d-1; k >= 0; k--) {
    /* invariant: root is the square root (integer part) of the digits 
       processed so far */

    /* look for next digit in root */
    copy(x, root);
    mult_digit(x, 2, x);
    lshift(x, 1);
    clear(t);

    lo = 0;
    hi = BASE;
    
    while (hi - lo > 1) {
      mid = (lo + hi) / 2;
      x[0] = t[0] = mid;
      mult(x, t, t2);
      if (compare(t2, r) <= 0) {
	lo = mid;
      } else {
	hi = mid;
      }
    }

    lshift(root, 1);
    root[0] = lo;

    /* form the next r */
    x[0] = t[0] = lo;
    mult(x, t, t2);
    subtract(r, t2, r);
    lshift(r, 2);
    r[1] = N[--d];
    r[0] = N[--d];
  }
}

int main(void)
{
  BigNum N, root;

  read_num(N);
  while (!is_zero(N)) {
    square_root(N, root);
    mult(root, root, N);
    write_num(N);
    printf("\n");
    read_num(N);
  }
  return 0;
}
