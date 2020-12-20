// this only works because the data is such that each border can match
// at most one other border...

#include <bits/stdc++.h>

using namespace std;

struct Tile
{
  vector<string> A;
  int id;
  int n;
  int sig[4];     // 0 = top, 1 = left, 2 = bot, 3 = right
  int sigA[4], sigB[4];
  
  void read()
  {
    string s;

    n = 0;
    while (getline(cin, s) && s != "") {
      A.push_back(s);
      n++;
    }

    assert(n == (int)A[0].length() && n == 10);
    comp_sig();
  }

  void comp_sig()
  {
    comp_sig(0, 0, 0, 0, 1);
    comp_sig(1, 0, 0, 1, 0);
    comp_sig(2, 9, 0, 0, 1);
    comp_sig(3, 0, 9, 1, 0);	
  }
  
  void comp_sig(int index, int r, int c, int dr, int dc)
  {
    int b[10];
    for (int i = 0; i < 10; i++) {
      b[i] = A[r][c] == '#';
      r += dr;
      c += dc;
    }

    int sig1 = 0, sig2 = 0;
    for (int i = 0; i < 10; i++) {
      sig1 = sig1*2 + b[i];
      sig2 = sig2*2 + b[9-i];
    }
    sigA[index] = sig1;
    sigB[index] = sig2;
    sig[index] = min(sig1, sig2);
  }

  void rotate()
  {
    vector<string> B = A;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
	A[i][j] = B[j][n-1-i];
      }
    }
    comp_sig();
  }

  void flipV()
  {
    reverse(begin(A), end(A));
    comp_sig();
  }
  
  void flipH()
  {
    for (auto &s : A) {
      reverse(begin(s), end(s));
    }
    comp_sig();
  }
  
  void print() const
  {
    cout << "id = " << id << endl;
    for (auto s : A) {
      cout << s << endl;
    }
  }
};

vector<Tile> tile;
int piece[100][100];
int piece_i[100][100];

char grid[1200][1200];

int sig_freq[1024];
int corner;

void solveA()
{
  for (auto t : tile) {
    for (int i = 0; i < 4; i++) {
      sig_freq[t.sig[i]]++;
    }
  }

  long long ansA = 1;
  for (auto t : tile) {
    int count1 = 0;
    for (int i = 0; i < 4; i++) {
      if (sig_freq[t.sig[i]] == 1) {
	count1++;
      }
    }
    if (count1 == 2) {
      ansA *= t.id;
      corner = t.id;
    }
  }
  cout << "A = " << ansA << endl;
}


void flipV(char dragon[20][21], int m, int n)
{
  for (int c = 0; c < n; c++) {
    for (int r = 0; r < m-1-r; r++) {
      swap(dragon[r][c], dragon[m-1-r][c]);
    }
  }
}

void flipH(char dragon[20][21], int m, int n)
{
  for (int r = 0; r < m; r++) {
    for (int c = 0; c < n-1-c; c++) {
      swap(dragon[r][c], dragon[r][n-1-c]);
    }
  }
}

void mark_dragon(char grid[8*12][8*12], bool mark[8*12][8*12], int M,
		 char dragon[20][21], int m, int n)
{
  for (int dr = 0; dr < M; dr++) {
    for (int dc = 0; dc < M; dc++) {
      if (dr + m - 1 >= M || dc + n - 1 >= M) continue;
      bool match = true;
      for (int r = 0; r < m; r++) {
	for (int c = 0; c < n; c++) {
	  match &= (dragon[r][c] != '#' || grid[dr+r][dc+c] == '#');
	}
      }
      if (!match) continue;
      for (int r = 0; r < m; r++) {
	for (int c = 0; c < n; c++) {
	  if (dragon[r][c] == '#') {
	    mark[dr+r][dc+c] = true;
	  }
	}
      }
    }
  }

}



