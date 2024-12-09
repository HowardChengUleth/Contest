#include <bits/stdc++.h>

using namespace std;

vector<int> read_disk()
{
  string line;
  cin >> line;

  int total = 0;
  for (int i = 0; i < line.length(); i++) {
    total += line[i] - '0';
  }

  vector<int> disk(total);
  bool infile = true;
  int id = 0;
  int di = 0;
  for (int i = 0; i < line.length(); i++) {
    int blocks = line[i] - '0';
    for (int j = 0; j < blocks; j++) {
      disk[di++] = (infile ? id : -1);
    }
    if (infile) {
      id++;
    }

    infile = !infile;
  }

  return disk;
}

void compact(vector<int> &disk)
{
  int free_id = 0;
  int next_id = disk.size()-1;

  while (free_id <= next_id) {
    while (free_id <= next_id && disk[free_id] >= 0) {
      free_id++;
    }
    while (free_id <= next_id && disk[next_id] < 0) {
      next_id--;
    }

    if (free_id < next_id) {
      assert(disk[free_id] < 0);
      assert(disk[next_id] >= 0);

      disk[free_id] = disk[next_id];
      disk[next_id] = -1;

      free_id++;
      next_id--;
    }
  }
}

long long calc_checksum(const vector<int> &disk)
{
  long long ans = 0;
  
  for (int i = 0; i < disk.size(); i++) {
    if (disk[i] < 0) continue;
    ans += disk[i] * i;
  }
  return ans;
}

int main()
{
  vector<int> disk = read_disk();
  compact(disk);
  long long checksum = calc_checksum(disk);
  cout << checksum << endl;
  /*
  for (auto x : disk) {
    if (x >= 0) {
      cout << x;
    } else {
      cout << '.';
    }
  }
  cout << endl;*/

  return 0;
}
