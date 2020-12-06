#include <bits/stdc++.h>

using namespace std;

int decode(string s)
{
  int r = 0;
  for (auto c : s) {
    r *= 2;
    if (c == 'B' || c == 'R') {
      r++;
    }
  }
  return r;
}

int main()
{
  int ansA = 0;
  vector<int> seats;
  
  string line;
  while (cin >> line) {
    int id = decode(line);
    ansA = max(ansA, id);
    seats.push_back(id);
  }

  cout << "A = " << ansA << endl;
  sort(begin(seats), end(seats));
  for (int i = 1; i < seats.size(); i++) {
    if (seats[i] == seats[i-1]+2) {
      cout << "B = " << seats[i]-1 << endl;
      break;
    }
  }

  return 0;
}
