/*
 * Big integer implementation
 *
 * Author: Howard Cheng
 *
 * Each digit in our representation represents LOG_BASE decimal digits
 *
 */

#include <vector>
#include <string>
#include <cstdio>
#include <cctype>
#include <iostream>
#include <algorithm>
#include <cassert>
#include <cmath>

using namespace std;

typedef long long Digit;
#define BASE 1000000000
#define LOG_BASE 9
#define FMT_STR "%lld"
#define FMT_STR0 "%09lld"

class BigInteger {
private:

  int sign;           // +1 = positive, 0 = zero, -1 = negative
  vector<Digit> mag;  // magnitude
  
  void normalize();

public:
  BigInteger(Digit n = 0);
  string toString() const;        // convert to string

  void clear();  // set to zero

  // comparison
  bool operator<(const BigInteger &a) const;
  bool operator==(const BigInteger &a) const;
  bool isZero() const;

  // arithmetic
  BigInteger &operator+=(const BigInteger &a);
  BigInteger &operator-=(const BigInteger &a);
  BigInteger &operator*=(const BigInteger &a);
  BigInteger &operator*=(Digit a);
  BigInteger &operator<<=(Digit a);
};

BigInteger operator+(const BigInteger &a, const BigInteger &b);
BigInteger operator-(const BigInteger &a, const BigInteger &b);
BigInteger operator*(const BigInteger &a, const BigInteger &b);
BigInteger operator*(const BigInteger &a, Digit b);
BigInteger operator<<(const BigInteger &a, Digit b);
BigInteger operator/(const BigInteger &a, const BigInteger &b);
BigInteger operator/(const BigInteger &a, Digit b);
BigInteger operator%(const BigInteger &a, const BigInteger &b);
Digit operator%(const BigInteger &a, Digit b);

BigInteger power(BigInteger x, Digit y);
ostream &operator<<(ostream &os, const BigInteger &a);

void BigInteger::normalize()
{
  if (mag.size() == 0) {
    return;
  }
  vector<Digit>::iterator p = mag.end();
  do {
    if (*(--p) != 0) break;
  } while (p != mag.begin());
  if (p == mag.begin() && *p == 0) {
    clear();
    sign = 0;
  } else {
    mag.erase(++p, mag.end());
  }
}

BigInteger::BigInteger(Digit n)
{
  if (n == 0) {
    sign = 0;
    return;
  }
  if (n < 0) {
    sign = -1;
    n = -n;
  } else {
    sign = 1;
  }
  
  while (n > 0) {
    mag.push_back(n % BASE);
    n /= BASE;
  }
}

string BigInteger::toString() const
{
  char buffer[LOG_BASE+1];
  string s;

  if (isZero()) {
    return "0";
  } else {
    if (sign < 0) {
      s += "-";
    }
    for (int i = mag.size()-1; i >= 0; i--) {
      if (i == (int)(mag.size()-1)) {
	sprintf(buffer, FMT_STR, mag[i]);
      } else {
	sprintf(buffer, FMT_STR0, mag[i]);
      }
      s += buffer;
    }
    return s;
  }
}

void BigInteger::clear()
{
  sign = 0;
  mag.clear();
}

bool BigInteger::operator<(const BigInteger &a) const
{
  if (sign != a.sign) {
    return sign < a.sign;
  } else if (sign == 0) {
    return false;
  } else if (mag.size() < a.mag.size()) {
    return sign > 0;
  } else if (mag.size() > a.mag.size()) {
    return sign < 0;
  } else {
    for (int i = mag.size()-1; i >= 0; i--) {
      if (mag[i] < a.mag[i]) {
	return sign > 0;
      } else if (mag[i] > a.mag[i]) {
	return sign < 0;
      }
    }
    return false;
  }
}

bool BigInteger::operator==(const BigInteger &a) const
{
  return sign == a.sign && mag == a.mag;
}

bool BigInteger::isZero() const
{
  return sign == 0;
}

BigInteger &BigInteger::operator+=(const BigInteger &a)
{
  if (a.sign == 0) {
    return *this;
  } else if (sign == 0) {
    sign = a.sign;
    mag = a.mag;
    return *this;
  } else if (sign < 0 && a.sign > 0) {
    BigInteger b(a);
    sign = 1;
    b -= *this;
    return *this = b;
  } else if (sign > 0 && a.sign < 0) {
    BigInteger b(a);
    b.sign = 1;
    return (*this) -= b;
  } else {
    Digit carry = 0;
    unsigned int limit = max(mag.size(), a.mag.size());
    for (unsigned int i = 0; i < limit; i++) {
      Digit s1 = (i < mag.size()) ? mag[i] : 0;
      Digit s2 = (i < a.mag.size()) ? a.mag[i] : 0;
      Digit sum = s1 + s2 + carry;
      Digit result = (sum < BASE) ? sum : sum - BASE;
      carry = (sum >= BASE);
      if (i < mag.size()) {
	mag[i] = result;
      } else {
	mag.push_back(result);
      }
    }
    if (carry) {
      mag.push_back(carry);
    }
    return *this;
  }
}

