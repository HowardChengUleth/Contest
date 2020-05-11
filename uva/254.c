/* @JUDGE_ID: 1102NT 254 C "" */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

#define MAX_DIGIT 8
#define BASE 10000
#define LOG_BASE 4
#define FMT_STR "%04d"

typedef int BigNum[MAX_DIGIT];
BigNum two, three;


static void copy(BigNum a, BigNum b)
{
  int i;
  for (i = 0; i < MAX_DIGIT; i++) {
    a[i] = b[i];
  }
}

static void clear(BigNum a)
{
  int i;
  for (i = 0; i < MAX_DIGIT; i++) {
    a[i] = 0;
  }
}

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

static void inc(BigNum a)
{
  BigNum one;
  clear(one);
  one[0] = 1;
  add(a, one, a);
}

static void dec(BigNum a)
{
  BigNum one;
  clear(one);
  one[0] = 1;
  subtract(a, one, a);
}

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
  int i;
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

static void power(BigNum x, int y, BigNum result)
{
  BigNum sx, t;

  clear(result);
  inc(result);
  copy(sx, x);

  while (y > 0) {
    if (y & 0x01) {
      y--;
      mult(result, sx, t);
      copy(result, t);
    } else {
      y >>= 1;
      mult(sx, sx, t);
      copy(sx, t);
    }
  }
}

static void divide2(BigNum a, int digit, int *r)
{
    int i, t;
    *r = 0;
    for (i = MAX_DIGIT-1; i >= 0; i--) {
	t = a[i] + (*r)*BASE;
	a[i] = t / digit;
	*r = t % digit;
    }
}

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

void do_case(int num, BigNum moves)
{
    int len[3], disks[3][101];
    int i, i1, i2, i3, t, k, j, d;
    BigNum mask, t1, t2;

    for (i = 0; i < 3; i++) {
	len[i] = 0;
	disks[i][0] = 1000;
    }
    len[0] = num;
    i1 = 0;
    for (i = 1; i <= num; i++) {
	disks[0][i] = num-i+1;
    }
    power(two, num, mask);
    dec(mask);
    d = num;
    while (!is_zero(moves)) {
	if (compare(moves, mask) >= 0) {
	    copy(t1, mask);
	    inc(t1);
	    divide2(t1, 2, &j);
	    clear(t2);
	    t2[0] = i1;
	    add(t1, t2, t1);
	    divide2(t1, 3, &k);
	    for (j = 1; j <= d; j++) {
		disks[k][len[k]+j] = disks[i1][len[i1]-d+j];
	    }
	    len[i1] -= d;
	    len[k] += d;
	    i1 = k;
	    subtract(moves, mask, moves);
	    if (!is_zero(moves)) {
		i2 = (i1) ? 0 : 1;
		i3 = (i1 < 2) ? 2 : 1;
		if (disks[i2][len[i2]] > disks[i3][len[i3]]) {
		    t = i2;
		    i2 = i3;
		    i3 = t;
		}
		disks[i3][len[i3]+1] = disks[i2][len[i2]];
		len[i3]++;
		len[i2]--;
		dec(moves);
	    }
	}
	divide2(mask, 2, &j);
	d--;
    }

    printf("%d %d %d\n", len[0], len[1], len[2]);
}

void main(void)
{
    int n;
    BigNum m, p;

    clear(two);
    inc(two); inc(two);
    copy(three, two);
    inc(three);
    scanf("%d", &n);
    read_num(m);
    while (n > 0 || !is_zero(m)) {
        assert(n <= 100);
	power(two, n, p);
	assert(compare(m, p) == -1);
	do_case(n, m);
	scanf("%d", &n);
	read_num(m);
    }
}
