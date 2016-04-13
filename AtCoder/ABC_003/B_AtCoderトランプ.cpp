#include <bits/stdc++.h>

using namespace std;

int main() {
  string s, t;
  string check("atcoder");

  cin >> s >> t;

  for (int i=0; i<s.size(); i++) {
    bool ok = (s[i] == t[i]);

    if (s[i] == '@' && check.find(t[i]) != string::npos) ok = true;
    if (t[i] == '@' && check.find(s[i]) != string::npos) ok = true;

    if (!ok) {
      cout << "You will lose" << endl;
      return 0;
    }
  }
  cout << "You can win" << endl;
}
