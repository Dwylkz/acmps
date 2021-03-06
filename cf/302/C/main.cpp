#include <cstdlib>
#include <algorithm>
#include <vector>
#include <map>
#include <cstdio>
#include <cctype>
#include <string.h>
#include <iostream>
using namespace std;
const int maxn = 1e5 + 10;
#define Rep(c, a, b) for (int c = a; c < (b); c++)
int n, v[maxn], m[maxn], l, res;
bool cmp(int a, int b) {
	return abs(a) > abs(b);
}
int sum() {
	int res = 0;
	for (int i = 0; i < l; i++) {
		res += v[i];
	}
	return res;
}
void greed() {
	int rm = n;
	memset(m, 0, sizeof(m));
	for (int i = 0; rm && i < l; i++) {
		if (v[i] < 0) {
			m[i] = 1;
			v[i] *= -1;
			rm--;
		}
	}
	for (int i = l - 1; rm && 0 <= i; i--) {
		if (!m[i]) {
			v[i] *= -1;
			rm--;
		}
	}
	res = max(res, sum());
}
void dynamic() {
	int dp[220][110];
	memset(dp, 0, sizeof(dp));
	dp[0][0] = v[0];
	dp[0][1] = -v[0];
	for (int i = 1; i < l; i++) {
		for (int j = 0; j <= n; j++) {
			int tp = dp[i - 1][j] + v[i];
			if (j) {
				tp = max(tp, dp[i - 1][j - 1] + -v[i]);
			}
			dp[i][j] = tp;
		}
	}
	res = max(res, dp[l - 1][n]);
	res = max(res, dp[l - 1][0]);
}
int main()
{
#if 1
	freopen("input.txt", "r", stdin);
#endif
	while (~scanf("%d", &n)) {
		l = 2 * n - 1;
		for (int i = 0; i < l; i++) {
			scanf("%d", v + i);
		}
		res = sum();
		sort(v, v + l, cmp);
		/*for (int i = 0; i < l; i++) {
			dynamic();
		}*/
		greed();
		for (int i = l - n - 1; i < l; i++) {
			v[i] = -1 * v[i];
		}
		res = max(res, sum(););
		printf("%d\n", res);
	} 
	return 0;
}
