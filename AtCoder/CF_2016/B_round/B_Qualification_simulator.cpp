#include <bits/stdc++.h>

using namespace std;

int main() {
  int n, a, b;
  int passed = 0;
  int overseas = 0;
  string s;

  cin >> n >> a >> b >> s;

  for (int i=0; i<n; i++) {
    if (s[i] == 'a') {
      if (passed < a + b) {
        cout << "Yes" << endl;
        passed += 1;
      } else {
        cout << "No" << endl;
      }
    } else if (s[i] == 'b') {
      if (passed < a + b && overseas < b) {
        cout << "Yes" << endl;
        passed += 1;
        overseas += 1;
      } else {
        cout << "No" << endl;
      }
    } else {
      cout << "No" << endl;
    }
  }

  return 0;
}
