#include <bits/stdc++.h>
using namespace std;

int main() {
  string dw[7] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};
  string s;

  cin >> s;

  auto iter = find(begin(dw), end(dw), s);
  size_t index = distance(begin(dw), iter);
  cout << 7 - index << endl;
}
