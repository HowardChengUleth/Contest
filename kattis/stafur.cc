#include <bits/stdc++.h>

using namespace std;

int main()
{
    const string vowels = "AEIOU";
    
    char ch;

    cin >> ch;
    if (ch == 'Y') {
	cout << "Kannski" << endl;
    } else if (vowels.find(ch) != string::npos) {
	cout << "Jebb" << endl;
    } else {
	cout << "Neibb" << endl;
    }

    return 0;
}
