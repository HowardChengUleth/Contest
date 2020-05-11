#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

void do_case()
{
  int K;
  cin >> K;
  cin.ignore(1);

  long long cost[256];
  fill(cost, cost+256, 0);

  for (int i = 0; i < K; i++) {
    unsigned char ch = cin.get();
    cin >> cost[ch];
    cin.ignore(1);
  }

  int M;
  cin >> M;
  cin.ignore(1);

  long long total = 0;
  while (M > 0) {
    unsigned char ch = cin.get();
    if (ch == '\n') {
      M--;
    } else {
      total += cost[ch];
    }
  }

  cout << total / 100 << '.' << setw(2) << setfill('0') << total % 100
       << '$' << endl;
}

int main(void)
{
  int N;
  cin >> N;
  while (N-- > 0) {
    do_case();
  }
  return 0;
}
