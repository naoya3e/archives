#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  cin >> n;

  int p[n], q[n];

  for (int i=0; i<n; i++) {
    cin >> p[i];
  }

  for (int i=0; i<n; i++) {
    cin >> q[i];
  }

  int s[n];
  int p_pos, q_pos;

  for (int i=0; i<n; i++) s[i] = i+1;

  int pos = 0;

  do {
    if (equal(s, s+n, p)) p_pos = pos;
    if (equal(s, s+n, q)) q_pos = pos;
    pos += 1;
  } while (next_permutation(s, s+n));

  cout << abs(p_pos - q_pos) << endl;
}
