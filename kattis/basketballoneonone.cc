#include <iostream>
#include <string>

using namespace std;

int main()
{
    string s;
    cin >> s;
    
    int score[2] = { 0 };
    string name = "AB";
    bool tiebreak = false;
    for (int i = 0; i < s.length(); i += 2) {
        int who = s[i] - 'A';
        int inc = s[i+1] - '0';
        score[who] += inc;
        
        if ((score[who] >= 11 && !tiebreak) ||
            (tiebreak && score[who] - score[1-who] >= 2)) {
            cout << name[who] << endl;
            break;
        }
        
        if (score[who] == 10 && score[1-who] == 10) {
            tiebreak = true;
        }
    }
    
    
    
    return 0;
}