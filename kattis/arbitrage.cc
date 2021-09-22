#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int main() {
    int numCurrencies;
    cin >> numCurrencies;
    while (numCurrencies != 0) {
        vector<string> currencyCodes;
        for (int i = 0; i < numCurrencies; ++i) {
            string code;
            cin >> code;
            currencyCodes.push_back(code);
        }
        int numExchangeRates;
        cin >> numExchangeRates;
        double adjMatrix[numCurrencies][numCurrencies];

	for (int i = 0; i < numCurrencies; i++) {
	  for (int j = 0; j < numCurrencies; j++) {
	    adjMatrix[i][j] = 0;
	  }
	}
        for (int c = 0; c < numCurrencies; ++c) {
            adjMatrix[c][c] = 1;
        }
        for (int j = 0; j < numExchangeRates; ++j) {
            string current1, current2;
            cin >> current1 >> current2;
            int c1Pos, c2Pos;
            c1Pos = distance(currencyCodes.begin(), find(currencyCodes.begin(), currencyCodes.end(), current1));
            c2Pos = distance(currencyCodes.begin(), find(currencyCodes.begin(), currencyCodes.end(), current2));
            double val1, val2;
            char colon;
            cin >> val1 >> colon >> val2;
            adjMatrix[c1Pos][c2Pos] = val2 / val1;
            //adjMatrix[c2Pos][c1Pos] = val1 / val2;
        }

       for (int k = 0; k < numCurrencies; ++k) {
           for (int i = 0; i < numCurrencies; ++i) {
               for (int j = 0; j < numCurrencies; ++j) {
                   adjMatrix[i][j] = max(adjMatrix[i][j], adjMatrix[i][k] * adjMatrix[k][j]);
               }
           }
        }
        for (int c = 0; c < numCurrencies; ++c) {
            if (adjMatrix[c][c] > 1) {
                cout << "Arbitrage" << endl;
                goto NextCase;
            }
        }
        cout << "Ok" << endl;
NextCase:
        cin >> numCurrencies;
    }
    return 0;
}
