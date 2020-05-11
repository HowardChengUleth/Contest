#include <iostream>
#include <string>
#include <vector>

using namespace std;

const string dirname[] = { "N", "NE", "E", "SE", "S", "SW", "W", "NW" };
const int dr[] = { -1, -1, 0, 1, 1, 1, 0, -1 };
const int dc[] = { 0, 1, 1, 1, 0, -1, -1, -1 };

int width;

vector<size_t> starts[256];

bool search(const string &text, int s, const string &needle, int p, int d)
{

  int row = p % s;
  int col = p / s;
  for (size_t i = 0; i < needle.length(); i++) {
    if (!(0 <= p && p < text.length())) return false;
    if (!(0 <= row && row < s && 0 <= col && col < width)) return false;
    if (needle[i] != text[p]) return false;

    p += dr[d] + s*dc[d];
    row += dr[d];
    col += dc[d];
  }
  
  return true;
}

void search(const string &text, int s, const string &needle)
{
  cout << needle << ' ';
  for (int i = 0; i < starts[needle[0]].size(); i++) {
    size_t p = starts[needle[0]][i];
    for (int d = 0; d < 8; d++) {
      if (search(text, s, needle, p, d)) {
	cout << p << ' ' << dirname[d] << endl;
	return;
      }
    }
  }
  cout << "NOT FOUND" << endl;
}

void solve()
{
  int s, m;
  string needle[128];

  cin >> s >> m;
  for (int i = 0; i < m; i++) {
    cin >> needle[i];
  }
  int n;
  cin >> n;
  cin.ignore(1);

  for (int i = 0; i < 256; i++) {
    starts[i].clear();
  }
  
  string line;
  string text;
  int k = 0;
  for (int i = 0; i < n; i++) {
    getline(cin, line);
    for (size_t j = 0; j < line.length(); j++) {
      if (isupper(line[j])) {
	text += line[j];
	starts[line[j]].push_back(k++);
      }
    }
  }

  width = (text.length() + s-1) / s;
  for (int i = 0; i < m; i++) {
    search(text, s, needle[i]);
  }
}

int main()
{
  int K;
  cin >> K;

  while (K--) {
    solve();
    if (K) cout << endl;
  }

  return 0;
}
