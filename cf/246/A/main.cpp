//Head
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
using namespace std;
//Dwylkz
namespace Dwylkz{
	//Type
	typedef unsigned int UI;
	typedef long long LL;
	typedef long double LD;
	//Constant
	const LL INFLL = ~0uLL >> 1;
	const int INFI = ~0u >> 1;
	const int MAXN = 1e7;
	const int MOD = 1e9 + 7;
	//Array
	typedef int AI[MAXN];
	typedef bool AB[MAXN];
	typedef double AD[MAXN];
	typedef LL ALL[MAXN];
	typedef LD ALD[MAXN];
}
using namespace Dwylkz;
//Macro
#define MS(c, a) memset(c, a, sizeof c)
#define Rep(c, a, b) for (int c = a; c < int(b); c++)
#define Nre(c, a, b) for (int c = a; c > int(b); c--)
#define FK puts("Here")
//Global
AI a;
int n;
//Main
int main(){
#if 0
	freopen("test.txt", "r", stdin);
	freopen("test.out", "w", stdout);
#endif
	while (~scanf("%d", &n)){
		if (n < 3){
			 puts("-1");
			 continue;
		}
		for (int i = n; i > 1; i--) printf("%d ", i);
		puts("1");
	}
	return 0;
}
