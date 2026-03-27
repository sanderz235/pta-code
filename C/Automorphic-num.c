
#include <stdio.h>

int IsAutomorphic(int x);
void FindAutomorphic(int lower, int upper);

int main()
{
    int a, b;
    scanf("%d%d", &a, &b);
    FindAutomorphic(a, b);
    return 0;
}


int IsAutomorphic(int x)
{
	int sq = x * x;
	while (x > 0) {
		if (x % 10 != sq % 10) return 0;
		x /= 10; sq /= 10;
	}
	return 1;
}
void FindAutomorphic(int lower, int upper)
{
	for (int i = lower; i <= upper; i++) {
		if (IsAutomorphic(i)) printf("%d ", i);
	}
	putchar('\n');
}