#include <iostream>
#include <iomanip>

using namespace std;

void print_head()
{
  cout << "------+---------" << endl;
  cout << " time | elapsed" << endl;
  cout << "------+---------" << endl;
}

void print_line(int hour, int adj)
{
  while (hour >= 13) hour -= 12;
  cout << setw(2) << hour << ":XX | XX";
  if (adj > 0) {
    cout << " + " << adj;
  } else if (adj < 0) {
    cout << " - " << -adj;
  }
  cout << endl;
}

void solve()
{
  int SH, SM, DH, DM;
  cin >> SH >> SM >> DH >> DM;
  int S = SH * 60 + SM;
  int D = DH * 60 + DM;
  const int MAX_D = 10*60 + 59;

  print_head();
  int T = SH*60;
  while (T - S <= D) {
    print_line(T / 60, T - S);
    T += 60;
  }
}

int main(void)
{
  int N;
  cin >> N;
  while (N--) {
    solve();
  }
  return 0;
}
