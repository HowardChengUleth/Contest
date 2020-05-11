// coordinate compression, and then simple DP.

#include <iostream>
#include <algorithm>
#include <map>

using namespace std;

bool wall[2001][4001];
bool stuck[2001][4001];

void compress_coord(const int orig[], int orig_num, int max_coord,
		    int &num_coord, int size[], map<int, int> &coord_map)
{
  int coord[5000];
  copy(orig, orig + orig_num, coord);
  sort(coord, coord + orig_num);
  int new_num = unique(coord, coord + orig_num) - coord;
  
  num_coord = 0;
  coord_map.clear();
  
  int prev = 0;
  for (int i = 0; i < new_num; i++) {
    if (prev < coord[i]) {
      size[num_coord++] = coord[i] - prev;
    }

    coord_map[coord[i]] = num_coord;
    size[num_coord++] = 1;
    prev = coord[i]+1;
  }

  if (prev < max_coord) {
    size[num_coord++] = max_coord - prev;
  }
  
}

bool do_case(int case_num)
{
  int m, n, w;
  int wall_x1[1000], wall_x2[1000], wall_y[1000];
  
  
  cin >> m >> n >> w;
  if (!m && !n && !w) {
    return false;
  }
  for (int i = 0; i < w; i++) {
    cin >> wall_x1[i] >> wall_y[i] >> wall_x2[i] >> wall_y[i];
  }

  // compress x-coordinates
  int num_x;
  int x_size[4001];
  map<int, int> x_map;
  int wall_x[2000];
  copy(wall_x1, wall_x1 + w, wall_x);
  copy(wall_x2, wall_x2 + w, wall_x + w);
  compress_coord(wall_x, 2*w, n, num_x, x_size, x_map);
  
  // compress y-coordinates
  int num_y;
  int y_size[2001];
  map<int, int> y_map;
  compress_coord(wall_y, w, m, num_y, y_size, y_map);

  // now build a grid
  for (int y = 0; y < num_y; y++) {
    fill(wall[y], wall[y] + num_x, false);
  }

  for (int i = 0; i < w; i++) {
    int x1 = x_map[wall_x1[i]];
    int x2 = x_map[wall_x2[i]];
    int y = y_map[wall_y[i]];
    fill(wall[y]+x1, wall[y]+x2+1, true);
  }

  long long num_stuck = 0;
  for (int y = num_y - 1; y >= 0; y--) {
    for (int x = num_x - 1; x >= 0; x--) {
      if (wall[y][x]) {
	stuck[y][x] = true;
	continue;
      }
      if (y == num_y - 1 && x == num_x - 1) {
	stuck[y][x] = false;
	continue;
      }
      stuck[y][x] = !((y < num_y-1 && !stuck[y+1][x]) ||
		      (x < num_x-1 && !stuck[y][x+1]));
      if (stuck[y][x]) {
	num_stuck += (long long)x_size[x] * y_size[y];
      }
    }
  }
  cout << "Case " << case_num << ": " << num_stuck << endl;
  
  return true;
}

int main(void)
{
  int case_num = 1;
  while (do_case(case_num++))
    ;
  
  return 0;
}
