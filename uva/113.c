/* @JUDGE_ID: 1102NT 113 C "" */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define MAX_DIGIT 60
#define BASE 10000
#define LOG_BASE 4

typedef int BigNum[MAX_DIGIT];

static void print_header(void);
static void print_trailer(void);
static void copy(BigNum a, BigNum b);
static void clear(BigNum a);
static int is_zero(BigNum a);
static int compare(BigNum a, BigNum b);
static void add(BigNum a, BigNum b, BigNum result);
static void subtract(BigNum a, BigNum b, BigNum result);
static void inc(BigNum a);
static void lshift(BigNum a, int amount);
static int divisible(BigNum a, BigNum b, BigNum q);
static void mult_digit(BigNum a, int b, BigNum result);
static void mult(BigNum a, BigNum b, BigNum result);
static int check_power(BigNum k, BigNum p, int n);
static void read_num(BigNum a);
static void write_num(BigNum a);
static int div2(BigNum a, BigNum result);

int main(void)
{
  BigNum p, l, r, sum, m, one, two;
  int n, t, found;

  clear(one); inc(one);
  clear(two); inc(two); inc(two);

  while (scanf("%d", &n) == 1) {
    read_num(p);

    /* do binary search */
    clear(l);
    inc(l);
    copy(r, p);
    found = 0;
    while (!found && compare(l, r) <= 0) {
      add(l, r, sum);
      div2(sum, m);
      t = check_power(m, p, n);
      if (t == 0) {
	write_num(m);
	printf("\n");
	found = 1;
      } else if (t > 0) {
	subtract(m, one, r);
      } else {
	add(m, one, l);
      }
    }
    assert(found);
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
  int sum, carry, i;
  carry = 0;
  for (i = 0; i < MAX_DIGIT; i++) {
    sum = a[i] + b[i] + carry;
    result[i] = sum % BASE;
    carry = (sum >= BASE) ? 1 : 0; 
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
    borrow = (diff < 0) ? 1 : 0;
  }
  assert(borrow == 0);
}

/* perform a++ */
static void inc(BigNum a)
{
  BigNum one, result;
  clear(one);
  one[0] = 1;
  add(a, one, result);
  copy(a, result);
}

/* perform a *= BASE^amount */
static void lshift(BigNum a, int amount)
{
  int i;

  if (amount <= 0) {
    return;
  }

  for (i = MAX_DIGIT-1; i >= amount; i--) {
    a[i] = a[i-amount];
  }
  for (i = 0; i < amount; i++) {
    a[i] = 0;
  }
}

static int divisible(BigNum a, BigNum b, BigNum q)
{
  BigNum one, r, t, q_temp, diff, s;
  int shift;

  clear(one);
  inc(one);

  copy(r, a);
  clear(q);

  while (compare(r, b) >= 0) {
   
    /* find biggest shift t of b st t <= r */
    copy(t, b);
    lshift(t, 1);
    shift = 0;
    while (compare(t, r) <= 0 && shift < MAX_DIGIT-1) {
      shift++;
      lshift(t, 1);
    }

    /* we do the shifts */
    copy(t, b);
    lshift(t, shift);
    copy(q_temp, one);
    lshift(q_temp, shift);

    /* now start subtracting as much as possible */
    while (compare(r, t) >= 0) {
      subtract(r, t, diff);
      copy(r, diff);
      add(q, q_temp, s);
      copy(q, s);
    }
  }

  return is_zero(r);
}

static int div2(BigNum a, BigNum result)
{
  int i;
  int carry = 0;

  clear(result);
  for (i = MAX_DIGIT-1; i >= 0; i--) {
    if (carry) {
      result[i] = (a[i]+BASE) / 2;
    } else {
      result[i] = a[i] / 2;
    }
    if (a[i] & 0x01) {
      carry = 1;
    }
  }
}

static void mult_digit(BigNum a, int b, BigNum result)
{
  int i, carry;
  int prod;

  assert(0 <= b && b < BASE);
  clear(result);
  carry = 0;
  for (i = 0; i < MAX_DIGIT; i++) {
    prod = b * a[i];
    result[i] = (carry + prod) % BASE;
    carry = (carry + prod) / BASE;
  }
  assert(carry == 0);
}

static void mult(BigNum a, BigNum b, BigNum result)
{
  int i, j;
  BigNum temp1, temp2;

  clear(result);

  for (i = 0; i < MAX_DIGIT; i++) {
    if (b[i] != 0) {
      copy(temp1, a);
      lshift(temp1, i);
      mult_digit(temp1, b[i], temp2);
      add(temp2, result, result);
    }
  }
}

/* 
   returns 1 if k^n > p
           0 if k^n = p
          -1 if k^n < p
 */

static int check_power(BigNum k, BigNum p, int n)
{
  BigNum res, x, t;

  clear(res);
  inc(res);
  copy(x, k);

  while (n > 0) {
    if (n & 0x01) {
      n--;
      mult(res, x, t);
      copy(res, t);
    } else {
      n >>= 1;
      mult(x, x, t);
      copy(x, t);
    }
    if (compare(res, p) > 0 || compare(x, p) > 0) {
      return 1;
    }
  }

  return compare(res, p);

}

static void read_num(BigNum a)
{
  char buffer[1024];
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
	printf("%d", a[i]);
      } else if (a[i]) {
	printf("%d", a[i]);
	writing = 1;
      } 
    }
  }
}
