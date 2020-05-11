#include <iostream>
#include <string>
using namespace std;

const int MAX_N = 1030;
int len[MAX_N];

int main(){
	int N,L,C;
	string tmp;
	while(cin >> N >> L >> C){
		for(int i=0;i<N;i++){
			cin >> tmp;
			len[i] = tmp.length()+1;
		}
		C++;
		int lines = 1;
		int chars = 0;
		int word = 0;
		while(word < N){
			if(chars + len[word] > C){
				chars = 0;
				lines++;
			} else {
				chars += len[word];
				word++;
			}
		}
		cout << (lines + L - 1)/L << endl;
	}
	return 0;
}
