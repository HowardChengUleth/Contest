#include <bits/stdc++.h>

using namespace std;

int main()
{
  int N;
  map<string, int> freq;

  cin >> N;
  for (int i = 0; i < N; i++) {
    string s;
    cin >> s;
    freq[s]++;
  }

  int smallest = N+1;
  for (auto [s, f] : freq) {
    smallest = min(smallest, f);
  }

  for (auto [s, f] : freq) {
    if (f == smallest) {
      cout << s << endl;
    }
  }

  
    
  return 0;
}
