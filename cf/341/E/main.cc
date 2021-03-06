#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;
const int N = 1e3+10;

int a[N], ax[N<<10], ay[N<<10];

int main() {
#if 1
  freopen("input.in", "r", stdin);
#endif
  for (int n; ~scanf("%d", &n); ) {
    for (int i = 0; i < n; i++) scanf("%d", a+i);
    int p1, p2 = 0, p3 = 1, an = 0;
    for (int i = 2; i < n; i++)
      for (p1 = i; ; ) {
        if (a[p1] > a[p2]) swap(p1, p2);
        if (a[p2] > a[p3]) swap(p2, p3);
        if (a[p1] > a[p2]) swap(p1, p2);
        if (!a[p1]) break;
        for (int j = a[p2]/a[p1]; j; j >>= 1, a[p1] <<= 1) {
          ax[an] = p1;
          if (j&1) {
            a[p2] -= a[p1];
            ay[an++] = p2;
          } else {
            a[p3] -= a[p1];
            ay[an++] = p3;
          }
        }
      }
    if (!a[p2]) puts("-1");
    else {
      printf("%d\n", an);
      for (int i = 0; i < an; i++) printf("%d %d\n", ax[i]+1, ay[i]+1);
    }
  }
  return 0;
}
