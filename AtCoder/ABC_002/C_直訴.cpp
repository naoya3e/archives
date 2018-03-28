#include <bits/stdc++.h>
using namespace std;

int main() {
  int xa, ya, xb, yb, xc, yc;

  cin >> xa >> ya >> xb >> yb >> xc >> yc;

  cout << fixed << setprecision(1) << fabs((xb-xa)*(yc-ya) - (yb-ya)*(xc-xa)) / 2.0 << endl;
}

