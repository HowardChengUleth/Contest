#include <bits/stdc++.h>

using namespace std;

int get_total()
{
  int total = 0;

  string line;
  while (getline(cin, line) && line != "") {
    total += stoi(line);
  }
  return total;
}

int main()
{
  int best = 0;

  int total;
  while ((total = get_total()) > 0) {
    best = max(best, total);
  }
  cout << best << endl;

  
  return 0;
}
