#include <iostream>
#include <algorithm>

using namespace std;

int ind(int i, int j)
{
  return i*8+j;
}

const int dr[8] = { -2, -2, -1, -1,  1, 1 , 2, 2 };
const int dc[8] = { -1,  1, -2,  2, -2, 2, -1, 1 };

void solve()
{
  int m;
  cin >> m;

  char board[8][8];
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      cin >> board[i][j];
    }
  }

  int dist[64][64];
  for (int i = 0; i < 64; i++) {
    fill(dist[i], dist[i]+64, 1000);
  }

  int pawns[8];
  int num_pawns = 0;
  int knight;
  
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if (board[i][j] == 'k') {
	knight = ind(i, j);
      } else if (board[i][j] == 'P') {
	pawns[num_pawns++] = ind(i, j);
      }
      
      if (board[i][j] == 'K' || board[i][j] == 'p') continue;
      for (int k = 0; k < 8; k++) {
	int i2 = i + dr[k], j2 = j + dc[k];
	if (!(0 <= i2 && i2 < 8 && 0 <= j2 && j2 < 8)) continue;
	if (board[i2][j2] == 'K' || board[i2][j2] == 'p') continue;
	dist[ind(i,j)][ind(i2,j2)] = 1;
      }
    }
  }

  for (int k = 0; k < 64; k++) {
    for (int i = 0; i < 64; i++) {
      for (int j = 0; j < 64; j++) {
	dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
      }
    }
  }
  
  int perm[8];
  for (int i = 0; i < num_pawns; i++) {
    perm[i] = i;
  }

  int best = 10000000;
  do {
    int total = 0;
    for (int i = 0; i < num_pawns; i++) {
      total += dist[(i > 0) ? pawns[perm[i-1]] : knight][pawns[perm[i]]];
    }
    best = min(best, total);
  } while (next_permutation(perm, perm+num_pawns));

  if (best <= m) {
    cout << "Yes" << endl;
  } else {
    cout << "No" << endl;
  }

}

int main(void)
{
  int T;
  cin >> T;
  while (T--) 
    solve();
  return 0;
}
    
