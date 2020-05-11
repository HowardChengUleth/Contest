#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int area(string grid[100], int n, int r, int c, bool visited[100][100])
{
  const int dr[] = { -1, 1,  0, 0, -1, -1, 1, 1};
  const int dc[] = {  0, 0, -1, 1, -1,  1, -1, 1};

  if (grid[r][c] != 'W') return 0;
  visited[r][c] = true;

  int A = 1;

  for (int d = 0; d < 8; d++) {
    int nr = r + dr[d], nc = c + dc[d];
    if ((0 <= nr && nr < n && 0 <= nc && nc < grid[nr].length()) &&
	!visited[nr][nc]) {
      A += area(grid, n, nr, nc, visited);
    }
  }

  return A;
}

void solve()
{
  string grid[100];
  int n = 0;

  string s;
  while (getline(cin, s) && (s[0] == 'L' || s[0] == 'W')) {
    grid[n++] = s;
  }

  while (s != "" && cin) {
    istringstream iss(s);
    int r, c;
    iss >> r >> c;
    
    bool visited[100][100];
    for (int i = 0; i < n; i++) {
      fill(visited[i], visited[i]+100, false);
    }

    cout << area(grid, n, r-1, c-1, visited) << endl;

    getline(cin, s);
  }

}

int main()
{
  int n;
  cin >> n;
  cin.ignore(1);
  cin.ignore(1);
  
  while (n--) {
    solve();
    if (n) cout << endl;
  }

  return 0;
}
