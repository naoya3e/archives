#include <bits/stdc++.h>

using namespace std;

int main() {
  int n;
  vector<pair<int, int>> vp;

  cin >> n;
  for (int i=0; i<n; i++) {
    int x;
    cin >> x;
    vp.push_back(make_pair(x, i));
  }

  sort(rbegin(vp), rend(vp));
  // sort(begin(vp), end(vp), greater<pair<int, int>>());

  for (int i=0; i<n; i++) {
    cout << vp[i].second + 1 << endl;
  }

  return 0;
}
