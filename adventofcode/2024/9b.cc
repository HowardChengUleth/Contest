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

void print_disk(const vector<int> &disk)
{
  for (auto x : disk) {
    if (x >= 0) {
      cout << x;
    } else {
      cout << '.';
    }
  }
  cout << endl;
}


void compact(vector<int> &disk)
{
  vector<pair<int,int>> empty;
  int i = 0, len;
  while (i < disk.size()) {
    if (disk[i] >= 0) {
      i++;
    } else {
      len = 1;
      while (i + len < disk.size() && disk[i+len] < 0) {
	len++;
      }
      empty.emplace_back(i, len);
      i += len;
    }
  }

  i = disk.size()-1;
  while (i >= 0) {
    if (disk[i] < 0) {
      i--;
      continue;
    }
    
    int file_id = disk[i];
    len = 1;
    while (i - len >= 0 && disk[i - len] == file_id) {
      len++;
    }

    for (int k = 0; k < empty.size(); k++) {
      if (empty[k].first < i-len && empty[k].second >= len) {
	for (int j = 0; j < len; j++) {
	  disk[empty[k].first + j] = disk[i - j];
	  disk[i - j] = -1;
	}
	empty[k].first += len;
	empty[k].second -= len;
	break;
      }
    }
    
    i -= len;
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

  return 0;
}
