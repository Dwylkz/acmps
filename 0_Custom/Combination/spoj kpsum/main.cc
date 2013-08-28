#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long LL;

LL n;

LL askf(int g, int f) {
  LL rv = 0;
  if (g&1) {
    rv = -1;
    for ( ; f--; ) rv *= 10;
    rv /= 2;
  } else {
    if (f&1) {
      rv = -45;
      for ( ; --f; ) rv *= 10;
    }
  }
  return rv;
}
LL askp(LL p, int f) {
  LL rv = 0, d = 1, o = 1;
  for (LL t = p; t > 9; t /= 10) o *= 10, d++;
  for (LL t = p, i = 0; o; t %= o, o /= 10, i ^= 1)
    if (i&1) rv -= t/o;
    else rv += t/o;
  for (int i = 0; i < f; i++) rv *= 10;
  if (f+d&1) {
    if (f) rv = askf(d+f, f);
    else rv += askf(d+f, f);
  } else rv += askf(d+f, f);
  return rv;
}
LL askn(LL n) {
  if (n < 10) return n;
  LL rv = 0, d = 1, o = 1;
  for (LL t = n; t > 9; t /= 10) d++, o *= 10;
  for (int i = 1; i < d; i++)
    if (i == 1) rv -= 5;
    else for (int j = 1; j < 10; j++)
      rv += askp(j, i-1);
  for (LL t = n, p = 0; o; p = p*10+t/o, t %= o, o /= 10, d--)
    for (int i = p == 0? 1: 0; i < t/o; i++)
      rv += askp(p*10+i, d-1);
  return rv;
}
LL check(int n) {
  LL rv = 0, r = 0;
  for (int i = 0; i <= n; i++) {
    LL o = 1;
    for (int t = i; t > 9; t /= 10) o *= 10;
    for (int t = i; o; t %= o, o /= 10) {
      if (r) rv -= t/o;
      else rv += t/o;
      r ^= 1;
    }
  }
  return rv;
}

int main() {
#if 1
  freopen("input.in", "r", stdin);
#endif
//   int k = 202020;
//   printf("%lld == %lld?\n", askn(k+1), check(k));
  for ( ; ~scanf("%lld", &n), n; ) {
    printf("%lld\n", askn(n+1));
  }
  return 0;
}
