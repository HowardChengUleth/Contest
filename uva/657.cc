#include <iostream>
#include <algorithm>

using namespace std;

const int dr[] = { -1, 1, 0, 0 };
const int dc[] = { 0, 0, -1, 1 };

char A[50][50];
int w, h;

void filldice(int i, int j, int diceid[50][50], int id)
{
  diceid[i][j] = id;

  for (int d = 0; d < 4; d++) {
    int ii = i + dr[d], jj = j + dc[d];
    if (!(0 <= ii && ii < h && 0 <= jj && jj < w)) continue;
    if (A[ii][jj] == '.' || diceid[ii][jj] >= 0) continue;
    filldice(ii, jj, diceid, id);
  }
}

void fillX(int i, int j, bool marked[50][50])
{
  marked[i][j] = true;
  for (int d = 0; d < 4; d++) {
    int ii = i + dr[d], jj = j + dc[d];
    if (!(0 <= ii && ii < h && 0 <= jj && jj < w)) continue;
    if (A[ii][jj] != 'X' || marked[ii][jj]) continue;
    fillX(ii, jj, marked);
  }
}

bool solve(int id)
{
  cin >> w >> h;
  if (!w && !h) return false;

  cout << "Throw " << id << endl;
  
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      cin >> A[i][j];
    }
  }

  int diceid[50][50];
  int numdice = 0;

  for (int i = 0; i < h; i++) {
    fill(diceid[i], diceid[i]+w, -1);
  }
  
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      if (diceid[i][j] < 0 && A[i][j] != '.') {
	filldice(i, j, diceid, numdice++);
      }
    }
  }

  int dice[2500] = { 0 };
  bool marked[50][50];
  for (int i = 0; i < h; i++) {
    fill(marked[i], marked[i]+w, false);
  }

  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      if (A[i][j] == 'X' && !marked[i][j]) {
	fillX(i, j, marked);
	dice[diceid[i][j]]++;
      }
    }
  }

  sort(dice, dice+numdice);
  for (int i = 0; i < numdice; i++) {
    if (i) cout << ' ';
    cout << dice[i];
  }
  cout << endl;
  cout << endl;
  return true;
}

int main()
{
  int id = 1;

  while (solve(id++))
    ;
  return 0;
}
  
