#include <bits/stdc++.h>

using namespace std;

char A[300][300];

const int dr[] = { -1, 1, 0, 0 };
const int dc[] = { 0, 0, -1, 1 };

typedef pair<int,int> pii;

void do_step(int dir)
{
  map<pii, vector<pii>> dest;
  
  for (int r = 0; r < 300; r++) {
    for (int c = 0; c < 300; c++) {
      if (A[r][c] == '.') continue;
      assert(r > 0 && r < 299 && c > 0 && c < 299);

      // don't move if there are no elfs around
      int elf = 0;
      for (int dr2 = -1; dr2 <= 1; dr2++) {
	for (int dc2 = -1; dc2 <= 1; dc2++) {
	  if (dr2 || dc2) {
	    elf += (A[r + dr2][c + dc2] == '#');
	  }
	}
      }
      if (!elf) continue;

      for (int dd = 0; dd < 4; dd++) {
	int dir2 = (dir + dd) % 4;
      
        elf = 0;
	for (int dr2 = -1; dr2 <= 1; dr2++) {
	  for (int dc2 = -1; dc2 <= 1; dc2++) {
	    if ((dr[dir2] && dr2 == dr[dir2]) ||
		(dc[dir2] && dc2 == dc[dir2])) {
	      elf += (A[r + dr2][c + dc2] == '#');
	    }
	  }
	}

	if (!elf) {
	  int r2 = r + dr[dir2], c2 = c + dc[dir2];
	  dest[pii(r2, c2)].emplace_back(r, c);
	  //	  cout << "moving " << r << ", " << c << " to " << r2 << ", " << c2 << endl;
	  break;
	}
      }
    }
  }

  for (auto [ to, from ] : dest) {
    auto [r2, c2] = to;
    if (from.size() == 1) {
      auto [r, c] = from[0];
      A[r][c] = '.';
      A[r2][c2] = '#';
    }
  }
}


int main()
{
  for (int r = 0; r < 300; r++) {
    for (int c = 0; c < 300; c++) {
      A[r][c] = '.';
    }
  }

  string line;
  int r = 0;
  while (getline(cin, line)) {
    for (int c = 0; c < (int)line.length(); c++) {
      A[r+100][c+100] = line[c];
    }
    r++;
  }

  for (int i = 0; i < 10; i++) {
    do_step(i % 4);
  }

  int min_r = 1000, min_c = 1000, max_r = -1, max_c = -1;
  int elf = 0;
  for (int r = 0; r < 300; r++) {
    for (int c = 0; c < 300; c++) {
      if (A[r][c] == '.') continue;
      elf++;
      min_r = min(r, min_r);
      max_r = max(r, max_r);
      min_c = min(c, min_c);
      max_c = max(c, max_c);
    }
  }

  int ans = (max_c - min_c + 1) * (max_r - min_r + 1) - elf;
  cout << ans << endl;

  return 0;
}
