#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <cctype>

using namespace std;

char grid[8][8];

bool inrange(int i, int j)
{
  return 0 <= i && i < 8 && 0 <= j && j < 8;
}

void mark_line(int i, int j, int dr, int dc, int n = 1)
{
  int steps = 1;
  i += dr;
  j += dc;
  while (steps <= n && inrange(i, j) &&
	 (grid[i][j] == ' ' || grid[i][j] == 'X')) {
    grid[i][j] = 'X';
    i += dr;
    j += dc;
    steps++;
  }
}

int main()
{
  string s;
  while (cin >> s) {
    replace(s.begin(), s.end(), '/', ' ');
    istringstream iss(s);
    for (int i = 0; i < 8; i++) {
      fill(grid[i], grid[i]+8, ' ');
      int j = 0;
      string line;
      iss >> line;
      for (unsigned int k = 0; k < line.length(); k++) {
	if (isdigit(line[k])) {
	  j += line[k] - '0';
	} else {
	  grid[i][j++] = line[k];
	}
      }
    }

    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
	if (tolower(grid[i][j]) == 'k') {
	  // king
	  for (int dr = -1; dr <= 1; dr++) {
	    for (int dc = -1; dc <= 1; dc++) {
	      if (dr || dc) {
		mark_line(i, j, dr, dc);
	      }
	    }
	  }
	} else if (tolower(grid[i][j]) == 'q') {
	  // queen
	  for (int dr = -1; dr <= 1; dr++) {
	    for (int dc = -1; dc <= 1; dc++) {
	      if (dr || dc) {
		mark_line(i, j, dr, dc, 8);
	      }
	    }
	  }
	} else if (tolower(grid[i][j]) == 'b') {
	  // bishop
	  mark_line(i, j, -1, -1, 8);
	  mark_line(i, j, -1,  1, 8);
	  mark_line(i, j,  1, -1, 8);
	  mark_line(i, j,  1,  1, 8);
	} else if (tolower(grid[i][j]) == 'r') {
	  // rook
	  mark_line(i, j,  0,  1, 8);
	  mark_line(i, j,  0, -1, 8);
	  mark_line(i, j,  1,  0, 8);
	  mark_line(i, j, -1,  0, 8);
	} else if (tolower(grid[i][j]) == 'n') {
	  // knight
	  mark_line(i, j, -2, -1);
	  mark_line(i, j, -2,  1);
	  mark_line(i, j,  2, -1);
	  mark_line(i, j,  2,  1);
	  mark_line(i, j, -1, -2);
	  mark_line(i, j, -1,  2);
	  mark_line(i, j,  1, -2);
	  mark_line(i, j,  1,  2);
	} else if (grid[i][j] == 'P') {
	  // white pawn
	  mark_line(i, j, -1, -1);
	  mark_line(i, j, -1,  1);
	} else if (grid[i][j] == 'p') {
	  // black pawn
	  mark_line(i, j,  1, -1);
	  mark_line(i, j,  1,  1);
	}
      }
    }

    int count = 0;
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
	if (grid[i][j] == ' ') count++;
      }
    }
    cout << count << endl;
  }

  return 0;
}
