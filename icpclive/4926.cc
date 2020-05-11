#include <iostream>

using namespace std;

void doit(int sr, int sc, int W, int T, char orig[64][64], char ans[64][64])
{
  if (W == 1) {
    ans[sr][sc] = orig[sr][sc];
    return;
  }

  int count0 = 0;
  for (int i = 0; i < W; i++) {
    for (int j = 0; j < W; j++) {
      if (orig[sr+i][sc+j] == '0') {
	count0++;
      }
    }
  }
  int count1 = W*W - count0;

  if (count0 * 100 >= T*W*W) {
    for (int i = 0; i < W; i++) {
      for (int j = 0; j < W; j++) {
	ans[sr+i][sc+j] = '0';
      }
    }
    return;
  }

  if (count1 * 100 >= T*W*W) {
    for (int i = 0; i < W; i++) {
      for (int j = 0; j < W; j++) {
	ans[sr+i][sc+j] = '1';
      }
    }
    return;
  }

  doit(sr, sc, W/2, T, orig, ans);
  doit(sr+W/2, sc, W/2, T, orig, ans);
  doit(sr, sc+W/2, W/2, T, orig, ans);
  doit(sr+W/2, sc+W/2, W/2, T, orig, ans);
  
}

bool solve(int id)
{
  int W, T;
  cin >> W;
  if (!W) return false;
  cin >> T;

  cout << "Image " << id << ":" << endl;

  char orig[64][64], ans[64][64];

  for (int i = 0; i < W; i++) {
    for (int j = 0; j < W; j++) {
      cin >> orig[i][j];
    }
  }

  doit(0, 0, W, T, orig, ans);
  
  for (int i = 0; i < W; i++) {
    for (int j = 0; j < W; j++) {
      cout << ans[i][j];
    }
    cout << endl;
  }
  
  return true;
}

int main(void)
{
  int im_no = 1;
  while (solve(im_no++))
    ;
  
  return 0;
}
