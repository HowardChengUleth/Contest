#include <iostream>
#include <string>

using namespace std;

class Terminal {
private:
  char screen[10][10];
  bool overwrite;
  int row, col;

public:
  Terminal() 
    : overwrite(true), row(0), col(0)
  {
    clear();
  }

  void clear()
  {
    for (int r = 0; r < 10; r++) {
      for (int c = 0; c < 10; c++) {
	screen[r][c] = ' ';
      }
    }
  }

  void parse(const string &line)
  {
    unsigned int i = 0;

    while (i < line.length()) {
      if (line[i] != '^') {
	// normal character
	put(line[i++]);
      } else {
	i++;
	switch (line[i]) {
	case 'b':
	  col = 0;
	  break;
	case 'c':
	  clear();
	  break;
	case 'd':
	  if (row < 9) row++;
	  break;
	case 'e':
	  for (int c = col; c+1 < 10; c++) {
	    screen[row][c] = screen[row][c+1];
	  }
	  screen[row][9] = ' ';
	  break;
	case 'h':
	  row = col = 0;
	  break;
	case 'i':
	  overwrite = false;
	  break;
	case 'l':
	  if (col > 0) col--;
	  break;
	case 'o':
	  overwrite = true;
	  break;
	case 'r':
	  if (col < 9) col++;
	  break;
	case 'u':
	  if (row > 0) row--;
	  break;
	case '^':
	  put('^');
	  break;
	default:
	  row = line[i++] - '0';
	  col = line[i] - '0';
	}	    
	i++;
      }
    }
  }

  void put(char ch) 
  {
    if (overwrite) {
      screen[row][col] = ch;
    } else {
      for (int c = 9; c >= col+1; c--) {
	screen[row][c] = screen[row][c-1];
      }
      screen[row][col] = ch;
    }
    if (col < 9) col++;
  }

  void write() const
  {
    cout << '+';
    for (int c = 0; c < 10; c++) {
      cout << '-';
    }
    cout << '+' << endl;

    for (int r = 0; r < 10; r++) {
      cout << '|';
      for (int c = 0; c < 10; c++) {
	cout << screen[r][c];
      }
      cout << '|' << endl;
    }

    cout << '+';
    for (int r = 0; r < 10; r++) {
      cout << '-';
    }
    cout << '+' << endl;
  }
  
};


int main(void)
{
  int n;
  int case_num = 1;

  while (cin >> n && n > 0) {
    cin.ignore();      // eats the new line after n
    Terminal terminal;

    string line;
    while (n-- > 0) {
      getline(cin, line);
      terminal.parse(line);
    }
    
    cout << "Case " << case_num++ << endl;
    terminal.write();
  }

  return 0;
  
}
