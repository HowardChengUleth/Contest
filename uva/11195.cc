#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

bool diag[27], antidiag[27];

int count(int perm[], int start, int n, string grid[])
{
  int ans = 0;

  if (start == n) {
    return 1;
  }
  
  for (int i = start; i < n; i++) {
    swap(perm[start], perm[i]);
    bool good = (grid[start][perm[start]] == '.');

    int d = start - perm[start] + n;
    int ad = start + perm[start];
    good &= !diag[d] && !antidiag[ad];

    if (good) {
      diag[d] = antidiag[ad] = true;
      ans += count(perm, start+1, n, grid);
      diag[d] = antidiag[ad] = false;
    }
    swap(perm[start], perm[i]);
  }
  
  return ans;
}

bool solve(int id)
{
  int n;
  cin >> n;
  if (n == 0) return false;

  string grid[14];

  for (int i = 0; i < n; i++) {
    cin >> grid[i];
  }

  int perm[14];
  for (int i = 0; i < n; i++) {
    perm[i] = i;
  }
  fill(diag, diag+2*n-1, false);
  fill(antidiag, antidiag+2*n-1, false);
  int ans = count(perm, 0, n, grid);
  
  cout << "Case " << id << ": " << ans << endl;
  
  return true;
}

int main(void)
{
  int id = 1;
  while (solve(id++))
    ;

  return 0;
}
