#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>

using namespace std;

void process(double &P, double &U, double &I, const string &p, int pos)
{
  istringstream is(p.substr(pos+1, p.length()-(pos+1)));
  

  double num;
  is >> num;
  
  char prefix;
  is >> prefix;

  switch (prefix) {
  case 'm':
    num /= 1000;
    break;
  case 'k':
    num *= 1000;
    break;
  case 'M':
    num *= 1000000;
    break;
  }
 
  switch(p[pos-1]) {
  case 'P':
    P = num;
    break;
  case 'U':
    U = num;
    break;
  case 'I':
    I = num;
    break;
  }
}

void solve(const string &p)
{
  double P, U, I;

  P = U = I = -1;
  int pos1 = p.find('=');
  int pos2 = p.find('=', pos1+1);
  
  process(P, U, I, p, pos1);
  process(P, U, I, p, pos2);
  
  if (P < 0) {
    cout << "P=" << fixed << setprecision(2) << U*I << "W" << endl;
  } else if (U < 0) {
    cout << "U=" << fixed << setprecision(2) << P/I << "V" << endl;
  } else if (I < 0) {
    cout << "I=" << fixed << setprecision(2) << P/U << "A" << endl;
  }
}

int main(void)
{
  int N;
  
  cin >> N;
  cin.ignore();

  for (int i = 1; i <= N; i++) {
    cout << "Problem #" << i << endl;
    string p;
    getline(cin, p);
    solve(p);
    cout << endl;
  }
  return 0;
}
