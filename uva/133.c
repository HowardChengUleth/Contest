/* @JUDGE_ID: 1102NT 133 C "" */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

int used[30];
int N, k, m;

int inc(int i)
{
    if (i+1 >= N) {
	return 0;
    } else {
	return i+1;
    }
}

int dec(int i)
{
    if (i-1 < 0) {
	return N-1;
    } else {
	return i-1;
    }
}

int find_next1(int p1)
{
    for (p1 = inc(p1); used[p1]; p1 = inc(p1))
	;
    return p1;
}

int find_next2(int p2)
{
    for (p2 = dec(p2); used[p2]; p2 = dec(p2))
	;
    return p2;
}

void main(void)
{
    int i, p1, p2, count;
    while (scanf("%d %d %d", &N, &k, &m) == 3 && (N || k || m)) {
	for (i = 0; i < N; i++) {
	    used[i] = 0;
	}
	count = N;
	p1 = N-1;
	p2 = 0;
	while (count > 0) {
	    for (i = 0; i < k; i++) {
		p1 = find_next1(p1);
	    }
	    for (i = 0; i < m; i++) {
		p2 = find_next2(p2);
	    }
	    assert(!used[p1] && !used[p2]);
	    used[p1] = used[p2] = 1;
	    if (count != N) {
		printf(",");
	    }
	    printf("%3d", p1+1);
	    count--;
	    if (p1 != p2) {
		printf("%3d", p2+1);
		count--;
	    }
	}
	printf("\n");
    }
}
