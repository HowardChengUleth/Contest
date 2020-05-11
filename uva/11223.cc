#include <iostream>
#include <string>
#include <map>
#include <sstream>

using namespace std;

string symbol = "AJS1.:BKT2,;CLU3?=DMV4'+ENW5!-FOX6/_GPY7(\"HQZ8)@IR09&";
string code[] = {
  ".-",
  ".---",
  "...",
  ".----",
  ".-.-.-",
  "---...",
  "-...",
  "-.-",
  "-",
  "..---",
  "--..--",
  "-.-.-.",
  "-.-.",
  ".-..",
  "..-",
  "...--",
  "..--..",
  "-...-",
  "-..",
  "--",
  "...-",
  "....-",
  ".----.",
  ".-.-.",
  ".",
  "-.",
  ".--",
  ".....",
  "-.-.--",
  "-....-",
  "..-.",
  "---",
  "-..-",
  "-....",
  "-..-.",
  "..--.-",
  "--.",
  ".--.",
  "-.--",
  "--...",
  "-.--.",
  ".-..-.",
  "....",
  "--.-",
  "--..",
  "---..",
  "-.--.-",
  ".--.-.",
  "..",
  ".-.",
  "-----",
  "----.",
  ".-...",
};

map<string,char> decode;

void decode_word(const string &line)
{
  istringstream is(line);
  string c;

  while (is >> c) {
    //    cout << "c = " << c << " ";
    cout << decode[c];
    //    cout << endl;
  }
  
}

int main(void)
{

  for (unsigned int i = 0; i < symbol.length(); i++) {
    decode[code[i]] = symbol[i];
  }

  int T;
  cin >> T;
  cin.ignore();
  for (int i = 1; i <= T; i++) {
    if (i > 1) {
      cout << endl;
    }
    cout << "Message #" << i << endl;
    
    string line;
    getline(cin, line);

    unsigned int p;
    while ((p = line.find("  ")) != string::npos) {
      decode_word(line.substr(0, p));
      cout << " ";
      line.erase(0, p+2);
    }
    if (line.length() > 0) {
      decode_word(line);
    }
    cout << endl;
    
  }

  return 0;

}
