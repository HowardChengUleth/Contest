/* @JUDGE_ID: 1102NT 441 C "" */


void choose(int *list, int n, int curr, int *selected, int k)
{
    int i, j;

    if (k == 0) {
	for (i = 0; i < 6; i++) {
	    if (i) {
		printf(" ");
	    }
	    printf("%d", selected[i]);
	}
	printf("\n");
	return;
    }

    if (curr >= n || curr + k > n) {
	return;
    }

    selected[6-k] = list[curr];
    choose(list, n, curr+1, selected, k-1);
    choose(list, n, curr+1, selected, k);


}

int main(void)
{
    int list[20], selected[6];
    int n, i, case_no;

    case_no = 0;
    while (scanf("%d", &n) == 1 && n > 0) {
	for (i = 0; i < n; i++) {
	    scanf("%d", list+i);
	}
	if (++case_no > 1) {
	    printf("\n");
	}
	choose(list, n, 0, selected, 6);
    }
    return 0;
}
