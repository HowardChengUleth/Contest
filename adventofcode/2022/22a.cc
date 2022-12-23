#include <bits/stdc++.h>

using namespace std;

const int dr[] = { 0, 1, 0, -1 };
const int dc[] = { 1, 0, -1, 0 };

int dirindex[256];

vector<string> G;

int main()
{
  string line;
  while (getline(cin, line) && line != "") {
    G.push_back(line);
  }

  string cmd;
  getline(cin, cmd);

  int r, c;
  int dir = 0;
  r = c = 0;
  while (c < G[0].length() && c != '.') {
    c++;
  }
  
  istringstream iss(cmd);
  while (true) {
    int steps;
    if (!(iss >> steps)) {
      break;
    }
    for (int i = 0; i < steps; i++) {
      int r2 = r + dr[dir], c2 = c + dc[dir];

      while (!(0 <= r2 && r2 < (int)G.size() && 0 <= c2 && c2 < (int)G[r2].length()
	       && G[r2][c2] != ' ')) {
	// out of bounds, adjust
	if (r2 < 0 && dir % 2 == 1) r2 = G.size()-1;
	else if (r2 >= (int)G.size() && dir % 2 == 1) r2 = 0;
	else if (c2 < 0 && dir % 2 == 0) c2 = G[r2].length()-1;
	else if (c2 >= (int)G[r2].length() && dir % 2 == 0) c2 = 0;
	else {
	  r2 += dr[dir];
	  c2 += dc[dir];
	}
      }

      if (G[r2][c2] == '#') {
	break;
      }
      
      r = r2;
      c = c2;
    }
    
    // move steps
    char dirname;
    if (!(iss >> dirname)) {
      break;
    }

    if (dirname == 'R') {
      dir = (dir+1) % 4;
    } else {
      dir = (dir+3) % 4;
    }
  }

  r++;
  c++;
  cout << "r, c, dir = " << r << ' ' << c << ' ' << dir << endl;

  int password = 1000 * r + 4 * c + dir;
  cout << password << endl;
  
  return 0;
}
