#include <iostream>
#include <string>
#include <cassert>

using namespace std;

bool is_label(char c)
{
  return c != '-' && c != '|' && c != ' ' && c != '#';
}

void print_tree(string line[201], int rows, int r, int c)
{
  cout << line[r][c];

  if (r+1 >= rows || line[r+1][c] != '|') {
    // leaf node
    cout << "()";
    return;
  }

  // not leaf
  assert(r+3 < rows && c < line[r+2].length() && line[r+2][c] == '-');
  int left, right;
  for (left = c; left > 0 && line[r+2][left-1] == '-'; left--)
    ;

  for (right = c; right < line[r+2].length()-1 && line[r+2][right+1] == '-';
       right++)
    ;

  cout << "(";
  for (int i = left; i <= right && i < line[r+3].length(); i++) {
    if (is_label(line[r+3][i])) {
      print_tree(line, rows, r+3, i);
    }
  }
  cout << ")";
}

void do_case(void)
{
  string line[201];
  int rows = 0;

  while (getline(cin, line[rows]) && line[rows] != "#") {
    rows++;
  }

  for (int r = 0; r < rows; r++) {
    for (int c = 0; c < line[r].length(); c++) {
      if (is_label(line[r][c])) {
	cout << "(";
	print_tree(line, rows, r, c);
	cout << ")" << endl;
	return;
      }
    }
  }
  cout << "()" << endl;
}

int main(void)
{
  int T;
  cin >> T;
  cin.ignore(1);
  while (T-- > 0) {
    do_case();
  }
    
  return 0;
}
