#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#define REP(i, n) for(int i=0; i<n; i++)

using namespace std;

int main() {
  ios::sync_with_stdio(false);

  string str;

  cin >> str;

  if (str[0] == str[1] && str[1] == str[2] && str[2] == str[3] && str[3] == str[0]) {
    cout << "SAME" << endl;
  } else {
    cout << "DIFFERENT" << endl;
  }
}

