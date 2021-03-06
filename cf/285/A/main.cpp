#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <string.h>
#include <iostream>
using namespace std;
const int MAXN = 10e5 + 10;

int n, k, q[MAXN];

int main()
{
#if 0
	freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
#endif
	int p;
	while (~scanf("%d%d", &n, &k)) {
		for (int i = 0; i < n; i++) {
			q[i] = i + 1;
		}
		k++;
		for (int i = 0; i < k / 2; i++) {
			swap(q[i], q[k - i - 1]);
		}
		printf("%d", q[0]);
		for (int i = 1; i < n; i++) {
			printf(" %d", q[i]);
		}
		puts("");
	}
	return 0;
}
