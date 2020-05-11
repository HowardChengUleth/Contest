#include <iostream>
#include <string>

using namespace std;

string str;

int len[1000][1000];

int solve(int s, int e)
{
  if (len[s][e] >= 0) {
    return len[s][e];
  }

  // either we don't keep the first letter, or keep it
  len[s][e] = solve(s+1, e);
  
  for (int i = e; i >= s+1; i--) {
    if (str[s] == str[i]) {
      len[s][e] = max(len[s][e], 2 + solve(s+1, i-1));
      break;
    }
  }
  return len[s][e];
}

int main(void)
{
  int N;
  cin >> N;
  getline(cin, str);
  while (N--) {
    getline(cin, str);
    int n = str.length();
    if (n == 0) {
      cout << 0 << endl;
      continue;
    }

    for (int i = 0; i < n; i++) {
      len[i][i] = 1;
      for (int j = i+1; j < n; j++) {
	len[i][j] = -1;
      }
    }
    cout << solve(0, n-1) << endl;
  }

  return 0;
}
