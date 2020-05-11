#include <iostream>
#include <string>

using namespace std;

int val[256];

int convert(const string &line)
{
  int ans = 0;
  for (unsigned int i = 0; i < line.length(); i++) {
    ans = ans * 4 + val[line[i]];
  }
  return ans;
}

void solve()
{
  string line;

  cin >> line;
  int num1 = convert(line);

  cin >> line;
  int num2 = convert(line);

  for (int i = 0; i < 3; i++) {
    char op;
    cin >> op;
    if (op == 'A') {
      num2 += num1;
    } else if (op == 'R') {
      num2 /= 4;
    } else if (op == 'L') {
      num2 *= 4;
    }
  }

  cin >> line;
  int num3 = convert(line);
  if (num2 == num3) {
    cout << "YES" << endl;
  } else {
    cout << "NO" << endl;
  }
}

int main(void)
{
  val['V'] = 0;
  val['U'] = 1;
  val['C'] = 2;
  val['D'] = 3;

  cout << "COWCULATIONS OUTPUT" << endl;
  int n;
  cin >> n;
  while (n--) 
    solve();
  cout << "END OF OUTPUT" << endl;
  return 0;
}
