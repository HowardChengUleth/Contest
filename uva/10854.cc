/* @JUDGE_ID: 1102NT 10854 C++ "" */

#include <iostream>
#include <string>
#include <vector>
#include <cassert>

using namespace std;

long long num_paths(vector<string> &v, int start, int end)
{
  long long count = 0;
  long long level = 0;
  long long else_start;

  if (start == end) {
    return 1;
  }
  
  assert(v[start] == "IF");
  for (int i = start; i < end; i++) {
    if (v[i] == "IF") {
      level++;
    } else if (v[i] == "ELSE") {
      if (level == 1) {
	count += num_paths(v, start+1, i);
	else_start = i+1;
      }
    } else if (v[i] == "END_IF") {
      if (!(--level)) {
	count += num_paths(v, else_start, i);
	return count * num_paths(v, i+1, end);
      }
    }
  }
  assert(0);
}

void solve_case(void)
{
  vector<string> prog;
  string s;

  while (cin >> s && s != "ENDPROGRAM") {
    if (s != "S") {
      prog.push_back(s);
    }
  }

  cout << num_paths(prog, 0, prog.size()) << endl;
}

int main(void)
{
  int n;

  cin >> n;
  while (n-- > 0) {
    solve_case();
  }
  return 0;
}
