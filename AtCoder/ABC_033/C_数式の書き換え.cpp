#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#define REP(i,n) for(int i=0; i<(int)(n); i++)

using namespace std;

int main() {
  ios::sync_with_stdio(false);

  string s;
  cin >> s;

  int answer = 0;
  bool used = false;

  for (int i=0; i<s.size(); i++) {
    if (s[i] == '0') used = true;
    if (s[i] == '+') {
      if (!used) answer++;
      used = false;
    }
  }

  if (!used) answer++;

  cout << answer << endl;
}

