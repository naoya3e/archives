#include <iostream>
#include <array>
using namespace std;

int main() {
  int n;
  cin >> n;

  array<int, 1000010> a;
  a[1] = 0;
  a[2] = 0;
  a[3] = 1;

  for (int i=4; i<n+1; i++) {
    a[i] = (a[i-1] + a[i-2] + a[i-3]) % 10007;
  }

  cout << a[n] << endl;

  return 0;
}
