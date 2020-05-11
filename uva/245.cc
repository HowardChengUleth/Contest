#include <iostream>
#include <string>
#include <deque>
#include <cctype>
#include <cassert>

using namespace std;

int main(void)
{
  deque<string> words;

  char c;
  string word;
  int index = 0;
  bool inword = false, innum = false;

  while (cin.get(c)) {
    assert(!(inword && innum));
    if (isalpha(c)) {
      word += c;
      inword = true;
      innum = false;
    } else if (isdigit(c)) {
      index = 10*index + c - '0';
      innum = true;
      inword = false;
    } else {
      if (inword) {
	cout << word;
	words.push_front(word);
	word = "";
	inword = false;
      } else if (innum) {
	if (index == 0) break;
	cout << (word = words[index-1]);
	words.erase(words.begin()+index-1);
	words.push_front(word);
	word = "";
	index = 0;
	innum = false;
      }

      cout << c;
    }
  }
  return 0;
}
