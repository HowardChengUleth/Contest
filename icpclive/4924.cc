#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int rot[7] = {2, 4, 4, 4, 2, 1, 2};
string piece[7][4][4] =
  { // A
    { { "####", "", "", "" },
      { "#", "#", "#", "#" } },
    // B
    { { "###", "#", "", "" },
      { "#", "#", "##", "" },
      { "  #", "###", "", "" },
      { "##", " #", " #", "" } },
    // C
    { { "###", " #", "", "" },
      { " #", "##", " #", "" },
      { " # ", "###", "", "" },
      { "#", "##", "#", "" } },
    // D
    { { "###", "  #", "", "" },
      { "##", "#", "#", "" },
      { "#", "###", "", "" },
      { " #", " #", "##", "" } },
    // E
    { { "##", " ##", "", "" },
      { " #", "##", "#", "" } },
    // F
    { { "##", "##", "", "" } },
    // G
    { { " ##", "##", "", "" },
      { "#", "##", " #", "" } }
  };

string best;

void recurse_blue(char grid[6][6], string blue, int index)
{
  if (index == 3) {
    for (int i = 0; i < 6; i++) {
      for (int j = 0; j < 6; j++) {
	if (grid[i][j] == 'R') return;
      }
    }

    string cand;
    for (int i = 0; i < 6; i++) {
      for (int j = 0; j < 6; j++) {
	cand += grid[i][j];
      }
      cand += '\n';
    }
    
    if (best == "No solution\n" ||
	cand < best) {
      best = cand;
    }
    
    return;
  }

  int pi = blue[index] - 'A';
  for (int r = 0; r < 6; r++) {
    for (int c = 0; c < 6; c++) {
      for (int p = 0; p < rot[pi]; p++) {
	// now see if we can put the piece there
	bool good = true;

	for (int rr = 0; rr < 4; rr++) {
	  for (unsigned int cc = 0; good && cc < piece[pi][p][rr].length();
	       cc++) {
	    if (r+rr >= 6 || c+cc >= 6 ||
		(piece[pi][p][rr][cc] == '#' && grid[r+rr][c+cc] != 'R')) {
	      good = false;
	    }
	  }
	}

	if (!good) continue;

	for (int rr = 0; rr < 4; rr++) {
	  for (unsigned int cc = 0; good && cc < piece[pi][p][rr].length();
	       cc++) {
	    if (piece[pi][p][rr][cc] == '#') {
	      grid[r+rr][c+cc] = '#';
	    }
	  }
	}

	recurse_blue(grid, blue, index+1);
	
	for (int rr = 0; rr < 4; rr++) {
	  for (unsigned int cc = 0; good && cc < piece[pi][p][rr].length();
	       cc++) {
	    if (piece[pi][p][rr][cc] == '#') {
	      grid[r+rr][c+cc] = 'R';
	    }
	  }
	}
      }
    }
  }
  

}


void recurse_red(char grid[6][6], string red, int index, string blue)
{
  if (index == 3) {
    recurse_blue(grid, blue, 0);
    return;
  }

  int pi = red[index] - 'A';
  for (int r = 0; r < 6; r++) {
    for (int c = 0; c < 6; c++) {
      for (int p = 0; p < rot[pi]; p++) {
	// now see if we can put the piece there
	bool good = true;

	for (int rr = 0; rr < 4; rr++) {
	  for (unsigned int cc = 0; good && cc < piece[pi][p][rr].length();
	       cc++) {
	    if (r+rr >= 6 || c+cc >= 6 ||
		(piece[pi][p][rr][cc] == '#' && grid[r+rr][c+cc] != '.')) {
	      good = false;
	    }
	  }
	}

	if (!good) continue;

	for (int rr = 0; rr < 4; rr++) {
	  for (unsigned int cc = 0; good && cc < piece[pi][p][rr].length();
	       cc++) {
	    if (piece[pi][p][rr][cc] == '#') {
	      grid[r+rr][c+cc] = 'R';
	    }
	  }
	}

	recurse_red(grid, red, index+1, blue);
	
	for (int rr = 0; rr < 4; rr++) {
	  for (unsigned int cc = 0; good && cc < piece[pi][p][rr].length();
	       cc++) {
	    if (piece[pi][p][rr][cc] == '#') {
	      grid[r+rr][c+cc] = '.';
	    }
	  }
	}
      }
    }
  }

}

void solve(string red, string blue)
{
  best = "No solution\n";

  char grid[6][6];
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 6; j++) {
      grid[i][j] = '.';
    }
  }
  recurse_red(grid, red, 0, blue);
  cout << best;
}

int main(void)
{
  int T;
  cin >> T;
  for (int i = 1; i <= T; i++) {
    cout << i << endl;
    string red, blue;
    cin >> red >> blue;
    solve(red, blue);
  }

  return 0;
}
