#include <iostream>
#include <string>
#include <algorithm>
#include <cassert>
#include <vector>

using namespace std;

const string sep  = "{}[](),.:\n\t ";
const string keywords[] = {"of", "array", "string"};

typedef long long ll;

vector<string> tokens;
int ti = 0;

string nextToken()
{
  char c;

  cin >> c;
  if (cin.eof()) return "";

  if (sep.find(c) != string::npos) {
    if (c == '.') {
      cin >> c;
      assert(c == '.');
      return "..";
    }
    return string(1,c);
  }

  string res = string(1,c);
  while (cin.peek() != EOF && sep.find(cin.peek()) == string::npos) {
    if ((isdigit(res[0]) || res[0] == '-') &&
	!isdigit(cin.peek())) break;
    cin >> c;
    res += c;
    if (find(keywords, keywords+3, res) != keywords+3) break;
  }
  return res;
}

ll bits(int n)
{
  ll ans = 0;
  ll power = 1;

  while (power < n) {
    ans++;
    power *= 2;
  }
  return ans;
}

ll Type();
ll Message(bool print = false);

ll RangeSize()
{
  assert(tokens[ti++] == "[");
  int lo = stoi(tokens[ti++]);
  assert(tokens[ti++] == "..");
  int hi = stoi(tokens[ti++]);
  assert(tokens[ti++] == "]");

  return hi-lo+1;
}

ll Record()
{
  ll ans = 0;

  if (tokens[ti] != "{") {
    return 0;
  }
  ti++;

  while (tokens[ti] != "}") {
    ans += Message();
  }
  ti++;

  return ans;
}

ll Array()
{
  if (tokens[ti] != "array" || tokens[ti+1] != "[") {
    return 0;
  }
  ti++;
  ll num = RangeSize();
  assert(tokens[ti++] == "of");
  ll elem = Type();
  return num * elem;
}

ll String()
{
  if (tokens[ti] != "string" || tokens[ti+1] != "(") {
    return 0;
  }
  ti++;
  assert(tokens[ti++] == "(");
  ll len = stoi(tokens[ti++]);
  assert(tokens[ti++] == ")");

  return len * 7;
}

ll Enum()
{
  if (tokens[ti] != "(") {
    return 0;
  }
  ti++;

  ll count = 1;  
  while (tokens[ti] != ")") {
    if (tokens[ti] == ",") count++;
    ti++;
  }
  ti++;

  return bits(count);
}

ll Range()
{
  if (tokens[ti] != "[") {
    return 0;
  }
  ti++;

  ll lo = stoi(tokens[ti++]);
  assert(tokens[ti++] == "..");
  ll hi = stoi(tokens[ti++]);
  assert(tokens[ti++] == "]");

  return bits(hi-lo+1);
}

ll Type()
{
  return Record() + Array() + String() + Enum() + Range();
}

ll Message(bool print)
{
  string id = tokens[ti++];
  while (tokens[ti] != ":") {
    id += tokens[ti++];
  }
  ti++;
  ll size = Type();
  if (print) {
    cout << "A \"" << id << "\" message requires " << size 
	 << " bits." << endl;
  }
  return size;
}

int main()
{
  int N;
  cin >> N;

  string s;
  while (!cin.eof() && ((s = nextToken()) != "")) {
    tokens.push_back(s);
    //          cout << "|" << s << "| = " << (s.length()) << endl;
  }
  tokens.push_back("");

  while (N--) {
    Message(true);
  }

  return 0;
}
