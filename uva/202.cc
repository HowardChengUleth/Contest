#include <iostream>
#include <map>
#include <string>

using namespace std;

void solve(int N, int D)
{
  cout << N << '/' << D << " = " << N/D << '.';

  map<int,int> dividend;
  int pos = 0;
  string decimals;

  N = (N % D)*10;
  do {
    dividend[N] = pos;
    char next = (char)(N/D) + '0';
    decimals += next;
    N = (N % D)*10;
    pos++;
  } while (dividend.find(N) == dividend.end());

  int cycle_len = pos - dividend[N];
  if (decimals.length() > 50) {
    decimals = decimals.substr(0, 50) + "...";
  }
  cout << decimals.substr(0, dividend[N]);
  decimals.erase(0, dividend[N]);
  cout << '(' << decimals << ')' << endl;

  cout << "   " << cycle_len << " = number of digits in repeating cycle"
       << endl;

}

int main(void)
{
  int N, D;

  while (cin >> N >> D) {
    solve(N, D);
    cout << endl;
  }
  return 0;
}
