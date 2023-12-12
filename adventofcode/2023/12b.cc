#include <bits/stdc++.h>

using namespace std;

vector<int> parselist(string list)
{
  replace(begin(list), end(list), ',', ' ');
  istringstream iss(list);
  vector<int> v, v2;
  int x;
  while (iss >> x) {
    v.push_back(x);
  }
  for (int i = 0; i < 5; i++) {
    for (auto x : v) {
      v2.push_back(x);
    }
  }
  return v2;
}

long long memo[150][150][150];

// f(i, j, ci) = number of ways to do line[i..n-1], with
//               last j being '#' using chunks[ci..m-1]
//
// assumes last character is '.'
long long check(string line, int i, int j, const vector<int> &chunk, int ci)
{
  if (memo[i][j][ci] >= 0) {
    return memo[i][j][ci];
  }

  if (i >= (int)line.length()) {
    assert(j == 0);
    return (ci == (int)chunk.size()) ? 1 : 0;
  }

  long long &ans = memo[i][j][ci];
  ans = 0;
  if (line[i] == '.' || line[i] == '?') {
    bool good = true;
    int ci2 = ci;
    if (j > 0) {
      if (ci < (int)chunk.size() && chunk[ci] == j) {
	ci2++;
      } else {
	good = false;
      }
    }
    if (good) {
      ans += check(line, i+1, 0, chunk, ci2);
    }
  }
  if (line[i] == '#' || line[i] == '?') {
    ans += check(line, i+1, j+1, chunk, ci);
  }

  return ans;
}

string unfold(string line)
{
  string ans = line;
  for (int i = 0; i < 4; i++) {
    ans += "?";
    ans += line;
  }
  ans += ".";
  return ans;
}

long long solve(string line, string list)
{
  line = unfold(line);
  vector<int> chunk = parselist(list);

  for (int i = 0; i <= (int)line.length(); i++) {
    for (int j = 0; j <= (int)line.length(); j++) {
      for (int ci = 0; ci <= (int)chunk.size(); ci++) {
	memo[i][j][ci] = -1;
      }
    }
  }
  
  long long ans = check(line, 0, 0, chunk, 0);
  cout << line << " = " << ans << endl;
  return ans;
}

int main()
{
  long long ans = 0;
  string line, list;
  while (cin >> line >> list) {
    ans += solve(line, list);
  }
  cout << ans << endl;

  return 0;
}
