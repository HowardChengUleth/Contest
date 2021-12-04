#include <bits/stdc++.h>

using namespace std;

int n, m;
string G[100];

// number of treasures and rocks from (0,0) to (r,c)
int n_t[100][100], n_r[100][100];

void init()
{
  for (int r = 0; r < n; r++) {
    for (int c = 0; c < m; c++) {
      n_t[r][c] = (G[r][c] == '$');
      n_r[r][c] = (G[r][c] == '#');
      if (r > 0) {
	n_t[r][c] += n_t[r-1][c];
	n_r[r][c] += n_r[r-1][c];
      }
      if (c > 0) {
	n_t[r][c] += n_t[r][c-1];
	n_r[r][c] += n_r[r][c-1];
      }
      if (r > 0 && c > 0) {
	n_t[r][c] -= n_t[r-1][c-1];
	n_r[r][c] -= n_r[r-1][c-1];
      }
    }
  }
}

int count(int nn[100][100], int r1, int c1, int r2, int c2)
{
  int ans = nn[r2][c2];
  if (r1 > 0) {
    ans -= nn[r1-1][c2];
  }
  if (c1 > 0) {
    ans -= nn[r2][c1-1];
  }
  if (r1 > 0 && c1 > 0) {
    ans += nn[r1-1][c1-1];
  }
  return ans;
}

char room_label(int k)
{
  if (k < 26) {
    return 'A' + k;
  } else {
    return 'a' + (k-26);
  }
}

string room[100];

bool search(int r, int c, int room_idx = 0)
{
  if (r >= n) {
    for (int i = 0; i < n; i++) {
      cout << room[i] << endl;
    }
    return true;
  }
  if (c >= m) {
    return search(r+1, 0, room_idx);
  }
  if (!(room[r][c] == '.' || room[r][c] == '$')) {
    return search(r, c+1, room_idx);
  }

  for (int s = 1; s <= 100; s++) {
    int r2 = r + s - 1, c2 = c + s - 1;
    if (r2 >= n || c2 >= m)
      break;

    // has rock, can't continue
    if (count(n_r, r, c, r2, c2) > 0) 
      break;
    int T = count(n_t, r, c, r2, c2);
    if (T == 0) continue;
    if (T > 1) break;

    bool good = true;
    for (int i = r; i <= r2; i++) {
      for (int j = c; j <= c2; j++) {
	good &= (room[i][j] == '.' || room[i][j] == '$');
      }
    }

    if (!good) continue;
    
    for (int i = r; i <= r2; i++) {
      for (int j = c; j <= c2; j++) {
	room[i][j] = room_label(room_idx);
      }
    }

    if (search(r, c2+1, room_idx+1)) {
      return true;
    }
    
    for (int i = r; i <= r2; i++) {
      for (int j = c; j <= c2; j++) {
	room[i][j] = '.';
      }
    }
  }

  return false;
}

int main()
{
  cin >> n >> m;
  for (int i = 0; i < n; i++) {
    cin >> G[i];
  }

  init();

  for (int i = 0; i < n; i++) {
    room[i] = G[i];
  }
  if (!search(0,0)) {
    cout << "elgnatcer" << endl;
  }
  
  return 0;
}
