#include <iostream>
#include <cstring>
#include <algorithm>
#include <numeric>
#include <cassert>

using namespace std;

const string keys[9] = {
   "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz", " "
};

int pressed(char c)
{
   for (int i = 0; i < 9; i++) {
      string::size_type pos = keys[i].find(c);
      if (pos != string::npos) {
	 return pos + 1;
      }
   }
   assert(0);
}

int main(void)
{
   int T;
   cin >> T;
   cin.ignore(1);
   for (int i = 0; i < T; i++) {
      cout << "Case #" << i+1 << ": ";
      string input;
      int count[100];
      
      getline(cin, input);
      transform(input.begin(), input.end(), count, pressed);
      cout << accumulate(count, count + input.length(), 0) << endl;
   }
   return 0;
}
