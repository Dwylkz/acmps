//coder: SXDwylkz
//heads
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cctype>
#include <algorithm>
#include <vector>
#include <map>
#include <stack>
#include <queue>
#include <string>
#include <cstring>
//namespaces
using namespace std;
//constants
const char input[] = "input.in",
	  output[] = "output.out";
const int inf32 = 0x7fffffff,
	  maxn = 1e5 + 10;
const long long inf64 = 0x7fffffffffffffffLL; 
//structure
//type definition
typedef long long LL;
//global variable
int N, M;
map<string, string> sh;
char f[30], t[30], b[200];
//access and mutator
//main
int main() {
#if 1
	freopen(input, "r", stdin);
	//freopen(output, "w", stdout);
#endif
	int T;
	scanf("%d", &T);
		for (int Case = 1; Case <= T; Case++) {
			sh.clear();
			scanf("%d%d", &N, &M);
			for (int i = 0; i < M; i++) {
				scanf("%s%s", f, t);
				sh[f] = t;
			}
			scanf("\n%[^\n]\n", b);
			string m = b;
			for (int i = 0; i < N - 1; i++) {
				string tm = "";
				for (int j = 0; j < m.length(); j++) {
					if ('a' <= m[j] && m[j] <= 'z') {
						string w = "";
						for ( ; j < m.length() && 'a' <= m[j] && m[j] <= 'z'; j++) {
							w += m[j];
						}
#if 0
						puts(buf.c_str());
#endif
						if (sh.find(w) != sh.end()) {
							tm += sh[w];
						} else {
							tm += w;
						}
						j--;
					} else {
						tm += m[j];
					}
				}
				m = tm.c_str();
			}
			printf("Case #%d: %s\n", Case, m.c_str());
		}
	return 0;
}
