#include <bits/stdc++.h>

using namespace std;

vector<int> parselist(string list)
{
  replace(begin(list), end(list), ',', ' ');
  istringstream iss(list);
  vector<int> v;
  int x;
  while (iss >> x) {
    v.push_back(x);
  }
  return v;
}

long long check(string line, int i, const vector<int> &chunk)
{
  if (i >= (int)line.length()) {
    //    cout << "base line = " << line << endl;
    int cindex = 0;
    for (int k = 0; k < (int)line.length();) {
      if (line[k] != '#') {
	k++;
	continue;
      }
      int t;
      for (t = 1; k+t < (int)line.length() && line[k+t] == '#'; t++) 
	;
      //      cout << t << ' ';
      if (!(cindex < (int)chunk.size() && chunk[cindex] == t)) {
	return 0;
      }
      cindex++;
      k += t;
    }
    //    cout << endl;
    return cindex == (int)chunk.size();
  }
  if (line[i] != '?') {
    return check(line, i+1, chunk);
  }
  long long ans = 0;
  line[i] = '.';
  ans += check(line, i+1, chunk);
  line[i] = '#';
  ans += check(line, i+1, chunk);
  line[i] = '?';
  return ans;
}

long long solve(string line, string list)
{
  vector<int> chunk = parselist(list);
  long long ans = check(line, 0, chunk);
  cout << line << ": " << ans << endl;
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