BigInteger &BigInteger::operator-=(const BigInteger &a)
{
  if (a.sign == 0) {
    return *this;
  } else if (sign == 0) {
    sign = -a.sign;
    mag = a.mag;
    return *this;
  } else if (sign != a.sign) {
    BigInteger b(a);
    b.sign *= -1;
    return *this += b;
  } else if (sign < 0) {
    BigInteger b(a);
    b.sign *= -1;
    sign *= -1;
    b -= *this;
    return *this = b;
  } else {
    if (*this == a) {
      clear();
      return *this;
    } else if (*this < a) {
      BigInteger b(a);
      b -= *this;
      b.sign *= -1;
      return *this = b;
    } else {
      // we know that *this > a
      unsigned int limit = mag.size();
      Digit borrow = 0;
      for (unsigned int i = 0; i < limit; i++) {
	Digit s1 = mag[i];
	Digit s2 = (i < a.mag.size()) ? a.mag[i] : 0;
	Digit diff = s1 - s2 - borrow;
	mag[i] = (diff >= 0) ? diff : diff + BASE;
	borrow = (diff < 0);
      }
      normalize();
      return *this;
    }
  }
}

BigInteger &BigInteger::operator*=(const BigInteger &a)
{
  BigInteger temp(*this);
  BigInteger c;
  
  if (this == &a) {
    c = a;          // make a copy to prevent clobbering it
  }

  const BigInteger &b = (this == &a) ? c : a;
  
  clear();
  if (b.sign) {
    for (unsigned int i = 0; i < b.mag.size(); i++) {
      if (b.mag[i] != 0) {
	*this += (temp * b.mag[i]);
      }
      temp <<= 1;
    }
    sign *= b.sign;
  }
  return *this;
}

BigInteger &BigInteger::operator*=(Digit a)
{
  if (a <= -BASE || a >= BASE) {
    BigInteger b(a);
    return (*this *= b);
  }

  if (isZero()) {
    return *this;
  } else if (a == 0) {
    clear();
    return *this;
  } else if (a < 0) {
    sign *= -1;
    a = -a;
  }
    
  Digit carry = 0;
  for (unsigned int i = 0; i < mag.size(); i++) {
    Digit prod = a * mag[i];
    mag[i] = (carry + prod) % BASE;
    carry = (carry + prod) / BASE;
  }
  if (carry) {
    mag.push_back(carry);
  }
  return *this;
}

BigInteger &BigInteger::operator<<=(Digit a)
{
  assert(a >= 0);
  if (sign) {
    while (a-- > 0) {
      mag.insert(mag.begin(), 0);
    }
  }
  return *this;
}

BigInteger operator+(const BigInteger &a, const BigInteger &b)
{
  BigInteger r(a);
  r += b;
  return r;
}

BigInteger operator-(const BigInteger &a, const BigInteger &b)
{
  BigInteger r(a);
  r -= b;
  return r;
}

BigInteger operator*(const BigInteger &a, const BigInteger &b)
{
  BigInteger r(a);
  r *= b;
  return r;
}

BigInteger operator*(const BigInteger &a, Digit b)
{
  BigInteger r(a);
  r *= b;
  return r;
}

BigInteger operator<<(const BigInteger &a, Digit b)
{
  BigInteger r(a);
  r <<= b;
  return r;
}

BigInteger power(BigInteger x, Digit y)
{
  BigInteger result(1), sx(x);
  
  assert(y >= 0);
  while (y > 0) {
    if (y & 0x01) {
      y--;
      result *= sx;
    } else {
      sx *= sx;
      y >>= 1;
    }
  }
  return result;
}

ostream &operator<<(ostream &os, const BigInteger &a)
{
  return (os << a.toString());
}

BigInteger compute(int t, int a, int b)
{
  static BigInteger limit = power(10, 100);
  if (a % b != 0 || (a-b)*log10(t) > 99) {
    return -1;
  }

  if (t == 1) {
    return -1;
  }

  if (a == b) {
    return 1;
  }

  BigInteger ans = 0, mult = 1, p = power(t, b);

  for (int i = 0; i < a/b; i++) {
    ans += mult;
    if (!(ans < limit)) {
      return -1;
    }
    mult *= p;
  }

  return ans;
}


int main(void)
{
  int t, a, b;

  while (cin >> t >> a >> b) {
    cout << '(' << t << '^' << a << "-1)/(" << t << '^' << b << "-1) ";
    BigInteger ans = compute(t, a, b);
    if (ans < 0) {
      cout << "is not an integer with less than 100 digits." << endl;
    } else {
      cout << ans << endl;
    }
  }

  return 0;
}

