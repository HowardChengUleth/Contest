#include <bits/stdc++.h>

using namespace std;

string entry[20];

bool check(string entry, string cand)
{
  int curr = 0;
  for (auto ch : cand) {
    auto pos = entry.find(ch, curr);
    if (pos == string::npos) {
      return false;
    }
    curr = pos+1;
  }
  return true;
}

int main()
{
  int K, N;
  cin >> K >> N;

  for (int i = 0; i < N; i++) {
    cin >> entry[i];
  }

  vector<string> soln;
  for (int i = 0; i < 1000000; i++) {
    ostringstream oss;
    oss << setw(K) << setfill('0') << i;
    if (oss.str().length() > K)
      break;
    bool good = true;
    for (int j = 0; j < N; j++) {
      good &= check(entry[j], oss.str());
    }
    if (good) {
      soln.push_back(oss.str());
    }
  }

  cout << soln.size() << endl;
  for (auto s : soln) {
    cout << s << endl;
  }
  
  return 0;
}
