//Kimady::S.X.Dwylkz
#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <stack>
#include <string>
#include <vector>
//Namespace
namespace dtd{
	//Constant
	const long long INFLL = ~0uLL>>1;
	const int INFI = ~0u>>1;
	const int MAXN = 100;
	const int MAXM = 100;
	const int MOD = 1e+7;
	//Type Definition
	typedef unsigned int UI;
	typedef long long LL;
	typedef long double LD;
	typedef int AI[MAXN];
	typedef bool AB[MAXN];
	typedef double AD[MAXN];
	typedef LL ALL[MAXN];
	typedef LD ALD[MAXN];
	typedef AI AI2[MAXM];
	typedef AB AB2[MAXM];
	typedef AD AD2[MAXM];
	typedef ALL ALL2[MAXM];
	typedef ALD ALD2[MAXM];
}
using namespace std;
using namespace dtd;
//Macro
#define Bug puts("Here")
//Global
char s[1000], t[] = "GZHU";
//Main
int main()
{
#if 0
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
#endif
	while (~scanf("%s", s)) {
		int sl = strlen(s), j = 0;
		for (int i = 0; i < sl; i++) {
			if (s[i] == t[j]) {
				j++;
			}
		}
		puts(4 < sl && j == 4? "Yes": "No");
	}
	return 0;
}
