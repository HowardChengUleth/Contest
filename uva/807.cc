#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <utility>
#include <cassert>

using namespace std;

typedef unsigned long long ull;
typedef pair<ull,ull> Term;

class Screen {
private:
  vector<string> line;    // line[0] is actually the bottom line
  int start_pos;

  void normalize()
  {
    ull max_len = line[0].length();
    for (vector<string>::size_type i = 1; i < line.size(); i++) {
      max_len = max(max_len, (ull)line[i].length());
    }

    for (vector<string>::size_type i = 0; i < line.size(); i++) {
      line[i].resize(max_len, ' ');
    }
  }

  void print_string(string s)
  {
    while (s.length() > 0 && s[s.length()-1] == ' ') {
      s.erase(s.length()-1, 1);
    }
    cout << s << endl;
  }

public:
  Screen(ull n)
  {
    ostringstream oss;
    oss << n << " = ";
    line.push_back(oss.str());
    start_pos = oss.str().length();
  }

  void append(ull line_num, const string &s)
  {
    while (!(line_num < line.size())) {
      line.push_back("");
    }
    normalize();
    line[line_num] += s;
    normalize();
  }

  void append(ull line_num, ull n)
  {
    ostringstream oss;
    oss << n;
    append(line_num, oss.str());
  }

  void print()
  {
    while (line[0].length() > 80) {
      int split_pos = 80;
      while (split_pos >= 0 && line[0][split_pos] != '+') {
	split_pos--;
      }
      assert(split_pos >= 0);
      
      cout << endl;
      for (vector<string>::reverse_iterator it = line.rbegin(); 
	   it != line.rend(); ++it) {
	print_string(it->substr(0, split_pos));
	it->erase(0, split_pos);
	it->insert(0, start_pos, ' ');
      }
    }

    cout << endl;
    for (vector<string>::reverse_iterator it = line.rbegin(); 
	 it != line.rend(); ++it) {
      print_string(*it);
    }
  }

};

void draw(Screen &screen, ull n, ull b, ull line_num = 0);

void print_term(Screen &screen, ull line_num, const Term &term, ull b)
{
  bool print_coeff = term.second != 1;
  bool print_power = term.first != 0;

  if (print_coeff || !print_power) {
    screen.append(line_num, term.second);
  }
  if (print_power) {
    if (print_coeff) {
      screen.append(line_num, "*");
    }
    screen.append(line_num, b);
    if (term.first > 1) {
      if (term.first < b) {
	screen.append(line_num+1, term.first);
      } else {
	draw(screen, term.first, b, line_num+1);
      }
    }
  }
}

void draw(Screen &screen, ull n, ull b, ull line_num)
{
  vector<Term> term;
  ull power = 0;
  while (n > 0) {
    if (n % b != 0) {
      term.push_back(make_pair(power, n % b));
    }
    power++;
    n /= b;
  }
  reverse(term.begin(), term.end());
  for (vector<Term>::size_type i = 0; i < term.size(); i++) {
    if (i > 0) {
      screen.append(line_num, "+");
    }
    print_term(screen, line_num, term[i], b);
  }
}

int main(void)
{
  ull n, b;
  bool first = true;

  while (cin >> n >> b && (n || b)) {
    if (!first) {
      for (int i = 0; i < 80; i++) {
	cout << '-';
      }
      cout << endl;
    }
    cout << n << " in complete base " << b << ":" << endl;
    Screen screen(n);
    draw(screen, n, b);
    screen.print();

    first = false;
  }

  return 0;
}
