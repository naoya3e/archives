#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);

  string s;
  cin >> s;

  if (stoi(s)%1111 == 0) cout << "SAME" << endl;
  else cout << "DIFFERENT" << endl;
}

