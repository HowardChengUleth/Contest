#include <iostream>
#include <string>
#include <cctype>
#include <cassert>

using namespace std;

class Quilt {
private:
  int m, n;
  char **A;
  bool bad;

  void resize(int m2, int n2)
  {
    char **B = new char *[m2];
    for (int i = 0; i < m2; i++) {
      B[i] = new char[n2];
    }
    for (int i = 0; i < m && i < m2; i++) {
      for (int j = 0; j < n && j < n2; j++) {
	B[i][j] = A[i][j];
      }
    }
    for (int i = 0; i < m; i++) {
      delete[] A[i];
    }
    delete[] A;
    A = B;
    m = m2;
    n = n2;
  }

public:
  Quilt(int mm, int nn) 
    : m(0), n(0), A(NULL), bad(0)
  {
    resize(mm, nn);
  }

  Quilt(char type) 
    : m(0), n(0), A(NULL)
  {
    if (bad = !(type == 'A' || type == 'B')) {
      return;
    }

    resize(2, 2);

    if (type == 'A') {
      A[0][0] = A[0][1] = A[1][0] = '/';
      A[1][1] = '+';
    } else {
      A[0][0] = A[0][1] = A[1][0] = A[1][1] = '-';
    }
  }

  Quilt(const Quilt &q)
    : m(0), n(0), A(NULL), bad(q.bad)
  {
    if (bad) return;
    resize(q.m, q.n);
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
	A[i][j] = q.A[i][j];
      }
    }
  }

  Quilt &operator=(const Quilt &q)
  {
    if (this == &q) return *this;
    bad = q.bad;
    if (bad) return *this;
    resize(q.m, q.n);
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
	A[i][j] = q.A[i][j];
      }
    }
    return *this;
  }

  ~Quilt()
  {
    for (int i = 0; i < m; i++) {
      delete[] A[i];
    }
    delete[] A;
    A = NULL;
    m = n = 0;
  }

  void turn()
  {
    if (bad) return;

    Quilt B(n, m);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
	B.A[i][j] = A[m-1-j][i];
	if (B.A[i][j] == '\\') {
	  B.A[i][j] = '/';
	} else if (B.A[i][j] == '/') {
	  B.A[i][j] = '\\';
	} else if (B.A[i][j] == '-') {
	  B.A[i][j] = '|';
	} else if (B.A[i][j] == '|') {
	  B.A[i][j] = '-';
	}
      }
    }

    resize(n, m);

    /* new m is old n, new n is old m now! */
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
	A[i][j] = B.A[i][j];
      }
    }
  }

  void sew(const Quilt &q)
  {
    if (q.bad || m != q.m) {
      bad = 1;
    }
    if (bad) return;

    resize(m, n+q.n);
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < q.n; j++) {
	A[i][n-q.n+j] = q.A[i][j];
      }
    }
  }

  friend ostream &operator<<(ostream &os, const Quilt &q);
};

ostream &operator<<(ostream &os, const Quilt &q)
{
  if (q.bad) {
    os << "error" << endl;
  } else {
    for (int i = 0; i < q.m; i++) {
      for (int j = 0; j < q.n; j++) {
	os << q.A[i][j];
      }
      os << endl;
    }
  }
  return os;
}

void eatspace(void)
{
  while (cin.peek() != EOF && isspace(cin.peek())) {
    cin.ignore(1);
  }
}
  
Quilt expr(void)
{
  int i;
  Quilt a(0,0);

  eatspace();
  switch(cin.peek()) {
  case 'A': case 'B':
    char c;
    cin.get(c);
    return Quilt(c);
  case 't':
    for (i = 0; i < 5; i++) {
      eatspace();
      cin.ignore(1);
    }
    a = expr();
    eatspace();
    cin.ignore(1);
    a.turn();
    return a;
  case 's':
    for (i = 0; i < 4; i++) {
      eatspace();
      cin.ignore(1);
    }
    a = expr();
    eatspace();
    cin.ignore(1);
    a.sew(expr());
    eatspace();
    cin.ignore(1);
    return a;
  default:
    cerr << "Bad input: '" << cin.peek() << "'" << endl;
  }
  return a;
}

int main(void)
{
  int num = 1;

  eatspace();
  while (cin.peek() != EOF) {
    cout << "Quilt " << num++ << ":" << endl;
    Quilt q = expr();
    cout << q;
    eatspace();
    assert(cin.peek() == ';');
    cin.ignore(1);
    eatspace();
  }
  return 0;
}
