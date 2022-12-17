#include <bits/stdc++.h>

using namespace std;

const int ROCKS = 10000;
const int MAX_HEIGHT = 4 * ROCKS;

vector<string> chamber(MAX_HEIGHT, string(7, '.'));

typedef unsigned long long ull;

vector<string> rock[5];
string jet;
int jet_idx = 0;

ull last_line = MAX_HEIGHT;

void drop(int idx)
{
  auto piece = rock[idx % 5];
  int ph = piece.size();

  int rock_c = 2;
  ull rock_r = last_line-4-ph+1;

  while (true) {
    // jet
    int dc = (jet[jet_idx] == '<' ? -1 : 1);
    jet_idx = (jet_idx + 1) % jet.length();
    
    bool bad = false;
    for (int r = 0; r < (int)piece.size(); r++) {
      for (int c = 0; c < (int)piece[r].length(); c++) {
	if (piece[r][c] == '.') continue;
	if (!(0 <= rock_c + c + dc
	      && rock_c + c + dc < (int)chamber[rock_r+r].length())) {
	  bad = true;
	} else if (chamber[rock_r+r][rock_c+c+dc] == '#') {
	  bad = true;
	}
      }
    }

    if (!bad) {
      rock_c += dc;
    }

    // fall one unit
    bad = false;
    for (int r = 0; r < (int)piece.size(); r++) {
      for (int c = 0; c < (int)piece[r].length(); c++) {
	if (piece[r][c] == '.') continue;
	if (rock_r+r+1 >= MAX_HEIGHT) {
	  bad = true;
	} else if (chamber[rock_r+r+1][rock_c+c] == '#') {
	  bad = true;
	}
      }
    }
    if (bad) {
      last_line = min(last_line, rock_r);
      for (int r = 0; r < (int)piece.size(); r++) {
	for (int c = 0; c < (int)piece[r].length(); c++) {
	  if (piece[r][c] == '.') continue;
	  assert(chamber[rock_r+r][rock_c+c] == '.');
	  chamber[rock_r+r][rock_c+c] = '#';
	}
      }
      return;
    }
    rock_r++;
  }
}

int main()
{
  rock[0].push_back("####");

  rock[1].push_back(".#.");
  rock[1].push_back("###");
  rock[1].push_back(".#.");

  rock[2].push_back("..#");
  rock[2].push_back("..#");
  rock[2].push_back("###");

  rock[3].push_back("#");
  rock[3].push_back("#");
  rock[3].push_back("#");
  rock[3].push_back("#");

  rock[4].push_back("##");
  rock[4].push_back("##");

  cin >> jet;
  map<string,pair<ull,ull>> pattern;
  ull i = 0;
  ull total = 1000000000000ULL;
  ull adj = 0;
  while (i < total) {
    drop(i++ % 5);

    ull height = MAX_HEIGHT - last_line;
    if (height >= 50) {
      string str;
      for (int r = 0; r < 50; r++) {
	str += chamber[last_line + r];
      }
      if (pattern.find(str) == pattern.end()) {
	pattern[str] = make_pair(i, last_line);
      } else {
	ull i_diff = i - pattern[str].first;
	ull h_diff = pattern[str].second - last_line;

	ull iter = (total - i) / i_diff;
	adj += h_diff * iter;
	i += iter * i_diff;
	/*
	cout << "i_diff = " << i_diff << endl;
	cout << "h_diff = " << h_diff << endl;
	cout << "iter = " << iter << endl;
	*/
      }
    }
  }

  cout << MAX_HEIGHT - last_line + adj << endl;
  
  return 0;
}
