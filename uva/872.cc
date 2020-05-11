#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

bool present[256];
bool before[256][256];
int n;
bool printed;

void doit(char order[], int n, bool used[], int index)
{
  if (index == n) {
    for (int i = 0; i < n; i++) {
      if (i) cout << ' ';
      cout << order[i];
    }
    cout << endl;
    printed = true;
    return;
  }

  for (char ch = 'A'; ch <= 'Z'; ch++) {
    if (!present[ch] || used[ch]) continue;
    int good = true;
    for (char ch2 = 'A'; ch2 <= 'Z' && good; ch2++) {
      good &= !before[ch2][ch];
    }
    if (!good) continue;

    order[index] = ch;
    used[ch] = true;
    bool temp[256];
    copy(before[ch], before[ch]+256, temp);
    fill(before[ch], before[ch]+256, false);
    doit(order, n, used, index+1);
    copy(temp, temp+256, before[ch]);
    used[ch] = false;
  }
}

void solve()
{
  n = 0;
  
  string line;
  getline(cin, line);
  istringstream iss(line);
  char ch;
  fill(present, present+256, false);
  while (iss >> ch) {
    present[ch] = true;
    n++;
  }

  for (int i = 0; i < 256; i++) {
    fill(before[i], before[i]+256, false);
  }
  getline(cin, line);
  iss.str(line);
  iss.clear();
  while (iss >> ch) {
    char ch2;
    iss >> ch2 >> ch2;
    before[ch][ch2] = true;
  }

  char order[20];
  bool used[256] = {false};

  printed = false;
  doit(order, n, used, 0);
  if (!printed) {
    cout << "NO" << endl;
  }
}

int main(void)
{
  int T;
  cin >> T;
  cin.ignore(1);
  
  for (int i = 0; i < T; i++) {
    if (i) cout << endl;
    
    string line;
    getline(cin, line);
    solve();
  }


  return 0;
}
