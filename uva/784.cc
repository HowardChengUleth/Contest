#include <iostream>
#include <string>
#include <vector>

using namespace std;

void paint(vector<string> &maze, unsigned int r, unsigned int c)
{
  maze[r][c] = '#';

  if (c > 0 && maze[r][c-1] == ' ') {
    paint(maze, r, c-1);
  }
  if (c < maze[r].length()-1 && maze[r][c+1] == ' ') {
    paint(maze, r, c+1);
  }
  if (r > 0 && c < maze[r-1].length() && maze[r-1][c] == ' ') {
    paint(maze, r-1, c);
  }
  if (r < maze.size()-1 && c < maze[r+1].length() && maze[r+1][c] == ' ') {
    paint(maze, r+1, c);
  }
}

int main(void)
{
  int dummy;
  cin >> dummy;
  cin.ignore();

  vector<string> maze;
  string line;
  while (getline(cin, line)) {
    maze.push_back(line);
  }

  for (unsigned int i = 0; i < maze.size(); i++) {
    for (unsigned int j = 0; j < maze[i].length(); j++) {
      if (maze[i][j] == '*') {
	paint(maze, i, j);
      }
    }
  }

  for (unsigned int i = 0; i < maze.size(); i++) {
    cout << maze[i] << endl;
  }
  return 0;
}
