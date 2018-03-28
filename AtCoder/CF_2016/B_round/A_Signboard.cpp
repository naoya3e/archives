#include <bits/stdc++.h>

using namespace std;

int main() {
  string s;
  cin >> s;

  string org = "CODEFESTIVAL2016";
  int fix = 0;

  for (int i=0; i<16; i++) {
    if (s[i] != org[i]) {
      fix += 1;
    }
  }

  cout << fix << endl;

  return 0;
}
