/* @JUDGE_ID: 1102NT 350 C "" */

#include <stdio.h>
#include <assert.h>

int used[10000];
int M, Z, I, L;

int main(void)
{
    int i, case_no = 1;

    while (scanf("%d %d %d %d", &Z, &I, &M, &L) == 4 && (Z || I || M || L)) {
	printf("Case %d: ", case_no++);
	for (i = 0; i < M; i++) {
	    used[i] = 0;
	}
	i = 0;
	while (!used[L]) {
	    used[L] = ++i;
	    L = (((Z*L)%M) + I)%M;
	}
	printf("%d\n", i+1-used[L]);
    }
    return 0;
}
