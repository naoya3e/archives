#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  cin >> n;

  int exp = 0;
  for (int i=1; i<=n; i++) {
    exp += i*10000 * 1/n;
  }

  cout << exp << endl;
}
