#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define MAX_VARS  2
#define MAX_CONS  4
#define MAX_ROWS  MAX_VARS+MAX_CONS+1
#define MAX_COLS  MAX_VARS+1

ll euclid(ll u, ll v)
{
  ll w = u / v;
  if (w*v > u) {
    w--;
  }
  if ((w+1)*v <= u) {
    w++;
  }
  return w;
}

int int_prog(ll A[MAX_ROWS][MAX_COLS], int n, int m, ll *value, ll *x)
{
  ll iter, nosol;
  ll b, c, i, j, k, l, r, r1, s, t, denom, num;

  for (j = 0; j < n; j++) {
    if (A[0][j] <= 0) {
      // BAD objective function coefficient: make sure it is positive
      assert(false);
    }
  }
  
  /* set constraints that x[j] >= 0, and clear output */
  for (i = 0; i < n; i++) {
    for (j = 0; j < n+1; j++) {
      A[m+1+i][j] = 0;
    }
    A[m+1+i][i] = -1;
  }
  A[0][n] = 0;

  nosol = 0;
  do {
    r = 0;
    do {
      iter = (A[++r][n] < 0);
    } while (!iter && r != n+m);
    if (iter) {
      for (k = iter = 0; k < n && !iter; k++) {
	iter = (A[r][k] < 0);
      }
      nosol = !iter;
      if (iter) {
	l = k-1;
	for (j = k; j < n; j++) {
	  if (A[r][j] < 0) {
	    for (i = 0; !(s = A[i][j] - A[i][l]); i++)
	      ;
	    if (s < 0) {
	      l = j;
	    }
	  }
	}
	for (s = 0; !A[s][l]; s++)
	  ;
	num = -A[r][l];
	denom = 1;
	for (j = 0; j < n; j++) {
	  if (A[r][j] < 0 && j != l) {
	    for (i = s-1, b = 1; b && i >= 0; i--) {
	      b = (A[i][j] == 0);
	    }
	    if (b) {
	      i = A[s][j];
	      r1 = A[s][l];
	      t = euclid(i, r1);
	      if (t*r1 == i && t > 1) {
		for (i = s+1; !(r1 = t*A[i][l] - A[i][j]); i++)
		  ;
		if (r1 > 0) {
		  t--;
		}
	      }
	      c = -A[r][j];
	      if (c*denom > t*num) {
		num = c;
		denom = t;
	      }
	    }
	  }
	}
	for (j = 0; j <= n; j++) {
	  if (j != l) {
	    c = euclid(A[r][j]*denom, num);
	    if (c) {
	      for (i = 0; i <= n+m; i++) {
		A[i][j] += c*A[i][l];
	      }
	    }
	  }
	}
      }
    }
  } while (iter && !nosol);

  *value = -A[0][n];
  for (j = 0; j < n; j++) {
    x[j] = A[m+1+j][n];
  }

  return !nosol;
}



void parse_button(string s, ll &dx, ll &dy)
{
  istringstream iss(s);
  string word;
  char ch;
  
  iss >> word >> word >> ch >> ch >> dx >> ch >> ch >> ch >> dy;
}

void parse_prize(string s, ll &x, ll &y)
{
  istringstream iss(s);
  string word;
  char ch;

  iss >> word >> ch >> ch >> x >> ch >> ch >> ch >> y;

  const ll adj = 10'000'000'000'000LL;
  x += adj;
  y += adj;
}

ll solve_case()
{
  const int Acost = 3, Bcost = 1;

  string s1, s2, s3, s4;
  getline(cin, s1);
  if (!cin.good()) {
    return -1;
  }
  
  getline(cin, s2);
  getline(cin, s3);
  getline(cin, s4);

  ll Ax, Ay, Bx, By, Tx, Ty;

  parse_button(s1, Ax, Ay);
  parse_button(s2, Bx, By);
  parse_prize(s3, Tx, Ty);

  ll A[MAX_ROWS][MAX_COLS];
  A[1][0] = Ax;  A[1][1] = Bx; A[1][2] = Tx;
  A[2][0] = Ay;  A[2][1] = By; A[2][2] = Ty;
  for (int j = 0; j < 3; j++) {
    A[3][j] = -A[1][j];
    A[4][j] = -A[2][j];
  }
  A[0][0] = Acost;  A[0][1] = Bcost;  A[0][2] = 0;

  ll x[2];
  ll value;
  
  int sol = int_prog(A, 2, 4, &value, x);
  if (sol == 0) {
    return 0;
  } else {
    return value;
  }
}

int main()
{
  ll best_cost = 0, ans = 0;
  while ((best_cost = solve_case()) >= 0) {
    ans += best_cost;
  }

  cout << ans << endl;

  return 0;
}
