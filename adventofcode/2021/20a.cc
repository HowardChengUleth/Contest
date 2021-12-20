#include <bits/stdc++.h>

using namespace std;
typedef vector<vector<int>> vvi;

string alg;

int border = 100;

vvi conv(const vvi &image, int def)
{
  vvi out = image;

  int m = image.size();
  int n = image[0].size();
  
  for (int r = 0; r < m; r++) {
    for (int c = 0; c < n; c++) {
      int t = 0;
      for (int i = r-1; i <= r+1; i++) {
	for (int j = c-1; j <= c+1; j++) {
	  int val = def;
	  if (0 <= i && i < m && 0 <= j && j < n) {
	    val = image[i][j];
	  }
	  t = t*2 + val;
	}
      }
      out[r][c] = (alg[t] == '#' ? 1 : 0);
    }
  }

  return out;
}

void print(const vvi &image)
{
  for (const auto &v : image) {
    for (auto x : v) {
      cout << (x ? "#" : ".");
    }
    cout << endl;
  }
}

int main()
{
  getline(cin, alg);

  string line;
  getline(cin, line);

  vector<string> input;
  while (getline(cin, line)) {
    input.push_back(line);
  }

  int m = input.size() + 2*border;
  int n = input[0].length() + 2*border;
  
  vvi image(m);
  for (auto &v : image) {
    v.resize(n, 0);
  }
  for (int i = 0; i < input.size(); i++) {
    for (int j = 0; j < input[i].length(); j++) {
      image[i+border][j+border] = (input[i][j] == '#' ? 1 : 0);
    }
  }
  print(image);

  image = conv(image, 0);
  print(image);
  image = conv(image, (alg[0] == '#'));
  print(image);
  int ans = 0;
  for (const auto &v : image) {
    for (auto x : v) {
      if (x) ans++;
    }
  }

  cout << ans << endl;
  
  
  return 0;
}
