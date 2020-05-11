#include <iostream>
#include <cassert>
#include <algorithm>

using namespace std;

class Fraction {
private:

  long long numer, denom;

  long long gcd(long long a, long long b)
  {
    if (a < 0) {
      return gcd(-a, b);
    }
    if (b < 0) {
      return gcd(a, -b);
    }

    while (b > 0) {
      long long r = a % b;
      a = b;
      b = r;
    }
    return a;
  }

  long long lcm(long long a, long long b)
  {
    return (a/gcd(a,b)) * b;
  }


  void normalize() {
    if (denom < 0) {
      denom *= -1;
      numer *= -1;
    }

    long long g = gcd(numer, denom);
    numer /= g;
    denom /= g;
  }

public:
  Fraction(long long n = 0, long long d = 1)
    : numer(n), denom(d)
  {
    assert(denom != 0);
    normalize();
  }

  Fraction inverse() const
  {
    return Fraction(denom, numer);
  }

  Fraction operator-() const
  {
    return Fraction(-numer, denom);
  }

  Fraction &operator+=(const Fraction &f) 
  {
    long long d = lcm(denom, f.denom);
    long long n = numer * (d/denom) + f.numer * (d/f.denom);
    numer = n;
    denom = d;
    normalize();
    return *this;
  }

  Fraction &operator-=(const Fraction &f) 
  {
    long long d = lcm(denom, f.denom);
    long long n = numer * (d/denom) - f.numer * (d/f.denom);
    numer = n;
    denom = d;
    normalize();

    return *this;
  }

  Fraction &operator*=(const Fraction &f) 
  {
    long long g1 = gcd(denom, f.numer);
    long long g2 = gcd(numer, f.denom);

    g1 = g2 = 1;
    numer /= g2;
    numer *= f.numer/g1;
    denom /= g1;
    denom *= f.denom/g2;
    normalize();
    return *this;
  }

  Fraction &operator/=(const Fraction &f) 
  {
    long long g1 = gcd(numer, f.numer);
    long long g2 = gcd(denom, f.denom);

    g1 = g2 = 1;
    numer /= g1;
    numer *= f.denom/g2;
    denom /= g2;
    denom *= f.numer/g1;
    normalize();
    return *this;
  }

  bool operator==(const Fraction &f)
  {
    return denom == f.denom && numer == f.numer;
  }
  
  friend istream &operator>>(istream &is, Fraction &f);
  friend ostream &operator<<(ostream &os, const Fraction &f);
};

Fraction operator+(const Fraction &f1, const Fraction &f2)
{
  Fraction ans(f1);
  ans += f2;
  return ans;
}

Fraction operator-(const Fraction &f1, const Fraction &f2)
{
  Fraction ans(f1);
  ans -= f2;
  return ans;
}

Fraction operator*(const Fraction &f1, const Fraction &f2)
{
  Fraction ans(f1);
  ans *= f2;
  return ans;
}

Fraction operator/(const Fraction &f1, const Fraction &f2)
{
  Fraction ans(f1);
  ans /= f2;
  return ans;
}

istream &operator>>(istream &is, Fraction &f)
{
  long long n, d;
  
  is >> n;
  if (is.peek() == '/') {
    is.ignore(1);
    is >> d;
  } else {
    d = 1;
  }
  
  f = Fraction(n, d);
  return is;
}

ostream &operator<<(ostream &os, const Fraction &f)
{
  if (f.denom == 1) {
    return os << f.numer;
  } else {
    return os << f.numer << '/' << f.denom;
  }
}

#define MAX_EQNS 53
#define MAX_VARS 53

class Matrix {
private:
  Fraction A[MAX_EQNS][MAX_VARS+1];
  int eqns, vars;

  void swapRows(int row1, int row2);
  void rowMult(int row, const Fraction &s);
  void addRowMult(int row1, const Fraction &s, int row2, int colstart);
  int GaussianElimination();

public:
  
  void solve();
  friend istream &operator>>(istream &is, Matrix &M);
};

istream &operator>>(istream &is, Matrix &M)
{
  is >> M.vars >> M.eqns;
  assert(0 <= M.vars && M.vars <= MAX_VARS &&
	 0 <= M.eqns && M.eqns <= MAX_EQNS);

  for (int i = 0; i < M.eqns; i++) {
    for (int j = 0; j <= M.vars; j++) {
      is >> M.A[i][j];
    }
  }
  return is;
}

void Matrix::swapRows(int row1, int row2)
{
  if (row1 == row2) return;
  for (int j = 0; j <= vars; j++) {
    swap(A[row1][j], A[row2][j]);
  }
}

void Matrix::rowMult(int row, const Fraction &s)
{
  for (int j = 0; j <= vars; j++) {
    A[row][j] *= s;
  }
}

void Matrix::addRowMult(int row1, const Fraction &s, int row2, int colstart)
{
  for (int j = colstart; j <= vars; j++) {
    A[row2][j] += (A[row1][j] * s);
  }
}

int Matrix::GaussianElimination()
{
  int rank = 0;

  // go through each column
  for (int col = 0; col < vars; col++) {
    int pivot;
    for (pivot = rank; pivot < eqns && A[pivot][col] == 0; pivot++)
      ;
    if (pivot >= eqns) {
      // no pivot for this column, skip
      continue;
    }

    // swap the pivot row into this row
    swapRows(rank, pivot);

    // now reduce
    rowMult(rank, A[rank][col].inverse());

    for (int row = 0; row < eqns; row++) {
      if (row == rank) continue;
      addRowMult(rank, -A[row][col], row, col);
    }

    rank++;
  }

  return rank;
}

void Matrix::solve()
{
  int rank = GaussianElimination();

  bool bad = false;
  for (int i = rank; i < eqns && !bad; i++) {
    if (!(A[i][vars] == 0)) {
      bad = true;
    }
  }

  if (bad) {
    cout << "No Solution." << endl;
  } else {
    if (rank == vars) {
      // unique solution
      for (int i = 1; i <= vars; i++) {
	cout << "x[" << i << "] = " << A[i-1][vars] << endl;
      }
    } else {
      cout << "Infinitely many solutions containing " << vars-rank
	   << " arbitrary constants." << endl;
    }
  }
}

bool do_case(bool first)
{
  int set_num = 0;
  cin >> set_num;
  if (set_num == 0) {
    return false;
  }
  if (!first) {
    cout << endl;
  }
  cout << "Solution for Matrix System # " << set_num << endl;

  Matrix M;

  cin >> M;
  M.solve();


  return true;
}

int main(void)
{
  bool first = true;
  while (do_case(first)) {
    first = false;
  }

  return 0;
}
