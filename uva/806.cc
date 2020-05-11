#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


const int dr[5] = { -1, 0, 0, 1, 1 };
const int dc[5] = { -1, 0, 1, 0, 1 };

void compress(char image[64][64], int n, int r, int c, int curr_num, 
	      int power, vector<int> &nodes)
{
  bool found_black = false, found_white = false;

  for (int i = r; i < r+n; i++) {
    for (int j = c; j < c+n; j++) {
      found_black |= image[i][j] == '1';
      found_white |= image[i][j] == '0';
    }
  }
  if (found_white && !found_black) {
    return;
  }
  if (!found_white && found_black) {
    nodes.push_back(curr_num);
    return;
  }
  
  for (int i = 1; i <= 4; i++) {
    compress(image, n/2, r + dr[i]*n/2, c + dc[i]*n/2, curr_num+i*power,
	     power*5, nodes);
  }
}

void uncompress(char image[64][64], int n, int r, int c, int curr_num)
{
  if (curr_num == 0) {
    for (int i = r; i < r+n; i++) {
      fill(image[i]+c, image[i]+c+n, '*');
    }
    return;
  }

  int branch = curr_num % 5;
  uncompress(image, n/2, r + dr[branch]*n/2, c + dc[branch]*n/2, curr_num / 5);
}

void image2path(int n)
{
  char image[64][64];

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> image[i][j];
    }
  }

  vector<int> nodes;
  compress(image, n, 0, 0, 0, 1, nodes);
  sort(nodes.begin(), nodes.end());
  bool first_in_line = true;
  int num_in_line = 0;
  for (vector<int>::const_iterator it = nodes.begin(); it != nodes.end(); ++it) {
    if (num_in_line == 12) {
      num_in_line = 0;
      first_in_line = true;
      cout << endl;
    }
    if (!first_in_line) {
      cout << ' ';
    }
    cout << *it;
    first_in_line = false;
    num_in_line++;
  }
  if (nodes.size() > 0) {
    cout << endl;
  }
  cout << "Total number of black nodes = " << nodes.size() << endl;
}

void path2image(int n)
{
  char image[64][64];
  for (int i = 0; i < n; i++) {
    fill(image[i], image[i]+n, '.');
  }

  int node;
  while (cin >> node && node != -1) {
    uncompress(image, n, 0, 0, node);
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cout << image[i][j];
    }
    cout << endl;
  }
}

int main(void)
{
  int n;
  int cases = 1;

  while (cin >> n && n != 0) {
    if (cases > 1) {
      cout << endl;
    }
    cout << "Image " << cases++ << endl;
    if (n > 0) {
      image2path(n);
    } else {
      path2image(-n);
    }
  }
  return 0;
}
