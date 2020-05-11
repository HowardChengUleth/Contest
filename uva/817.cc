#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <vector>
#include <stack>

using namespace std;



long long eval(char prob[], int n)
{
  int last_mul = -1;
  for (int i = n-1; i >= 0; i--) {
    if (prob[i] == '+') {
      return eval(prob, i) + eval(prob+i+1, n-i-1);
    } else if (prob[i] == '-') {
      return eval(prob, i) - eval(prob+i+1, n-i-1);
    } else if (prob[i] == '*' && last_mul < 0) {
      last_mul = i;
    }
  }

  if (last_mul >= 0) {
    return eval(prob, last_mul) * eval(prob+last_mul+1, n-last_mul-1);
  }

  long long sum = 0;
  for (int i = 0; i < n; i++) {
    sum = sum*10 + prob[i] - '0';
  }
  return sum;
}

vector<string> v;

bool test(const string &line, int n, int mask)
{
  char prob[100];
  int k = 0;
  prob[k++] = line[0];
  bool first0 = line[0] == '0';
  
  for (int i = 1; i < n; i++) {
    bool op = false;
    switch (mask & 3) {
    case 1:
      prob[k++] = '+';
      op = true;
      break;
    case 2:
      prob[k++] = '-';
      op = true;
      break;
    case 3:
      prob[k++] = '*';
      op = true;
      break;
    case 0:
      if (first0) return false;
    }
    prob[k++] = line[i];
    first0 = (op && line[i] == '0');
      
    mask >>= 2;
  }

  prob[k] = 0;
  bool ans = eval(prob, k) == 2000;
  if (ans) {
    v.push_back(string(prob) + "=");
  }
  return ans;
}

bool solve(int id)
{
  string line;
  cin >> line;
  if (line == "=") return false;

  int n = line.length()-1;
  line = line.substr(0, n);

  cout << "Problem " << id << endl;

  v.clear();
  
  bool found = false;
  for (int i = 1; i < (1 << (2*n-2)); i++) {
    found |= test(line, n, i);
  }
  if (!found) {
    cout << "  IMPOSSIBLE" << endl;
  } else {
    sort(v.begin(), v.end());
    for (unsigned int i = 0; i < v.size(); i++) {
      cout << "  " << v[i] << endl;
    }
  }
  return true;
}

int main()
{
  int id = 1;
  while (solve(id++))
    ;
  return 0;
}
