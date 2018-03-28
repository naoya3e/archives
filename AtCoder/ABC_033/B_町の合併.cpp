#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);

  int n;

  cin >> n;
  vector<string> s(n);
  vector<int> p(n);

  int sum = 0;
  for (int i=0; i<n; i++) {
    cin >> s[i] >> p[i];
    sum += p[i];
  }

  for (int i=0; i<n; i++) {
    if (sum/2 < p[i]) {
      cout << s[i] << endl;
      return 0;
    }
  }

  cout << "atcoder" << endl;
}