void solveB()
{
  int n = (tile.size() == 9) ? 3 : 12;
  int piece[12][12];
  
  // find the corner piece
  for (int i = 0; i < (int)tile.size(); i++) {
    if (tile[i].id == corner) {
      while (!(sig_freq[tile[i].sig[0]] == 1 &&
	       sig_freq[tile[i].sig[1]] == 1)) {
	tile[i].rotate();
      }
      piece[0][0] = i;
      break;
    }
  }

  // get first row
  for (int c = 1; c < n; c++) {
    auto &left = tile[piece[0][c-1]];
    for (int i = 0; i < (int)tile.size(); i++) {
      if (i == piece[0][c-1]) continue;
      auto &right = tile[i];
      
      for (int i = 0; i < 4 && right.sig[1] != left.sig[3]; i++) {
	right.rotate();
      }
      if (right.sig[1] == left.sig[3]) {
	if (left.sigA[3] == right.sigB[1]) {
	  right.flipV();
	}
	piece[0][c] = i;
	break;
      }
    }
  }

  for (int r = 1; r < n; r++) {
    for (int c = 0; c < n; c++) {
      auto &top = tile[piece[r-1][c]];
      for (int i = 0; i < (int)tile.size(); i++) {
	if (i == piece[r-1][c]) continue;
	auto &bot = tile[i];

	for (int i = 0; i < 4 && top.sig[2] != bot.sig[0]; i++) {
	  bot.rotate();
	}
	if (top.sig[2] == bot.sig[0]) {
	  if (top.sigA[2] == bot.sigB[0]) {
	    bot.flipH();
	  }
	  piece[r][c] = i;
	  break;
	}
      }
    }
  }

  for (int r = 0; r < n; r++) {
    for (int c = 0; c < n; c++) {
      cout << tile[piece[r][c]].id << ' ';
    }
    cout << endl;
  }

  char grid[8*12][8*12];
  for (int rb = 0; rb < n; rb++) {
    for (int cb = 0; cb < n; cb++) {
      const auto &t = tile[piece[rb][cb]];
      for (int r = 0; r < 8; r++) {
	for (int c = 0; c < 8; c++) {
	  grid[rb*8+r][cb*8+c] = t.A[r+1][c+1];
	}
      }
    }
  }

  char dragon1[20][21] = { "                  # ",
			 "#    ##    ##    ###",
			 " #  #  #  #  #  #   " };
  char dragon2[20][21];
  for (int r = 0; r < 20; r++) {
    for (int c = 0; c < 3; c++) {
      dragon2[r][c] = dragon1[c][r];
    }
  }

  bool mark[8*12][8*12] = { false };

  mark_dragon(grid, mark, n*8, dragon1, 3, 20);
  mark_dragon(grid, mark, n*8, dragon2, 20, 3);
  flipV(dragon1, 3, 20);
  flipV(dragon2, 20, 3);
  mark_dragon(grid, mark, n*8, dragon1, 3, 20);
  mark_dragon(grid, mark, n*8, dragon2, 20, 3);
  flipH(dragon1, 3, 20);
  flipH(dragon2, 20, 3);
  mark_dragon(grid, mark, n*8, dragon1, 3, 20);
  mark_dragon(grid, mark, n*8, dragon2, 20, 3);
  flipV(dragon1, 3, 20);
  flipV(dragon2, 20, 3);
  mark_dragon(grid, mark, n*8, dragon1, 3, 20);
  mark_dragon(grid, mark, n*8, dragon2, 20, 3);

  int count = 0;
  for (int r = 0; r < n*8; r++) {
    for (int c = 0; c < n*8; c++) {
      if (grid[r][c] == '#' && !mark[r][c]) {
	count++;
      }
    }
  }
  cout << "B = " << count << endl;
}

int main()
{
  string s;
  int id;
  while (cin >> s >> id >> s) {
    getline(cin, s);

    Tile t;
    t.id = id;
    t.read();
    tile.push_back(t);
  }

  solveA();
  solveB();
  
  
  
  return 0;

}
