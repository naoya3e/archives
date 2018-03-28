#include <bits/stdc++.h>
using namespace std;

// 100の重さのおもりが100個ある場合が最大
bool dp[10010];

int main() {
  ios::sync_with_stdio(false);

  int n;
  int w;
  int sum = 0;

  dp[0] = true;

  cin >> n;

  for (int i=0; i<n; i++) {
    cin >> w;
    sum += w;

    for (int j=10000; j>=w; j--) {
      dp[j] |= dp[j-w];
    }

    // DEBUG
    for (int i=0; i<10; i++) {
      cout << dp[i] << endl;
    }
    cout << "-------------" << endl;
  }

  // 重さの合計が奇数であれば、そもそも釣り合わせることはできない
  // 重さの合計の半分が片方に存在し得ればよい
  if (sum%2 == 0 && dp[sum/2]) cout << "possible" << endl;
  else cout << "impossible" << endl;
}
