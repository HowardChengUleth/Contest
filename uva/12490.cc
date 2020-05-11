// Integral = (f(0) + f(n))/2 + sum f(k)

#include <iostream>
#include <utility>
#include <algorithm>
using namespace std;

const int MAX_N = 1000030;
pair<int,int> F[MAX_N];
int diff[MAX_N];

int main(){
	int N,M,Y;
	while(cin >> N >> M >> Y){
		for(int i=0;i<M;i++)
			cin >> F[i].first >> F[i].second;
		sort(F,F+M);
		if((F[0].second + F[M-1].second) % 2 == 1){
			cout << "N" << endl;
			continue;
		}
		
		int base = (F[0].second + F[M-1].second)/2;
		int inter = M-2;
		diff[N] = 0;
		for(int i=N-1;i>=0;i--){
			if(F[inter].first == i){
				diff[i] = diff[i+1];
				if(i) base += F[inter].second;
				inter--;
			} else {
				diff[i] = diff[i+1] + abs(F[inter].second - F[inter+1].second);
				base += min(F[inter].second,F[inter+1].second);
			}
		}
		
		if(!(base <= Y && Y <= base + diff[1])){
			cout << "N" << endl;
			continue;
		}
		
		Y -= base;
		
		cout << "S";
		
		for(int i=0;i<M-1;i++){
			// If this interval is constant, print it...
			if(F[i].second == F[i+1].second){
				for(int j=F[i].first+1;j<F[i+1].first;j++)
					cout << " " << F[i].second;
				continue;
			}
			
			// If this interval is increasing...
			if(F[i].second < F[i+1].second){
				// If this is where the transition happens
				if(diff[F[i].first] >= Y && diff[F[i+1].first] < Y){
					for(int j=F[i].first+1;j<F[i+1].first;j++){
						if(diff[j] >= Y && diff[j+1] < Y){
							cout << " " << (Y-diff[j+1]+min(F[i].second,F[i+1].second));
							Y = diff[j+1];
						} else {
							cout << " " << min(F[i].second,F[i+1].second);
						}
					}
				} else { // Otherwise, take the minimum
					for(int j=F[i].first+1;j<F[i+1].first;j++)
						cout << " " << min(F[i].second,F[i+1].second);
				}
				continue;
			}
			
			// If this interval is decreasing...
			if(F[i].second > F[i+1].second){
				// If this is where the transition happens
				if(diff[F[i].first] >= Y && diff[F[i+1].first] < Y){
					// If we're decreasing here, then we want to spread
					// this out as much as possible. Look to see how much
					// the next interval can handle, and we'll take the
					// rest
					int y = Y - diff[F[i+1].first];
					Y = diff[F[i+1].first];
					int n = F[i+1].first - F[i].first - 1;
					for(int k=0;k<n;k++)
						cout << " " << min(F[i].second,F[i+1].second)+
						((k < (y % n)) + y/n);
				} else { // Otherwise, take the minimum
					for(int j=F[i].first+1;j<F[i+1].first;j++)
						cout << " " << min(F[i].second,F[i+1].second);
				}
			}
		}
		cout << endl;
	}
	return 0;
}
