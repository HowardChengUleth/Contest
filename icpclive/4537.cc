#include <iostream>
#include <algorithm>
#include <set>
#include <vector>

using namespace std;

int grid[100][100];
int grid2[100][100];
int n, m;

void flood(int r, int c, int h, int grid2[100][100], int val)
{
  if (r < 0 || c < 0 || r >= n || c >= m || grid[r][c] > h || 
      grid2[r][c] == val) {
    return;
  }
  grid2[r][c] = val;
  flood(r-1, c, h, grid2, val);
  flood(r+1, c, h, grid2, val);
  flood(r, c-1, h, grid2, val);
  flood(r, c+1, h, grid2, val);
}

void flood2(int r, int c, int grid2[100][100], int val)
{
  if (r < 0 || c < 0 || r >= n || c >= m || grid2[r][c] != 0) {
    return;
  }
  grid2[r][c] = val;
  flood2(r-1, c, grid2, val);
  flood2(r+1, c, grid2, val);
  flood2(r, c-1, grid2, val);
  flood2(r, c+1, grid2, val);
}

bool do_case(int case_num)
{
  cin >> n >> m;
  if (n == 0 && m == 0) return false;
  
  set<int> heights;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> grid[i][j];
      heights.insert(grid[i][j]);
    }
  }

  int split = -1;
  for (set<int>::iterator it = heights.begin(); it != heights.end(); ++it) {
    int h = *it;

    for (int i = 0; i < n; i++) {
      fill(grid2[i], grid2[i]+m, 0);
    }

    // flood from outside
    for (int i = 0; i < n; i++) {
      flood(i, 0, h, grid2, -1);
      flood(i, m-1, h, grid2, -1);
    }
    for (int j = 0; j < m; j++) {
      flood(0, j, h, grid2, -1);
      flood(n-1, j, h, grid2, -1);
    }

    // now find connected regions
    int count = 0;
    for (int i = 0; i < n && count < 2; i++) {
      for (int j = 0; j < m && count < 2; j++) {
	if (grid2[i][j] == -1) continue;
	if (grid2[i][j] > 0) continue;
	if (count == 1) {
	  count++;
	} else {
	  flood2(i, j, grid2, ++count);
	}
      }
    }
    if (count > 1) {
      split = h;
      break;
    }
  }



  cout << "Case " << case_num << ": ";
  if (split > 0) {
    cout << "Island splits when ocean rises " << split << " feet." << endl;
  } else {
    cout << "Island never splits." << endl;
  }
  return true;
}

int main(void)
{
  int case_num = 1;
  while (do_case(case_num++))
    ;
  return 0;
}
