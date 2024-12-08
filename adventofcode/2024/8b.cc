#include <bits/stdc++.h>

using namespace std;

vector<string> grid;
int M, N;

void read_input()
{
  string line;

  while (getline(cin, line)) {
    grid.push_back(line);
  }
  M = grid.size();
  N = grid[0].size();
}

typedef pair<int,int> pii;
map<char, vector<pii>> antenna;

bool inside(int r, int c)
{
  return 0 <= r && r < M && 0 <= c && c < N;
}

int main()
{
  read_input();

  for (int r = 0; r < M; r++) {
    for (int c = 0; c < N; c++) {
      char ch = grid[r][c];
      if (isalnum(ch)) {
	antenna[ch].emplace_back(r, c);
      }
    }
  }

  set<pii> antinode;
  for (const auto &[ch, v] : antenna) {
    int n = v.size();
    for (int i = 0; i < n; i++) {
      for (int j = i+1; j < n; j++) {
	auto [ir, ic] = v[i];
	auto [jr, jc] = v[j];
	int dr = jr - ir, dc = jc - ic;

	int r = ir, c = ic;
	while (inside(r, c)) {
	  antinode.emplace(r, c);
	  r -= dr;
	  c -= dc;
	}

	r = ir; c = ic;
	while (inside(r, c)) {
	  antinode.emplace(r, c);
	  r += dr;
	  c += dc;
	}
      }
    }
  }

  cout << antinode.size() << endl;
  
  return 0;
}
