#include <bits/stdc++.h>

using namespace std;



int syllables(string s)
{
  transform(begin(s), end(s), begin(s), [](char c) { return tolower(c); });
  const string vowels = "aeiou";

  string w;
  for (auto c : s) {
    if (isalpha(c)) w += c;
  }

  string vc;
  int n = w.length();
  for (int i = 0; i < n; i++) {
    if (w[i] == 'y' && (i == 0 || vowels.find(w[i-1]) == string::npos)) {
      vc += 'V';
    } else if (vowels.find(w[i]) == string::npos) {
      vc += 'C';
    } else if (w[i] == 'u' && i > 0 && w[i-1] == 'q') {
      ;
    } else if (vowels.find(w[i]) != string::npos) {
      vc += 'V';
    }
  }

  int ans = 0;
  if (n >= 1 && w[n-1] == 'e' &&
      !(n-2 >= 0 && vc.length()-3 >= 0 && w[n-2] == 'l'
	&& vc[vc.length()-3] == 'C')) {
    vc.erase(vc.length()-1);
  } else if (n >= 2 && w[n-2] == 'e' && w[n-1] == 's' &&
	     (vc.length() >= 3 && vc[vc.length()-3] == 'C')
	     && (vc.length() >= 4 && vc[vc.length()-4] == 'V')) {
    ans--;
  }

  vc += 'C';
  bool cons = true;
  for (auto c : vc) {
    if (c == 'C') {
      if (!cons) {
	ans++;
      }
      cons = true;
    } else {
      cons = false;
    }
  }

  ans = max(ans, 1);
  return ans;
}

void print_line(const vector<string> &line)
{
  bool first = true;
  for (auto w : line) {
    if (!first) cout << ' ';
    cout << w;
    first = false;
  }
  cout << endl;

}

int main()
{
  string oline;
  getline(cin, oline);

  istringstream iss(oline);
  vector<string> word;
  string s;
 
  while (iss >> s) {
    word.push_back(s);
  }

  const int total[] = {5,7,5};
  vector<string> line[3];

  bool good = true;
  int curr_count = 0;
  int curr_line = 0;
  for (auto w : word) {
    if (curr_line >= 3) {
      good = false;
      break;
    }
    int c = syllables(w);
    //   cout << w << ": " << c << endl;
    if (c + curr_count <= total[curr_line]) {
      line[curr_line].push_back(w);
      curr_count += c;
      if (curr_count == total[curr_line]) {
	curr_line++;
	curr_count = 0;
      }
    } else {
      good = false;
      break;
    }
  }
  good &= curr_count == 0 && curr_line == 3;

  if (good) {
    for (int i = 0; i < 3; i++) {
      print_line(line[i]);
    }
  } else {
    cout << oline << endl;
  }
  
  return 0;
}
