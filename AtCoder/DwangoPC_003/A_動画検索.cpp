#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, a, b;
  cin >> n >> a >> b;

  int ok = (a + b) - n;
  if (ok > 0) {
    cout << ok << endl;
  } else {
    cout << 0 << endl;
  }
}
