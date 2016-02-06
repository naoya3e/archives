#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#define REP(i,n) for(int i=0; i<(int)(n); i++)

using namespace std;

int main() {
  ios::sync_with_stdio(false);

  int n;

  cin >> n;
  vector<string> s;
  vector<int> p;

  REP(i, n) {
    int y;
    string x;
    cin >> x >> y;
    s.push_back(x);
    p.push_back(y);
  }

  int sum = 0;
  for (int n : p) sum += n;

  int half = sum/2;

  bool status = false;
  REP(i,n) {
    if (p[i] > half) {
      cout << s[i] << endl;
      status = true;
      break;
    }
  }

  if (!status) cout << "atcoder" << endl;
}

