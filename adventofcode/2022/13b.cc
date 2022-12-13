#include <bits/stdc++.h>

using namespace std;

string strip(string line)
{
  assert(line[0] == '[' && line[line.length()-1] == ']');
  return line.substr(1, line.length()-2);
}

pair<string,string> carcdr(string line)
{
  line = strip(line);

  int level = 0, len = line.length();
  for (int i = 0; i < line.length(); i++) {
    if (line[i] == '[') level++;
    if (line[i] == ']') level--;
    if (line[i] == ',' && !level) {
      len = i;
      break;
    }
  }

  string car = line.substr(0, len);
  string cdr = "[";
  if (len+1 < line.length()) {
    cdr += line.substr(len+1);
  }
  cdr += "]";

  return make_pair(car,cdr);
}

int compare(string line1, string line2)
{
  bool list1 = line1[0] == '[';
  bool list2 = line2[0] == '[';
  
  // both are integers
  if (!list1 && !list2) {
    int val1 = stoi(line1), val2 = stoi(line2);
    return val1 - val2;
  }

  // both are lists
  if (list1 && list2) {
    if (line1 == "[]" && line2 == "[]") return 0;
    if (line1 == "[]") return -1;
    if (line2 == "[]") return 1;

    auto [car1, cdr1] = carcdr(line1);
    auto [car2, cdr2] = carcdr(line2);
    
    int res = compare(car1, car2);
    if (res != 0) return res;
    return compare(cdr1, cdr2);
  }

  if (!list1) {
    assert(list2);
    return compare("[" + line1 + "]", line2);
  }

  if (!list2) {
    assert(list1);
    return compare(line1, "[" + line2 + "]");
  }

  assert(false);
}

int main()
{
  vector<string> A;
  
  string line;
  while (getline(cin, line)) {
    if (line != "") {
      A.push_back(line);
    }
  }
  A.push_back("[[2]]");
  A.push_back("[[6]]");
  sort(begin(A), end(A), [](string s1, string s2) {
			   return compare(s1, s2) < 0;
			 });

  int ans = 1;
  ans *= find(begin(A), end(A), "[[2]]") - begin(A) + 1;
  ans *= find(begin(A), end(A), "[[6]]") - begin(A) + 1;

  cout << ans << endl;
  return 0;
}
