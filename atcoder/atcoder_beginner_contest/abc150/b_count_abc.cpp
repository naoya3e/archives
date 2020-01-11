#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  string s;

  int n_abc = 0;

  cin >> n >> s;

  for (int i=0; i<n-2; i++) {
    if (s.substr(i, 3) == "ABC") {
      n_abc += 1;
    }
  }

  cout << n_abc << endl;
}
