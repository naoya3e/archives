#include <bits/stdc++.h>

using namespace std;

int main() {
  int n, k;
  cin >> n >> k;

  int r[n];
  for (int i=0; i<n; i++) {
    cin >> r[i];
  }

  sort(r, r+n);

  double rate = 0;
  for (int i=n-k; i<n; i++) {
    rate = (rate + r[i]) * 0.5;
  }
  cout << fixed << rate << endl;
}
