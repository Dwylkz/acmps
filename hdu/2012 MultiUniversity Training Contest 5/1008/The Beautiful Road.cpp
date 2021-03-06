#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <string>
using namespace std;
#define Rep(c, a, b) for (int c = a; c < b; c++)
#define MAXN (808)
#define MOD (1000000007)
typedef long long LL;

LL dp[MAXN][2];

int main()
{
#if 1
	freopen("/home/dwylkz/Desktop/Dwylkz/2012 MultiUniversity Training Contest 5/1008/test.txt", "rt", stdin);
#endif
	int T;

    scanf("%d", &T);
	while (T--)
	{
	    char buf[MAXN];
	    scanf("%s", buf);
	    int l = strlen(buf);
	    dp[0][0] = (buf[0] == 'R' || buf[0] == '?');
	    dp[0][1] = (buf[0] == 'G' || buf[0] == '?');
	    LL tp = dp[0][0] + dp[0][1];
	    dp[1][0] = tp * (buf[1] == 'R' || buf[1] == '?');
	    dp[1][1] = tp * (buf[1] == 'G' || buf[1] == '?');
	    Rep(i, 2, l)
	    {
	        dp[i][0] = dp[i][1] = 0;
            if (buf[i] == 'R' || buf[i] == '?')
                for (int j = i - 2; j >= 0; j -= 2)
                    dp[i][0] += dp[(i + j) >> 1][1] - dp[j][0] + dp[(i + j) >> 1][0];
            if (buf[i] == 'G' || buf[i] == '?')
				dp[i][1] += dp[i - 1][0] + dp[i - 1][1];
			dp[i][0] %= MOD;
            dp[i][1] %= MOD;
	    }
	    LL o = 1;
	    Rep(i, 0, l) if (buf[i] == '?') o = o * 2 % MOD;
	    #if 0
            printf("%s\n", buf);
            Rep(i, 0, l) printf(" %4lld", dp[i][0]);
            puts("");
            Rep(i, 0, l) printf(" %4lld", dp[i][1]);
            puts("");
	    #endif
	    printf("%lld\n", o - (dp[l - 1][0] + dp[l - 1][1]) % MOD);
	}

	return 0;
}
