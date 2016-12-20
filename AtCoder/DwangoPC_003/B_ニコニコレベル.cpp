#include <bits/stdc++.h>
using namespace std;

int main() {
  string T;
  cin >> T;

  regex re("[25]*\\?+");

  vector<string> result;

  sregex_iterator iter(T.cbegin(), T.cend(), re);
  sregex_iterator end;

  for (; iter != end; ++iter) {
    result.push_back(iter->str());
  }

  int max = 0;
  string target;

  for (auto el : result) {
    cout << el << endl;
    cout << el.length() << endl;
    // if (max > el.length()) {
    //   max = el.length();
    //   target = el;
    // }
  }

  cout << target << endl;
}
