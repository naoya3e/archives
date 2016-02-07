#include <bits/stdc++.h>
using namespace std;

int main() {
  string s;
  size_t p;

  cin >> s;

  while ((p = s.find_first_of("aiueo")) != string::npos) {
    s.erase(p, 1);
  }

  cout << s << endl;
}

