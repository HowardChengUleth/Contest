#include <bits/stdc++.h>

using namespace std;

vector<string> A;
int m, n;

bool issymbol(char c)
{
  return !isdigit(c) && c != '.';
}

bool inside(int r, int c)
{
  return 0 <= r && r < m && 0 <= c && c < n;
}

int getnum(int r, int c)
{
  int ans = 0;
  int len = 0;
  while (c+len < n && isdigit(A[r][c+len])) {
    ans = ans*10 + A[r][c+len] - '0';
    len++;
  }

  for (int r2 = r-1; r2 <= r+1; r2++) {
    for (int c2 = c-1; c2 <= c+len; c2++) {
      if (inside(r2, c2) && issymbol(A[r2][c2])) {
	return ans;
      }
    }
  }

  return 0;
}

int main()
{
  string str;
  while (getline(cin, str)) {
    A.push_back(str);
  }

  m = A.size();
  n = A[0].size();

  int ans = 0;
  for (int r = 0; r < m; r++) {
    for (int c = 0; c < n; c++) {
      if (!isdigit(A[r][c])) continue;
      if (c > 0 && isdigit(A[r][c-1])) continue;
      int num = getnum(r, c);
      ans += num;
    }
  }
  cout << ans << endl;
  return 0;
}
