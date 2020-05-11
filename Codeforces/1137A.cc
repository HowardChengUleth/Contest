#include <bits/stdc++.h>

using namespace std;

int m, n;
int A[1000][1000];

vector<int> rows[1000], cols[1000];

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n >> m;
  for (int r = 0; r < n; r++) {
    rows[r].reserve(m);
  }
  for (int c = 0; c < m; c++) {
    cols[c].reserve(n);
  }

  for (int r = 0; r < n; r++) {
    for (int c = 0; c < m; c++) {
      cin >> A[r][c];
      rows[r].push_back(A[r][c]);
      cols[c].push_back(A[r][c]);
    }
  }
  for (int r = 0; r < n; r++) {
    sort(begin(rows[r]), end(rows[r]));
    rows[r].resize(unique(begin(rows[r]), end(rows[r])) - begin(rows[r]));
  }
  for (int c = 0; c < m; c++) {
    sort(begin(cols[c]), end(cols[c]));
    cols[c].resize(unique(begin(cols[c]), end(cols[c])) - begin(cols[c]));
  }
    
  for (int r = 0; r < n; r++) {
    for (int c = 0; c < m; c++) {
      int ri = lower_bound(begin(rows[r]), end(rows[r]), A[r][c])
	- begin(rows[r]);
      int rsize = rows[r].size();
      int ci = lower_bound(begin(cols[c]), end(cols[c]), A[r][c])
	- begin(cols[c]);
      int csize = cols[c].size();

      int label = max(ri, ci);
      cout << label + max(rsize-ri, csize-ci) << ' ';
    }
    cout << endl;
  }
  
  return 0;
}
