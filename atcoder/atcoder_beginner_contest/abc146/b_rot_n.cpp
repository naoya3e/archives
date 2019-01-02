#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  string s;

  cin >> n >> s;

  for (auto&& c: s) {
    c = ((c - 'A' + n) % 26) + 'A';
  }

  cout << s << endl;
}
